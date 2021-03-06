 if (mpctx->sh_audio)
                if (!fill_audio_out_buffers())//djf 20151217 mark : 音频播放
                	
//djf 20151217 mark : 音频播放
static int fill_audio_out_buffers(void)
{
    unsigned int t;
    double tt;
    int playsize;
    int playflags = 0;
    int audio_eof = 0;
    int bytes_to_write;
    int format_change = 0;
    int timeout = 0;
    sh_audio_t *const sh_audio = mpctx->sh_audio;

    current_module = "play_audio";

    while (1) {
        int sleep_time;
        // all the current uses of ao_data.pts seem to be in aos that handle
        // sync completely wrong; there should be no need to use ao_data.pts
        // in get_space()
        ao_data.pts    = ((mpctx->sh_video ? mpctx->sh_video->timer : 0) + mpctx->delay) * 90000.0;
        bytes_to_write = mpctx->audio_out->get_space();// djf 20151209 mark : linux使用ALSA驱动: /libao2/ao_alsa.c中定义 1.
        if (mpctx->sh_video || bytes_to_write >= ao_data.outburst)
            break;
        if (timeout++ > 10) {
            mp_msg(MSGT_CPLAYER, MSGL_WARN, MSGTR_AudioDeviceStuck);
            break;
        }

        // handle audio-only case:
        // this is where mplayer sleeps during audio-only playback
        // to avoid 100% CPU use
        sleep_time = (ao_data.outburst - bytes_to_write) * 1000 / ao_data.bps;
        if (sleep_time < 10)
            sleep_time = 10;                  // limit to 100 wakeups per second
        usec_sleep(sleep_time * 1000);
    }

    while (bytes_to_write) {
        int res;
        playsize = bytes_to_write;
        if (playsize > MAX_OUTBURST)
            playsize = MAX_OUTBURST;
        bytes_to_write -= playsize;

        // Fill buffer if needed:
        current_module = "decode_audio";
        t = GetTimer();
        if (!format_change) {
            res = mp_decode_audio(sh_audio, playsize); //djf 20151204 mark : 音频流进行解码 2. 
            format_change = res == -2;
        }
        if (!format_change && res < 0) // EOF or error
            if (mpctx->d_audio->eof) {
                audio_eof = 1;
                if (sh_audio->a_out_buffer_len == 0)
                    return 0;
            }
        t  = GetTimer() - t;
        tt = t * 0.000001f;
        audio_time_usage += tt;
        if (playsize > sh_audio->a_out_buffer_len) {
            playsize = sh_audio->a_out_buffer_len;
            if (audio_eof || format_change)
                playflags |= AOPLAY_FINAL_CHUNK;
        }
        if (!playsize)
            break;

        // play audio:
        current_module = "play_audio";

        // Is this pts value actually useful for the aos that access it?
        // They're obviously badly broken in the way they handle av sync;
        // would not having access to this make them more broken?
        ao_data.pts = ((mpctx->sh_video ? mpctx->sh_video->timer : 0) + mpctx->delay) * 90000.0;
        playsize    = mpctx->audio_out->play(sh_audio->a_out_buffer, playsize, playflags);// djf 20151209 mark : 播放 3.

        if (playsize > 0) {
            sh_audio->a_out_buffer_len -= playsize;
            memmove(sh_audio->a_out_buffer, &sh_audio->a_out_buffer[playsize],
                    sh_audio->a_out_buffer_len);
            mpctx->delay += playback_speed * playsize / (double)ao_data.bps;
        } else if ((format_change || audio_eof) && mpctx->audio_out->get_delay() < .04) {
            // Sanity check to avoid hanging in case current ao doesn't output
            // partial chunks and doesn't check for AOPLAY_FINAL_CHUNK
            mp_msg(MSGT_CPLAYER, MSGL_WARN, MSGTR_AudioOutputTruncated);
            sh_audio->a_out_buffer_len = 0;
        }
    }
    if (format_change) {
        uninit_player(INITIALIZED_AO);
        reinit_audio_chain();
    }
    return 1;
}



//2. djf 20151204 mark : 音频流进行解码 /libmpcodecs/dec_audio.c
int mp_decode_audio(sh_audio_t *sh_audio, int minlen)
{
    // Indicates that a filter seems to be buffering large amounts of data
    int huge_filter_buffer = 0;
    // Decoded audio must be cut at boundaries of this many bytes
    int unitsize = sh_audio->channels * sh_audio->samplesize * 16;

    /* Filter output size will be about filter_multiplier times input size.
     * If some filter buffers audio in big blocks this might only hold
     * as average over time. */
    double filter_multiplier = af_calc_filter_multiplier(sh_audio->afilter);

    /* If the decoder set audio_out_minsize then it can do the equivalent of
     * "while (output_len < target_len) output_len += audio_out_minsize;",
     * so we must guarantee there is at least audio_out_minsize-1 bytes
     * more space in the output buffer than the minimum length we try to
     * decode. */
    int max_decode_len = sh_audio->a_buffer_size - sh_audio->audio_out_minsize;
    if (!unitsize)
        return -1;
    max_decode_len -= max_decode_len % unitsize;

    while (sh_audio->a_out_buffer_len < minlen) {
	int res;
	int declen = (minlen - sh_audio->a_out_buffer_len) / filter_multiplier
	    + (unitsize << 5); // some extra for possible filter buffering
	if (huge_filter_buffer)
	/* Some filter must be doing significant buffering if the estimated
	 * input length didn't produce enough output from filters.
	 * Feed the filters 2k bytes at a time until we have enough output.
	 * Very small amounts could make filtering inefficient while large
	 * amounts can make MPlayer demux the file unnecessarily far ahead
	 * to get audio data and buffer video frames in memory while doing
	 * so. However the performance impact of either is probably not too
	 * significant as long as the value is not completely insane. */
	    declen = 2000;
	declen -= declen % unitsize;
	if (declen > max_decode_len)
	    declen = max_decode_len;
	else
	    /* if this iteration does not fill buffer, we must have lots
	     * of buffering in filters */
	    huge_filter_buffer = 1;
	res = filter_n_bytes(sh_audio, declen);//djf 20151218 mark: 音频解码
	if (res < 0)
	    return res;
    }
    return 0;
}

//djf 20151218 mark: 音频解码
static int filter_n_bytes(sh_audio_t *sh, int len)
{
    int error = 0;
    // Filter
    af_data_t filter_input = {
	.audio = sh->a_buffer,
	.rate = sh->samplerate,
	.nch = sh->channels,
	.format = sh->sample_format
    };
    af_data_t *filter_output;

    assert(len-1 + sh->audio_out_minsize <= sh->a_buffer_size);

    // Decode more bytes if needed
    while (sh->a_buffer_len < len) {
	unsigned char *buf = sh->a_buffer + sh->a_buffer_len;
	int minlen = len - sh->a_buffer_len;
	int maxlen = sh->a_buffer_size - sh->a_buffer_len;
	int ret = sh->ad_driver->decode_audio(sh, buf, minlen, maxlen);// djf 20151217 mark: 音频解码 2.1.
	int format_change = sh->samplerate != filter_input.rate ||
	                    sh->channels != filter_input.nch ||
	                    sh->sample_format != filter_input.format;
	if (ret <= 0 || format_change) {
	    error = format_change ? -2 : -1;
	    len = sh->a_buffer_len;
	    break;
	}
	sh->a_buffer_len += ret;
    }

    filter_input.len = len;
    af_fix_parameters(&filter_input);
    filter_output = af_play(sh->afilter, &filter_input);// djf 20151217 mark :  2.2.
    if (!filter_output)
	return -1;
    if (sh->a_out_buffer_size < sh->a_out_buffer_len + filter_output->len) {
	int newlen = sh->a_out_buffer_len + filter_output->len;
	mp_msg(MSGT_DECAUDIO, MSGL_V, "Increasing filtered audio buffer size "
	       "from %d to %d\n", sh->a_out_buffer_size, newlen);
	sh->a_out_buffer = realloc(sh->a_out_buffer, newlen);
	sh->a_out_buffer_size = newlen;
    }
    memcpy(sh->a_out_buffer + sh->a_out_buffer_len, filter_output->audio,
	   filter_output->len);
    sh->a_out_buffer_len += filter_output->len;

    // remove processed data from decoder buffer:
    sh->a_buffer_len -= len;
    memmove(sh->a_buffer, sh->a_buffer + len, sh->a_buffer_len);

    return error;
}

//2.1. djf 20151217 mark: 音频解码 这里跳到具体解码协议文件，MP3在/libmpcodecs/ad_mp3lib.c中
static int decode_audio(sh_audio_t *sh_audio,unsigned char *buf,int minlen,int maxlen)
{
   return MP3_DecodeFrame(buf,-1);
}
//跳转到/mp3lib/sr1.c
// Read & decode a single frame. Called by sound driver.
int MP3_DecodeFrame(unsigned char *hova,short single){
   pcm_sample = hova;
   pcm_point = 0;
   if(!read_frame(&fr)) return 0;//djf 20151219 mark : 读取一帧数据 2.1.1
   if(single==-2){ set_pointer(512); return 1; }
   if(fr.error_protection) getbits(16); /* skip crc */
   fr.single=single;
   switch(fr.lay){
     case 2: do_layer2(&fr,single);break;
     case 3: do_layer3(&fr,single);break;//djf 20151219 mark : 按照MP3压缩方式解压 2.1.2
     case 1: do_layer1(&fr,single);break;
     default:
         return 0;      // unsupported
   }
//   ++MP3_frames;
   return pcm_point ? pcm_point : 2;
}

//2.1.1 djf 20151219 mark : 读取一帧数据
/*****************************************************************
 * read next frame     return number of frames read.
 */
LOCAL int read_frame(struct frame *fr){
  uint32_t newhead;
  union {
    unsigned char buf[8];
    unsigned long dummy; // for alignment
  } hbuf;
  int skipped,resyncpos;
  int frames=0;

resync:
  skipped=MP3_fpos;
  resyncpos=MP3_fpos;

  set_pointer(512);
  fsizeold=fr->framesize;       /* for Layer3 */
  if(!stream_head_read(hbuf.buf,&newhead)) return 0;//djf 20151219 mark : 读取4字节的帧头 2.1.1.1
  if(!decode_header(fr,newhead)){//djf 20151219 mark : 解析帧头 2.1.1.2
    // invalid header! try to resync stream!
#ifdef DEBUG_RESYNC
    printf("ReSync: searching for a valid header...  (pos=%X)\n",MP3_fpos);
#endif
retry1:
    while(!decode_header(fr,newhead)){
      if(!stream_head_shift(hbuf.buf,&newhead)) return 0;
    }
    resyncpos=MP3_fpos-4;
    // found valid header
#ifdef DEBUG_RESYNC
    printf("ReSync: found valid hdr at %X  fsize=%ld  ",resyncpos,fr->framesize);
#endif
    if(!stream_read_frame_body(fr->framesize)) return 0; // read body
    set_pointer(512);
    fsizeold=fr->framesize;       /* for Layer3 */
    if(!stream_head_read(hbuf.buf,&newhead)) return 0;
    if(!decode_header(fr,newhead)){
      // invalid hdr! go back...
#ifdef DEBUG_RESYNC
      printf("INVALID\n");
#endif
//      mp3_seek(resyncpos+1);
      if(!stream_head_read(hbuf.buf,&newhead)) return 0;
      goto retry1;
    }
#ifdef DEBUG_RESYNC
    printf("OK!\n");
    ++frames;
#endif
  }

  skipped=resyncpos-skipped;
//  if(skipped && !MP3_resync) printf("\r%d bad bytes skipped  (resync at 0x%X)                          \n",skipped,resyncpos);

//  printf("%8X [%08X] %d %d (%d)%s%s\n",MP3_fpos-4,newhead,fr->framesize,fr->mode,fr->mode_ext,fr->error_protection?" CRC":"",fr->padding?" PAD":"");

  /* read main data into memory */
  if(!stream_read_frame_body(fr->framesize)){
    printf("\nBroken frame at 0x%X                                                  \n",resyncpos);
    return 0;
  }
  ++frames;

  if(MP3_resync){
    MP3_resync=0;
    if(frames==1) goto resync;
  }

  return frames;
}

//2.1.1.1 djf 20151219 mark : 读取4字节的帧头
LOCAL int stream_head_read(unsigned char *hbuf,uint32_t *newhead){
  if(mp3_read(hbuf,4) != 4) return FALSE;//djf 20151219 mark : 读取4字节的帧头
#if ARCH_X86
  *newhead = bswap_32(*((uint32_t*)hbuf));
#else
  /*
   * we may not be able to address unaligned 32-bit data on non-x86 cpus.
   * Fall back to some portable code.
   */
  *newhead =
      hbuf[0] << 24 |
      hbuf[1] << 16 |
      hbuf[2] <<  8 |
      hbuf[3];
#endif
  return TRUE;
}

//djf 20151219 mark : 读取4字节的帧头
LOCAL int mp3_read(char *buf,int size){
//  int len=fread(buf,1,size,mp3_file);
  int len=mplayer_audio_read(buf,size);//djf 20151219 mark : 读取4字节的帧头
  if(len>0) MP3_fpos+=len;
//  if(len!=size) MP3_eof=1;
  return len;
}

//djf 20151219 mark : 读取4字节的帧头 这里回调/libmpcodecs/ad_mp3lib.c中函数
// MP3 decoder buffer callback:
int mplayer_audio_read(char *buf,int size){
  return demux_read_data(dec_audio_sh->ds,buf,size);//djf 20151219 mark : 读取4字节的帧头// djf 20151219 mark : dec_audio_sh是在init函数中初始化的
}

//djf 20151219 mark : 读取4字节的帧头 //这里调用/libmpdemux/demuxer.c中函数
int demux_read_data(demux_stream_t *ds, unsigned char *mem, int len)
{
    int x;
    int bytes = 0;
    while (len > 0) {
        x = ds->buffer_size - ds->buffer_pos;
        if (x == 0) {
            if (!ds_fill_buffer(ds))//djf 20151219 mark : 读取信息到ds->buffer
                return bytes;
        } else {
            if (x > len)
                x = len;
            if (mem)
                fast_memcpy(mem + bytes, &ds->buffer[ds->buffer_pos], x);
            bytes += x;
            len -= x;
            ds->buffer_pos += x;
        }
    }
    return bytes;
}

//djf 20151219 mark : 读取信息到ds->buffer
int ds_fill_buffer(demux_stream_t *ds)
{
    demuxer_t *demux = ds->demuxer;
    if (ds->current)
        free_demux_packet(ds->current);
    ds->current = NULL;
    if (mp_msg_test(MSGT_DEMUXER, MSGL_DBG3)) {
        if (ds == demux->audio)
            mp_dbg(MSGT_DEMUXER, MSGL_DBG3,
                   "ds_fill_buffer(d_audio) called\n");
        else if (ds == demux->video)
            mp_dbg(MSGT_DEMUXER, MSGL_DBG3,
                   "ds_fill_buffer(d_video) called\n");
        else if (ds == demux->sub)
            mp_dbg(MSGT_DEMUXER, MSGL_DBG3, "ds_fill_buffer(d_sub) called\n");
        else
            mp_dbg(MSGT_DEMUXER, MSGL_DBG3,
                   "ds_fill_buffer(unknown 0x%X) called\n", (unsigned int) ds);
    }
    while (1) {
        if (ds->packs) {
            demux_packet_t *p = ds->first;
            // obviously not yet EOF after all
            ds->eof = 0;
#if 0
            if (demux->reference_clock != MP_NOPTS_VALUE) {
                if (   p->pts != MP_NOPTS_VALUE
                    && p->pts >  demux->reference_clock
                    && ds->packs < MAX_ACCUMULATED_PACKETS) {
                    if (demux_fill_buffer(demux, ds))
                        continue;
                }
            }
#endif
            // copy useful data:
            ds->buffer = p->buffer;
            ds->buffer_pos = 0;
            ds->buffer_size = p->len;
            ds->pos = p->pos;
            ds->dpos += p->len; // !!!
            ++ds->pack_no;
            if (p->pts != MP_NOPTS_VALUE) {
                ds->pts = p->pts;
                ds->pts_bytes = 0;
            }
            ds->pts_bytes += p->len;    // !!!
            if (p->stream_pts != MP_NOPTS_VALUE)
                demux->stream_pts = p->stream_pts;
            ds->flags = p->flags;
            // unlink packet:
            ds->bytes -= p->len;
            ds->current = p;
            ds->first = p->next;
            if (!ds->first)
                ds->last = NULL;
            --ds->packs;
            return 1;
        }
        // avoid printing the "too many ..." message over and over
        if (ds->eof)
            break;
        if (demux->audio->packs >= MAX_PACKS
            || demux->audio->bytes >= MAX_PACK_BYTES) {
            mp_msg(MSGT_DEMUXER, MSGL_ERR, MSGTR_TooManyAudioInBuffer,
                   demux->audio->packs, demux->audio->bytes);
            mp_msg(MSGT_DEMUXER, MSGL_HINT, MSGTR_MaybeNI);
            break;
        }
        if (demux->video->packs >= MAX_PACKS
            || demux->video->bytes >= MAX_PACK_BYTES) {
            mp_msg(MSGT_DEMUXER, MSGL_ERR, MSGTR_TooManyVideoInBuffer,
                   demux->video->packs, demux->video->bytes);
            mp_msg(MSGT_DEMUXER, MSGL_HINT, MSGTR_MaybeNI);
            break;
        }
        if (!demux_fill_buffer(demux, ds)) {//djf 20151219 mark : 利用demux->desc中的函数读取信息到ds->buffer
#if PARSE_ON_ADD && defined(CONFIG_FFMPEG)
            uint8_t *parsed_start = NULL;
            int parsed_len = 0;
            ds_parse(ds->sh, &parsed_start, &parsed_len, MP_NOPTS_VALUE, 0);
            if (parsed_len) {
                demux_packet_t *dp2 = new_demux_packet(parsed_len);
                if (!dp2) continue;
                dp2->pts = MP_NOPTS_VALUE;
                memcpy(dp2->buffer, parsed_start, parsed_len);
                ds_add_packet_internal(ds, dp2);
                continue;
            }
#endif
            mp_dbg(MSGT_DEMUXER, MSGL_DBG2,
                   "ds_fill_buffer()->demux_fill_buffer() failed\n");
            break; // EOF
        }
    }
    ds->buffer_pos = ds->buffer_size = 0;
    ds->buffer = NULL;
    mp_msg(MSGT_DEMUXER, MSGL_V,
           "ds_fill_buffer: EOF reached (stream: %s)  \n",
           ds == demux->audio ? "audio" : "video");
    ds->eof = 1;
    return 0;
}

//djf 20151219 mark : 利用demux->desc中的函数读取信息到ds->buffer
int demux_fill_buffer(demuxer_t *demux, demux_stream_t *ds)
{
    // Note: parameter 'ds' can be NULL!
    return demux->desc->fill_buffer(demux, ds);//djf 20151219 mark : 此处会调用具体协议中的函数，在demux中已找到对应结构 mp3 在/libmpdemux/demux_desc_audio.c中
}


//djf 20151219 mark : 此处会调用具体协议中的函数，在demux中已找到对应结构 mp3 在/libmpdemux/demux_desc_audio.c中
static int demux_audio_fill_buffer(demuxer_t *demux, demux_stream_t *ds) {
  int l;
  demux_packet_t* dp;
  sh_audio_t* sh_audio = ds->sh;
  da_priv_t* priv = demux->priv;
  double this_pts = priv->next_pts;
  stream_t* s = demux->stream;

  if(s->eof)
    return 0;

  switch(priv->frmt) {
  case MP3 :
    while(1) {
      uint8_t hdr[4];
      stream_read(s,hdr,4);// djf 20151219 mark : 从stream->buffer中读取4字节的数据
      if (s->eof)
        return 0;
      l = mp_decode_mp3_header(hdr);//djf 20151218 mark : 计算出mp3 帧大小
      if(l < 0) {
	if (demux->movi_end && stream_tell(s) >= demux->movi_end)
	  return 0; // might be ID3 tag, i.e. EOF
	stream_skip(s,-3);
      } else {
	dp = new_demux_packet(l);
	memcpy(dp->buffer,hdr,4);
	if (stream_read(s,dp->buffer + 4,l-4) != l-4)// djf 20151218 mark : 读取除去帧头4字节的剩余字节
	{
	  free_demux_packet(dp);
	  return 0;
	}
	priv->next_pts += sh_audio->audio.dwScale/(double)sh_audio->samplerate;
	break;
      }
    } break;
  case WAV : {
    unsigned align = sh_audio->wf->nBlockAlign;
    l = sh_audio->wf->nAvgBytesPerSec;
    if (l <= 0) l = 65536;
    if (demux->movi_end && l > demux->movi_end - stream_tell(s)) {
      // do not read beyond end, there might be junk after data chunk
      l = demux->movi_end - stream_tell(s);
      if (l <= 0) return 0;
    }
    if (align)
      l = (l + align - 1) / align * align;
    dp = new_demux_packet(l);
    l = stream_read(s,dp->buffer,l);
    priv->next_pts += l/(double)sh_audio->i_bps;
    break;
  }
  case fLaC: {
    l = 65535;
    dp = new_demux_packet(l);
    l = stream_read(s,dp->buffer,l);
    priv->next_pts = MP_NOPTS_VALUE;
    break;
  }
  default:
    mp_msg(MSGT_DEMUXER,MSGL_WARN,MSGTR_MPDEMUX_AUDIO_UnknownFormat,priv->frmt);
    return 0;
  }

  resize_demux_packet(dp, l);
  dp->pts = this_pts;
  ds_add_packet(ds, dp);//djf 20151219 mark : 将读取到的一帧信息存储到ds->last
  return 1;
}

//djf 20151219 mark : 将读取到的一帧信息存储到ds->last
void ds_add_packet(demux_stream_t *ds, demux_packet_t *dp)
{
#if PARSE_ON_ADD && defined(CONFIG_FFMPEG)
    int len = dp->len;
    int pos = 0;
    while (len > 0) {
        uint8_t *parsed_start = dp->buffer + pos;
        int parsed_len = len;
        int consumed = ds_parse(ds->sh, &parsed_start, &parsed_len, dp->pts, dp->pos);
        pos += consumed;
        len -= consumed;
        if (parsed_start == dp->buffer && parsed_len == dp->len) {
            ds_add_packet_internal(ds, dp);
        } else if (parsed_len) {
            demux_packet_t *dp2 = new_demux_packet(parsed_len);
            if (!dp2) return;
            dp2->pos = dp->pos;
            dp2->pts = dp->pts; // should be parser->pts but that works badly
            memcpy(dp2->buffer, parsed_start, parsed_len);
            ds_add_packet_internal(ds, dp2);
        }
    }
#else
    ds_add_packet_internal(ds, dp);
#endif
}

static void ds_add_packet_internal(demux_stream_t *ds, demux_packet_t *dp)
{
    // append packet to DS stream:
    ++ds->packs;
    ds->bytes += dp->len;
    if (ds->last) {
        // next packet in stream
        ds->last->next = dp;
        ds->last = dp;
    } else {
        // first packet in stream
        ds->first = ds->last = dp;
    }
    mp_dbg(MSGT_DEMUXER, MSGL_DBG2,
           "DEMUX: Append packet to %s, len=%d  pts=%5.3f  pos=%u  [packs: A=%d V=%d]\n",
           (ds == ds->demuxer->audio) ? "d_audio" : "d_video", dp->len,
           dp->pts, (unsigned int) dp->pos, ds->demuxer->audio->packs,
           ds->demuxer->video->packs);
}




//2.1.1.2djf 20151219 mark : 解析帧头 
/*
 * decode a header and write the information
 * into the frame structure
 */
LOCAL int decode_header(struct frame *fr,uint32_t newhead){

    // head_check:
    if( (newhead & 0xffe00000) != 0xffe00000 ||
        (newhead & 0x0000fc00) == 0x0000fc00) return FALSE;

    fr->lay = 4-((newhead>>17)&3);
//    if(fr->lay!=3) return FALSE;

    if( newhead & (1<<20) ) {
      fr->lsf = (newhead & (1<<19)) ? 0x0 : 0x1;
      fr->mpeg25 = 0;
    } else {
      fr->lsf = 1;
      fr->mpeg25 = 1;
    }

    if(fr->mpeg25)
      fr->sampling_frequency = 6 + ((newhead>>10)&0x3);
    else
      fr->sampling_frequency = ((newhead>>10)&0x3) + (fr->lsf*3);

    if(fr->sampling_frequency>8) return FALSE;  // valid: 0..8

    fr->error_protection = ((newhead>>16)&0x1)^0x1;
    fr->bitrate_index = ((newhead>>12)&0xf);
    fr->padding   = ((newhead>>9)&0x1);
    fr->extension = ((newhead>>8)&0x1);
    fr->mode      = ((newhead>>6)&0x3);
    fr->mode_ext  = ((newhead>>4)&0x3);
    fr->copyright = ((newhead>>3)&0x1);
    fr->original  = ((newhead>>2)&0x1);
    fr->emphasis  = newhead & 0x3;

    MP3_channels = fr->stereo    = (fr->mode == MPG_MD_MONO) ? 1 : 2;

    if(!fr->bitrate_index){
//      fprintf(stderr,"Free format not supported.\n");
      return FALSE;
    }

switch(fr->lay){
  case 2:
    MP3_bitrate=tabsel_123[fr->lsf][1][fr->bitrate_index];
    MP3_samplerate=freqs[fr->sampling_frequency];
    fr->framesize = MP3_bitrate * 144000;
    fr->framesize /= MP3_samplerate;
    MP3_framesize=fr->framesize;
    fr->framesize += fr->padding - 4;
    break;
  case 3:
    if(fr->lsf)
      ssize = (fr->stereo == 1) ? 9 : 17;
    else
      ssize = (fr->stereo == 1) ? 17 : 32;
    if(fr->error_protection) ssize += 2;

    MP3_bitrate=tabsel_123[fr->lsf][2][fr->bitrate_index];
    MP3_samplerate=freqs[fr->sampling_frequency];
    fr->framesize  = MP3_bitrate * 144000;
    fr->framesize /= MP3_samplerate<<(fr->lsf);
    MP3_framesize=fr->framesize;
    fr->framesize += fr->padding - 4;
    break;
  case 1:
//    fr->jsbound = (fr->mode == MPG_MD_JOINT_STEREO) ? (fr->mode_ext<<2)+4 : 32;
    MP3_bitrate=tabsel_123[fr->lsf][0][fr->bitrate_index];
    MP3_samplerate=freqs[fr->sampling_frequency];
    fr->framesize  = MP3_bitrate * 12000;
    fr->framesize /= MP3_samplerate;
    MP3_framesize  = ((fr->framesize+fr->padding)<<2);
    fr->framesize  = MP3_framesize-4;
//    printf("framesize=%d\n",fr->framesize);
    break;
  default:
    MP3_framesize=fr->framesize=0;
//    fprintf(stderr,"Sorry, unsupported layer type.\n");
    return 0;
}
    if(fr->framesize<=0 || fr->framesize>MAXFRAMESIZE) return FALSE;

    return 1;
}





//2.1.2 djf 20151219 mark : 按照MP3压缩方式解压  /mp3lib/layer3.c

/*
 * main layer3 handler
 */
/* int do_layer3(struct frame *fr,int outmode,struct audio_info_struct *ai) */
static int do_layer3(struct frame *fr,int single){
  int gr, ch, ss,clip=0;
  int scalefacs[2][39]; /* max 39 for short[13][3] mode, mixed: 38, long: 22 */
  struct III_sideinfo sideinfo;
  int stereo = fr->stereo;
  int ms_stereo,i_stereo;
  int sfreq = fr->sampling_frequency;
  int stereo1,granules;

//  if (fr->error_protection) getbits(16); /* skip crc */

  if(stereo == 1) { /* stream is mono */
    stereo1 = 1;
    single = 0;
  } else
  if(single >= 0) /* stream is stereo, but force to mono */
    stereo1 = 1;
  else
    stereo1 = 2;

  if(fr->mode == MPG_MD_JOINT_STEREO) {
    ms_stereo = (fr->mode_ext & 0x2)>>1;
    i_stereo  = fr->mode_ext & 0x1;
  } else
    ms_stereo = i_stereo = 0;

  if(!III_get_side_info(&sideinfo,stereo,ms_stereo,sfreq,single,fr->lsf))
    return -1;

  set_pointer(sideinfo.main_data_begin);

  granules = (fr->lsf) ? 1 : 2;
  for (gr=0;gr<granules;gr++){
    DECLARE_ALIGNED(16, real, hybridIn[2][SBLIMIT][SSLIMIT]);
    DECLARE_ALIGNED(16, real, hybridOut[2][SSLIMIT][SBLIMIT]);

    { struct gr_info_s *gr_info = &(sideinfo.ch[0].gr[gr]);
      int part2bits;
      if(fr->lsf)
        part2bits = III_get_scale_factors_2(scalefacs[0],gr_info,0);
      else
        part2bits = III_get_scale_factors_1(scalefacs[0],gr_info);
      if(III_dequantize_sample(hybridIn[0], scalefacs[0],gr_info,sfreq,part2bits))
        return clip;
    }

    if(stereo == 2) {
      struct gr_info_s *gr_info = &(sideinfo.ch[1].gr[gr]);

      int part2bits;
      if(fr->lsf)
        part2bits = III_get_scale_factors_2(scalefacs[1],gr_info,i_stereo);
      else
        part2bits = III_get_scale_factors_1(scalefacs[1],gr_info);

      if(III_dequantize_sample(hybridIn[1],scalefacs[1],gr_info,sfreq,part2bits))
          return clip;

      if(ms_stereo) {
        int i;
        int maxb = sideinfo.ch[0].gr[gr].maxb;
        if(sideinfo.ch[1].gr[gr].maxb > maxb)
            maxb = sideinfo.ch[1].gr[gr].maxb;
        for(i=0;i<SSLIMIT*maxb;i++) {
          real tmp0 = ((real *)hybridIn[0])[i];
          real tmp1 = ((real *)hybridIn[1])[i];
          ((real *)hybridIn[0])[i] = tmp0 + tmp1;
          ((real *)hybridIn[1])[i] = tmp0 - tmp1;
        }
      }

      if(i_stereo)
        III_i_stereo(hybridIn,scalefacs[1],gr_info,sfreq,ms_stereo,fr->lsf);

      if(ms_stereo || i_stereo || (single == 3) ) {
        if(gr_info->maxb > sideinfo.ch[0].gr[gr].maxb)
          sideinfo.ch[0].gr[gr].maxb = gr_info->maxb;
        else
          gr_info->maxb = sideinfo.ch[0].gr[gr].maxb;
      }

      switch(single) {
        case 3: {
          register int i;
          register real *in0 = (real *) hybridIn[0],*in1 = (real *) hybridIn[1];
          for(i=0;i<SSLIMIT*gr_info->maxb;i++,in0++)
            *in0 = (*in0 + *in1++); /* *0.5 done by pow-scale */
          break; }
        case 1: {
          register int i;
          register real *in0 = (real *) hybridIn[0],*in1 = (real *) hybridIn[1];
          for(i=0;i<SSLIMIT*gr_info->maxb;i++)
            *in0++ = *in1++;
          break; }
      }

    }  // if(stereo == 2)

    for(ch=0;ch<stereo1;ch++) {
      struct gr_info_s *gr_info = &(sideinfo.ch[ch].gr[gr]);
                  III_antialias(hybridIn[ch],gr_info);
                  III_hybrid(hybridIn[ch], hybridOut[ch], ch,gr_info);
    }

    for(ss=0;ss<SSLIMIT;ss++) {
      if(single >= 0) {
                    clip += (fr->synth_mono)(hybridOut[0][ss],pcm_sample,&pcm_point);
                } else {
                  int p1 = pcm_point;
                    clip += (fr->synth)(hybridOut[0][ss],0,pcm_sample,&p1);
                    clip += (fr->synth)(hybridOut[1][ss],1,pcm_sample,&pcm_point);
      }
    }

  }

  return clip;
}
