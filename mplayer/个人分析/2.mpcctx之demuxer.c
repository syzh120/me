mpctx->demuxer = demux_open(mpctx->stream, mpctx->file_format, audio_id, video_id, dvdsub_id, filename); // djf 20151203 mark: 分离音视频流

// libmpdemux/demuxer.c
demuxer_t *demux_open(stream_t *vs, int file_format, int audio_id,
                      int video_id, int dvdsub_id, char *filename)
{
    stream_t *as = NULL, *ss = NULL;
    demuxer_t *vd, *ad = NULL, *sd = NULL;
    demuxer_t *res;
    int afmt = DEMUXER_TYPE_UNKNOWN, sfmt = DEMUXER_TYPE_UNKNOWN;
    int demuxer_type;
    int audio_demuxer_type = 0, sub_demuxer_type = 0;
    int demuxer_force = 0, audio_demuxer_force = 0, sub_demuxer_force = 0;

    if ((demuxer_type =
         get_demuxer_type_from_name(demuxer_name, &demuxer_force)) < 0) {
        mp_msg(MSGT_DEMUXER, MSGL_ERR, "-demuxer %s does not exist.\n",
               demuxer_name);
    }
    if ((audio_demuxer_type =
         get_demuxer_type_from_name(audio_demuxer_name,
                                    &audio_demuxer_force)) < 0) {
        mp_msg(MSGT_DEMUXER, MSGL_ERR, "-audio-demuxer %s does not exist.\n",
               audio_demuxer_name);
    }
    if ((sub_demuxer_type =
         get_demuxer_type_from_name(sub_demuxer_name,
                                    &sub_demuxer_force)) < 0) {
        mp_msg(MSGT_DEMUXER, MSGL_ERR, "-sub-demuxer %s does not exist.\n",
               sub_demuxer_name);
    }

    if (audio_stream) {
        as = open_stream(audio_stream, 0, &afmt);
        if (!as) {
            mp_msg(MSGT_DEMUXER, MSGL_ERR, MSGTR_CannotOpenAudioStream,
                   audio_stream);
            return NULL;
        }
        if (audio_stream_cache) {
            if (!stream_enable_cache
                (as, audio_stream_cache * 1024,
                 audio_stream_cache * 1024 * (stream_cache_min_percent /
                                              100.0),
                 audio_stream_cache * 1024 * (stream_cache_seek_min_percent /
                                              100.0))) {
                free_stream(as);
                mp_msg(MSGT_DEMUXER, MSGL_ERR,
                       "Can't enable audio stream cache\n");
                return NULL;
            }
        }
    }
    if (sub_stream) {
        ss = open_stream(sub_stream, 0, &sfmt);
        if (!ss) {
            mp_msg(MSGT_DEMUXER, MSGL_ERR, MSGTR_CannotOpenSubtitlesStream,
                   sub_stream);
            return NULL;
        }
    }

    vd = demux_open_stream(vs, demuxer_type ? demuxer_type : file_format,
                           demuxer_force, audio_stream ? -2 : audio_id,
                           video_id, sub_stream ? -2 : dvdsub_id, filename);// djf 20151203 mark: 分离音视频流
    if (!vd) {
        if (as)
            free_stream(as);
        if (ss)
            free_stream(ss);
        return NULL;
    }
    if (as) {
        ad = demux_open_stream(as,
                               audio_demuxer_type ? audio_demuxer_type : afmt,
                               audio_demuxer_force, audio_id, -2, -2,
                               audio_stream);
        if (!ad) {
            mp_msg(MSGT_DEMUXER, MSGL_WARN, MSGTR_OpeningAudioDemuxerFailed,
                   audio_stream);
            free_stream(as);
        } else if (ad->audio->sh
                   && ((sh_audio_t *) ad->audio->sh)->format == 0x55) // MP3
            hr_mp3_seek = 1;    // Enable high res seeking
    }
    if (ss) {
        sd = demux_open_stream(ss, sub_demuxer_type ? sub_demuxer_type : sfmt,
                               sub_demuxer_force, -2, -2, dvdsub_id,
                               sub_stream);
        if (!sd) {
            mp_msg(MSGT_DEMUXER, MSGL_WARN,
                   MSGTR_OpeningSubtitlesDemuxerFailed, sub_stream);
            free_stream(ss);
        }
    }

    if (ad && sd)
        res = new_demuxers_demuxer(vd, ad, sd);
    else if (ad)
        res = new_demuxers_demuxer(vd, ad, vd);
    else if (sd)
        res = new_demuxers_demuxer(vd, vd, sd);
    else
        res = vd;

    correct_pts = user_correct_pts;
    if (correct_pts < 0)
        correct_pts = !force_fps && demux_control(res, DEMUXER_CTRL_CORRECT_PTS, NULL)
                      == DEMUXER_CTRL_OK;
    return res;
}

static demuxer_t *demux_open_stream(stream_t *stream, int file_format,
                                    int force, int audio_id, int video_id,
                                    int dvdsub_id, char *filename)
{
    demuxer_t *demuxer = NULL;

    sh_video_t *sh_video = NULL;

    const demuxer_desc_t *demuxer_desc;
    int fformat = 0;
    int i;

    // If somebody requested a demuxer check it
    if (file_format) { // djf 20151205 mark ： 回调后执行这里 //3.
        if ((demuxer_desc = get_demuxer_desc_from_type(file_format))) {// djf 20151205 mark : 获取具体编码协议的描述结构
            demuxer = new_demuxer(stream, demuxer_desc->type, audio_id,
                                  video_id, dvdsub_id, filename); // djf 20151205 mark :  demuxer 分配空间 //4.
            if (demuxer_desc->check_file)
                fformat = demuxer_desc->check_file(demuxer);// djf 20151205 mark :  调用具体的函数，读取部分数据并检测mp3的数据头信息  //5.
            if (force || !demuxer_desc->check_file)
                fformat = demuxer_desc->type;
            if (fformat != 0) {
                if (fformat == demuxer_desc->type) {// djf 20151207 mark: mp3的话都是: DEMUXER_TYPE_AUDIO
                    demuxer_t *demux2 = demuxer;
                    // Move messages to demuxer detection code?
                    mp_msg(MSGT_DEMUXER, MSGL_INFO,
                           MSGTR_Detected_XXX_FileFormat,
                           demuxer_desc->shortdesc);
                    file_format = fformat;
                    if (!demuxer->desc->open
                        || (demux2 = demuxer->desc->open(demuxer))) {
                        demuxer = demux2;
                        goto dmx_open;// djf 20151207 mark: mp3的话，demuxer->desc->open=NULL
                    }
                } else {
                    // Format changed after check, recurse
                    free_demuxer(demuxer);
                    return demux_open_stream(stream, fformat, force, audio_id,
                                             video_id, dvdsub_id, filename);
                }
            }
            // Check failed for forced demuxer, quit
            free_demuxer(demuxer);
            return NULL;
        }
    }
    // Test demuxers with safe file checks
    for (i = 0; (demuxer_desc = demuxer_list[i]); i++) { 
        if (demuxer_desc->safe_check) {
            demuxer = new_demuxer(stream, demuxer_desc->type, audio_id,
                                  video_id, dvdsub_id, filename);
            if ((fformat = demuxer_desc->check_file(demuxer)) != 0) {
                if (fformat == demuxer_desc->type) {
                    demuxer_t *demux2 = demuxer;
                    mp_msg(MSGT_DEMUXER, MSGL_INFO,
                           MSGTR_Detected_XXX_FileFormat,
                           demuxer_desc->shortdesc);
                    file_format = fformat;
                    if (!demuxer->desc->open
                        || (demux2 = demuxer->desc->open(demuxer))) {
                        demuxer = demux2;
                        goto dmx_open;
                    }
                } else {
                    if (fformat == DEMUXER_TYPE_PLAYLIST)
                        return demuxer; // handled in mplayer.c
                    // Format changed after check, recurse
                    free_demuxer(demuxer);
                    demuxer = demux_open_stream(stream, fformat, force,
                                                audio_id, video_id,
                                                dvdsub_id, filename);
                    if (demuxer)
                        return demuxer; // done!
                    file_format = DEMUXER_TYPE_UNKNOWN;
                }
            }
            free_demuxer(demuxer);
            demuxer = NULL;
        }
    }

    // If no forced demuxer perform file extension based detection
    // Ok. We're over the stable detectable fileformats, the next ones are
    // a bit fuzzy. So by default (extension_parsing==1) try extension-based
    // detection first:
    if (file_format == DEMUXER_TYPE_UNKNOWN && filename
        && extension_parsing == 1) { 
        file_format = demuxer_type_by_filename(filename);//djf 20151203 mark :  file_format, mp3->DEMUXER_TYPE_AUDIO 17 //1.
        if (file_format != DEMUXER_TYPE_UNKNOWN) {
            // we like recursion :)
            demuxer = demux_open_stream(stream, file_format, force, audio_id,
                                        video_id, dvdsub_id, filename);// djf 20151203 mark : 回调自己 //2.
            if (demuxer)
                return demuxer; // done! //djf 20151207 mark: 回调返回到这里，完成 demuxer
            file_format = DEMUXER_TYPE_UNKNOWN; // continue fuzzy guessing...
            mp_msg(MSGT_DEMUXER, MSGL_V,
                   "demuxer: continue fuzzy content-based format guessing...\n");
        }
    }
    // Try detection for all other demuxers
    for (i = 0; (demuxer_desc = demuxer_list[i]); i++) {
        if (!demuxer_desc->safe_check && demuxer_desc->check_file) {
            demuxer = new_demuxer(stream, demuxer_desc->type, audio_id,
                                  video_id, dvdsub_id, filename);
            if ((fformat = demuxer_desc->check_file(demuxer)) != 0) {
                if (fformat == demuxer_desc->type) {
                    demuxer_t *demux2 = demuxer;
                    mp_msg(MSGT_DEMUXER, MSGL_INFO,
                           MSGTR_Detected_XXX_FileFormat,
                           demuxer_desc->shortdesc);
                    file_format = fformat;
                    if (!demuxer->desc->open
                        || (demux2 = demuxer->desc->open(demuxer))) {
                        demuxer = demux2;
                        goto dmx_open;
                    }
                } else {
                    if (fformat == DEMUXER_TYPE_PLAYLIST)
                        return demuxer; // handled in mplayer.c
                    // Format changed after check, recurse
                    free_demuxer(demuxer);
                    demuxer = demux_open_stream(stream, fformat, force,
                                                audio_id, video_id,
                                                dvdsub_id, filename);
                    if (demuxer)
                        return demuxer; // done!
                    file_format = DEMUXER_TYPE_UNKNOWN;
                }
            }
            free_demuxer(demuxer);
            demuxer = NULL;
        }
    }

    return NULL;
    //====== File format recognized, set up these for compatibility: =========
 dmx_open:

    demuxer->file_format = file_format;

    if ((sh_video = demuxer->video->sh) && sh_video->bih) {
        int biComp = le2me_32(sh_video->bih->biCompression);
        mp_msg(MSGT_DEMUX, MSGL_INFO,
               "VIDEO:  [%.4s]  %dx%d  %dbpp  %5.3f fps  %5.1f kbps (%4.1f kbyte/s)\n",
               (char *) &biComp, sh_video->bih->biWidth,
               sh_video->bih->biHeight, sh_video->bih->biBitCount,
               sh_video->fps, sh_video->i_bps * 0.008f,
               sh_video->i_bps / 1024.0f);
    }
#ifdef CONFIG_ASS
    if (ass_enabled && ass_library) {
        for (i = 0; i < MAX_S_STREAMS; ++i) {
            sh_sub_t *sh = demuxer->s_streams[i];
            if (sh && sh->type == 'a') {
                sh->ass_track = ass_new_track(ass_library);
                if (sh->ass_track && sh->extradata)
                    ass_process_codec_private(sh->ass_track, sh->extradata,
                                              sh->extradata_len);
            } else if (sh && sh->type != 'v')
                sh->ass_track = ass_default_track(ass_library);
        }
    }
#endif
    return demuxer;//20151207 mark: 回调完毕，返回到 6.
}


//1. libmpdemux/extension.c

int demuxer_type_by_filename(char* filename){ //djf 20151205 mark: 根据文件后缀名获取协议类型
  int i;
  char* extension=strrchr(filename,'.');
  mp_msg(MSGT_OPEN, MSGL_V, "Searching demuxer type for filename %s ext: %s\n",filename,extension);
  if(extension) {
    ++extension;
//    mp_msg(MSGT_CPLAYER,MSGL_DBG2,"Extension: %s\n", extension );
    // Look for the extension in the extensions table
    for( i=0 ; i<(sizeof(extensions_table)/sizeof(extensions_table[0])) ; i++ ) { // djf 20151205 mark : 包括所有可识别后缀名
      if( !strcasecmp(extension, extensions_table[i].extension) ) {
        mp_msg(MSGT_OPEN, MSGL_V, "Trying demuxer %d based on filename extension\n",extensions_table[i].demuxer_type);
        return extensions_table[i].demuxer_type;
      }
    }
  }
  return DEMUXER_TYPE_UNKNOWN;
}
static struct {
        const char *extension;
        int demuxer_type;
} extensions_table[] = { // djf 20151205 mark : 包括所有可识别后缀名
//        { "mpeg", DEMUXER_TYPE_MPEG_PS },
//        { "mpg", DEMUXER_TYPE_MPEG_PS },
//        { "mpe", DEMUXER_TYPE_MPEG_PS },
        { "vob", DEMUXER_TYPE_MPEG_PS },
        { "m2v", DEMUXER_TYPE_MPEG_PS },
        { "avi", DEMUXER_TYPE_AVI },
        { "asx", DEMUXER_TYPE_ASF },
        { "asf", DEMUXER_TYPE_ASF },
        { "wmv", DEMUXER_TYPE_ASF },
        { "wma", DEMUXER_TYPE_ASF },
        { "viv", DEMUXER_TYPE_VIVO },
        { "vivo", DEMUXER_TYPE_VIVO },
        { "rm", DEMUXER_TYPE_REAL },
        { "rmvb", DEMUXER_TYPE_REAL },
        { "ra", DEMUXER_TYPE_REAL },
        { "y4m", DEMUXER_TYPE_Y4M },
        { "mp3", DEMUXER_TYPE_AUDIO }, //djf 20151205 mark : mp3格式
        { "wav", DEMUXER_TYPE_AUDIO },
        { "flac", DEMUXER_TYPE_AUDIO },
        { "fla", DEMUXER_TYPE_AUDIO },
        { "ogg", DEMUXER_TYPE_OGG },
        { "ogm", DEMUXER_TYPE_OGG },
//        { "pls", DEMUXER_TYPE_PLAYLIST },
//        { "m3u", DEMUXER_TYPE_PLAYLIST },
        { "xm", DEMUXER_TYPE_XMMS },
        { "mod", DEMUXER_TYPE_XMMS },
        { "s3m", DEMUXER_TYPE_XMMS },
        { "it", DEMUXER_TYPE_XMMS },
        { "mid", DEMUXER_TYPE_XMMS },
        { "midi", DEMUXER_TYPE_XMMS },
        { "nsv", DEMUXER_TYPE_NSV },
        { "nsa", DEMUXER_TYPE_NSV },
        { "mpc", DEMUXER_TYPE_MPC },
#ifdef CONFIG_WIN32DLL
        { "avs", DEMUXER_TYPE_AVS },
#endif
	{ "302", DEMUXER_TYPE_LAVF },
        { "264", DEMUXER_TYPE_H264_ES },
        { "26l", DEMUXER_TYPE_H264_ES },
	{ "ac3", DEMUXER_TYPE_LAVF },
        { "ape", DEMUXER_TYPE_LAVF },
        { "apl", DEMUXER_TYPE_LAVF },
        { "eac3",DEMUXER_TYPE_LAVF },
        { "mac", DEMUXER_TYPE_LAVF },
        { "str", DEMUXER_TYPE_LAVF },
        { "cdg", DEMUXER_TYPE_LAVF },

// At least the following are hacks against broken autodetection
// that should not be there

};


// 2. 获取到 file_format之后，回调自己，然后会执行 3.

//3. // djf 20151205 mark : 获取具体编码协议的描述结构
static const demuxer_desc_t *get_demuxer_desc_from_type(int file_format)
{
    int i;

    for (i = 0; demuxer_list[i]; i++) //djf 20151205 mark: 包含所有支持的协议，此处为编码协议
        if (file_format == demuxer_list[i]->type)
            return demuxer_list[i];

    return NULL;
}

const demuxer_desc_t *const demuxer_list[] = { // djf 20151205 mark : 包含所有支持的协议，此处为编码协议
    &demuxer_desc_rawaudio,
    &demuxer_desc_rawvideo,
#ifdef CONFIG_TV
    &demuxer_desc_tv,
#endif
    &demuxer_desc_mf,
#ifdef CONFIG_FFMPEG
    &demuxer_desc_lavf_preferred,
#endif
    &demuxer_desc_avi,
    &demuxer_desc_y4m,
    &demuxer_desc_asf,
    &demuxer_desc_nsv,
    &demuxer_desc_real,
    &demuxer_desc_smjpeg,
    &demuxer_desc_matroska,
    &demuxer_desc_realaudio,
    &demuxer_desc_vqf,
    &demuxer_desc_mov,
    &demuxer_desc_vivo,
    &demuxer_desc_fli,
    &demuxer_desc_film,
    &demuxer_desc_roq,
#ifdef CONFIG_GIF
    &demuxer_desc_gif,
#endif
#ifdef CONFIG_OGGVORBIS
    &demuxer_desc_ogg,
#endif
#ifdef CONFIG_WIN32DLL
    &demuxer_desc_avs,
#endif
    &demuxer_desc_pva,
    &demuxer_desc_mpeg_ts,
    &demuxer_desc_lmlm4,
    &demuxer_desc_mpeg_ps,
    &demuxer_desc_mpeg_pes,
    &demuxer_desc_mpeg_es,
    &demuxer_desc_mpeg_gxf,
    &demuxer_desc_mpeg4_es,
    &demuxer_desc_h264_es,
    &demuxer_desc_audio, // djf 20151205 mark : mp3格式使用这里
    &demuxer_desc_mpeg_ty,
#ifdef CONFIG_LIVE555
    &demuxer_desc_rtp,
#endif
#ifdef CONFIG_LIBNEMESI
    &demuxer_desc_rtp_nemesi,
#endif
#ifdef CONFIG_FFMPEG
    &demuxer_desc_lavf,
#endif
#ifdef CONFIG_MUSEPACK
    &demuxer_desc_mpc,
#endif
#ifdef CONFIG_LIBDV095
    &demuxer_desc_rawdv,
#endif
    &demuxer_desc_aac,
#ifdef CONFIG_LIBNUT
    &demuxer_desc_nut,
#endif
#ifdef CONFIG_XMMS
    &demuxer_desc_xmms,
#endif
#ifdef CONFIG_MNG
    &demuxer_desc_mng,
#endif
    /* Please do not add any new demuxers here. If you want to implement a new
     * demuxer, add it to libavformat, except for wrappers around external
     * libraries and demuxers requiring binary support. */
    NULL
};



// libmpdemux/demux_audio.c
const demuxer_desc_t demuxer_desc_audio = { // djf 20151205 mark : mp3格式使用这里
  "Audio demuxer",
  "audio",
  "Audio only",
  "?",
  "Audio only files",
  DEMUXER_TYPE_AUDIO,
  0, // unsafe autodetect
  demux_audio_open,
  demux_audio_fill_buffer,
  NULL,
  demux_close_audio,
  demux_audio_seek,
  demux_audio_control
};



//4.  djf 20151205 mark :  demuxer 分配空间
demuxer_t *new_demuxer(stream_t *stream, int type, int a_id, int v_id,
                       int s_id, char *filename)
{
    demuxer_t *d = alloc_demuxer(stream, type, filename);
    d->audio = new_demuxer_stream(d, a_id);
    d->video = new_demuxer_stream(d, v_id);
    d->sub = new_demuxer_stream(d, s_id);
    stream->eof = 0;
    stream_seek(stream, stream->start_pos);
    return d;
}


//5. libmpdemux/demux_audio.c 调用具体的函数，读取部分数据并检测mp3的数据头信息
static int demux_audio_open(demuxer_t* demuxer) {
  stream_t *s;
  sh_audio_t* sh_audio;
  uint8_t hdr[HDR_SIZE];
  int frmt = 0, n = 0, step;
  off_t st_pos = 0, next_frame_pos = 0;
  // mp3_hdrs list is sorted first by next_frame_pos and then by frame_pos
  mp3_hdr_t *mp3_hdrs = NULL, *mp3_found = NULL;
  da_priv_t* priv;
  double duration;
  int found_WAVE = 0;

  s = demuxer->stream;

  stream_read(s, hdr, HDR_SIZE);// djf 20151207 mark : 读取数据，若stream->buffer中无数据，会调用stream->fill_buffer()函数先读数据到stream->buffer
  while(n < 30000 && !s->eof) {
    int mp3_freq, mp3_chans, mp3_flen, mpa_layer, mpa_spf, mpa_br;
    st_pos = stream_tell(s) - HDR_SIZE;
    step = 1;

    if( hdr[0] == 'R' && hdr[1] == 'I' && hdr[2] == 'F' && hdr[3] == 'F' ) {
      stream_skip(s,4);
      if(s->eof)
	break;
      stream_read(s,hdr,4);
      if(s->eof)
	break;
      if(hdr[0] != 'W' || hdr[1] != 'A' || hdr[2] != 'V'  || hdr[3] != 'E' )
	stream_skip(s,-8);
      else
      // We found wav header. Now we can have 'fmt ' or a mp3 header
      // empty the buffer
	step = 4;
    } else if( hdr[0] == 'I' && hdr[1] == 'D' && hdr[2] == '3' && hdr[3] >= 2 && hdr[3] != 0xff) {
      unsigned int len = id3v2_tag_size(hdr[3], s);
      if(len > 0)
        stream_skip(s,len-10);
      step = 4;
    } else if( found_WAVE && hdr[0] == 'f' && hdr[1] == 'm' && hdr[2] == 't' && hdr[3] == ' ' ) {
      frmt = WAV;
      break;
    } else if((mp3_flen = mp_get_mp3_header(hdr, &mp3_chans, &mp3_freq,
                                &mpa_spf, &mpa_layer, &mpa_br)) > 0) // djf 20151204 mark : 分析mp3数据头
   {
      mp3_found = add_mp3_hdr(&mp3_hdrs, st_pos, mp3_chans, mp3_freq,
                              mpa_spf, mpa_layer, mpa_br, mp3_flen);// djf 20151204 mark : where init mp3_hdrs???
      if (mp3_found) {
        frmt = MP3;
        break;
      }
    } else if( hdr[0] == 'f' && hdr[1] == 'L' && hdr[2] == 'a' && hdr[3] == 'C' ) {
      frmt = fLaC;
      if (!mp3_hdrs || mp3_hdrs->cons_hdrs < 3)
        break;
    }
    found_WAVE = hdr[0] == 'W' && hdr[1] == 'A' && hdr[2] == 'V' && hdr[3] == 'E';
    // Add here some other audio format detection
    if(step < HDR_SIZE)
      memmove(hdr,&hdr[step],HDR_SIZE-step);
    stream_read(s, &hdr[HDR_SIZE - step], step);
    n++;
  }

  free_mp3_hdrs(&mp3_hdrs);

  if(!frmt)
    return 0;

  sh_audio = new_sh_audio(demuxer,0, NULL);//djf 20151207 mark: 新建sh_audio,并关联到demuxer->a_streams[id] = sh;sh->ds = demuxer->audio;

  switch(frmt) {
  case MP3:
    sh_audio->format = (mp3_found->mpa_layer < 3 ? 0x50 : 0x55);
    demuxer->movi_start = mp3_found->frame_pos;
    demuxer->movi_end = s->end_pos;
    next_frame_pos = mp3_found->next_frame_pos;
    sh_audio->audio.dwSampleSize= 0;
    sh_audio->audio.dwScale = mp3_found->mpa_spf;
    sh_audio->audio.dwRate = mp3_found->mp3_freq;
    sh_audio->wf = malloc(sizeof(*sh_audio->wf));
    sh_audio->wf->wFormatTag = sh_audio->format;
    sh_audio->wf->nChannels = mp3_found->mp3_chans;
    sh_audio->wf->nSamplesPerSec = mp3_found->mp3_freq;
    sh_audio->wf->nAvgBytesPerSec = mp3_found->mpa_br * (1000 / 8);
    sh_audio->wf->nBlockAlign = mp3_found->mpa_spf;
    sh_audio->wf->wBitsPerSample = 16;
    sh_audio->wf->cbSize = 0;
    duration = (double) mp3_vbr_frames(s, demuxer->movi_start) * mp3_found->mpa_spf / mp3_found->mp3_freq;
    free(mp3_found);
    mp3_found = NULL;
    if(demuxer->movi_end && (s->flags & MP_STREAM_SEEK) == MP_STREAM_SEEK) {
      if(demuxer->movi_end >= 128) {
        stream_seek(s,demuxer->movi_end-128);
      stream_read(s,hdr,3);
      if(!memcmp(hdr,"TAG",3)) {// djf 2015120 mark : mp3 的ID3V1
	char buf[31];
	uint8_t g;
          demuxer->movi_end -= 128;
	stream_read(s,buf,30);
	buf[30] = '\0';
	demux_info_add(demuxer,"Title",buf);
	stream_read(s,buf,30);
	buf[30] = '\0';
	demux_info_add(demuxer,"Artist",buf);
	stream_read(s,buf,30);
	buf[30] = '\0';
	demux_info_add(demuxer,"Album",buf);
	stream_read(s,buf,4);
	buf[4] = '\0';
	demux_info_add(demuxer,"Year",buf);
	stream_read(s,buf,30);
	buf[30] = '\0';
	demux_info_add(demuxer,"Comment",buf);
	if(buf[28] == 0 && buf[29] != 0) {
	  uint8_t trk = (uint8_t)buf[29];
	  sprintf(buf,"%d",trk);
	  demux_info_add(demuxer,"Track",buf);
	}
	g = stream_read_char(s);
	demux_info_add(demuxer,"Genre",genres[g]);
      }
      }
      if(demuxer->movi_end >= 10) {
      stream_seek(s,demuxer->movi_end-10);
      stream_read(s,hdr,4);
      if(!memcmp(hdr,"3DI",3) && hdr[3] >= 4 && hdr[3] != 0xff) {
        unsigned int len = id3v2_tag_size(hdr[3], s);
        if(len > 0) {
          if(len > demuxer->movi_end - demuxer->movi_start) {
            mp_msg(MSGT_DEMUX,MSGL_WARN,MSGTR_MPDEMUX_AUDIO_BadID3v2TagSize,len);
            len = FFMIN(10,demuxer->movi_end-demuxer->movi_start);
          } else {
            stream_seek(s,demuxer->movi_end-len);
            stream_read(s,hdr,4);
            if(memcmp(hdr,"ID3",3) || hdr[3] < 4 || hdr[3] == 0xff || id3v2_tag_size(hdr[3], s) != len) {
              mp_msg(MSGT_DEMUX,MSGL_WARN,MSGTR_MPDEMUX_AUDIO_DamagedAppendedID3v2Tag);
              len = FFMIN(10,demuxer->movi_end-demuxer->movi_start);
            }
          }
          demuxer->movi_end -= len;
        }
      }
    }
    }
    if (duration && demuxer->movi_end && demuxer->movi_end > demuxer->movi_start) sh_audio->wf->nAvgBytesPerSec = (demuxer->movi_end - demuxer->movi_start) / duration;
    sh_audio->i_bps = sh_audio->wf->nAvgBytesPerSec;
    break;
  case WAV: {
    unsigned int chunk_type;
    unsigned int chunk_size;
    WAVEFORMATEX* w;
    int l;
    l = stream_read_dword_le(s);
    if(l < 16) {
      mp_msg(MSGT_DEMUX,MSGL_ERR,"[demux_audio] Bad wav header length: too short (%d)!!!\n",l);
      l = 16;
    }
    if(l > MAX_WAVHDR_LEN) {
      mp_msg(MSGT_DEMUX,MSGL_ERR,"[demux_audio] Bad wav header length: too long (%d)!!!\n",l);
      l = 16;
    }
    sh_audio->wf = w = malloc(l > sizeof(*w) ? l : sizeof(*w));
    w->wFormatTag = sh_audio->format = stream_read_word_le(s);
    w->nChannels = sh_audio->channels = stream_read_word_le(s);
    w->nSamplesPerSec = sh_audio->samplerate = stream_read_dword_le(s);
    w->nAvgBytesPerSec = stream_read_dword_le(s);
    w->nBlockAlign = stream_read_word_le(s);
    w->wBitsPerSample = stream_read_word_le(s);
    sh_audio->samplesize = (w->wBitsPerSample + 7) / 8;
    w->cbSize = 0;
    sh_audio->i_bps = sh_audio->wf->nAvgBytesPerSec;
    l -= 16;
    if (l >= 2) {
      w->cbSize = stream_read_word_le(s);
      l -= 2;
      if (l < w->cbSize) {
        mp_msg(MSGT_DEMUX,MSGL_ERR,"[demux_audio] truncated extradata (%d < %d)\n",
               l,w->cbSize);
        w->cbSize = l;
      }
      stream_read(s,(char*)(w + 1),w->cbSize);
      l -= w->cbSize;
      if (w->wFormatTag == 0xfffe && w->cbSize >= 22)
          sh_audio->format = av_le2ne16(((WAVEFORMATEXTENSIBLE *)w)->SubFormat);
    }

    if( mp_msg_test(MSGT_DEMUX,MSGL_V) ) print_wave_header(w, MSGL_V);
    if(l)
      stream_skip(s,l);
    do
    {
      chunk_type = stream_read_fourcc(demuxer->stream);
      chunk_size = stream_read_dword_le(demuxer->stream);
      if (chunk_type != mmioFOURCC('d', 'a', 't', 'a'))
        stream_skip(demuxer->stream, chunk_size);
    } while (!s->eof && chunk_type != mmioFOURCC('d', 'a', 't', 'a'));
    demuxer->movi_start = stream_tell(s);
    demuxer->movi_end = chunk_size ? demuxer->movi_start + chunk_size : s->end_pos;
//    printf("wav: %X .. %X\n",(int)demuxer->movi_start,(int)demuxer->movi_end);
    // Check if it contains dts audio
    if((w->wFormatTag == 0x01) && (w->nChannels == 2) && (w->nSamplesPerSec == 44100)) {
	unsigned char buf[16384]; // vlc uses 16384*4 (4 dts frames)
	unsigned int i;
	memset(buf, 0, sizeof(buf));
	stream_read(s, buf, sizeof(buf));
	for (i = 0; i < sizeof(buf) - 5; i += 2) {
	    // DTS, 14 bit, LE
	    if((buf[i] == 0xff) && (buf[i+1] == 0x1f) && (buf[i+2] == 0x00) &&
	       (buf[i+3] == 0xe8) && ((buf[i+4] & 0xfe) == 0xf0) && (buf[i+5] == 0x07)) {
		sh_audio->format = 0x2001;
		mp_msg(MSGT_DEMUX,MSGL_V,"[demux_audio] DTS audio in wav, 14 bit, LE\n");
		break;
	    }
	    // DTS, 14 bit, BE
	    if((buf[i] == 0x1f) && (buf[i+1] == 0xff) && (buf[i+2] == 0xe8) &&
	       (buf[i+3] == 0x00) && (buf[i+4] == 0x07) && ((buf[i+5] & 0xfe) == 0xf0)) {
		sh_audio->format = 0x2001;
		mp_msg(MSGT_DEMUX,MSGL_V,"[demux_audio] DTS audio in wav, 14 bit, BE\n");
		break;
	    }
	    // DTS, 16 bit, BE
	    if((buf[i] == 0x7f) && (buf[i+1] == 0xfe) && (buf[i+2] == 0x80) &&
	       (buf[i+3] == 0x01)) {
		sh_audio->format = 0x2001;
		mp_msg(MSGT_DEMUX,MSGL_V,"[demux_audio] DTS audio in wav, 16 bit, BE\n");
		break;
	    }
	    // DTS, 16 bit, LE
	    if((buf[i] == 0xfe) && (buf[i+1] == 0x7f) && (buf[i+2] == 0x01) &&
	       (buf[i+3] == 0x80)) {
		sh_audio->format = 0x2001;
		mp_msg(MSGT_DEMUX,MSGL_V,"[demux_audio] DTS audio in wav, 16 bit, LE\n");
		break;
	    }
	}
	if (sh_audio->format == 0x2001) {
	    sh_audio->needs_parsing = 1;
	    mp_msg(MSGT_DEMUX,MSGL_DBG2,"[demux_audio] DTS sync offset = %u\n", i);
        }

    }
    stream_seek(s,demuxer->movi_start);
  } break;
  case fLaC:
	    sh_audio->format = mmioFOURCC('f', 'L', 'a', 'C');
	    demuxer->movi_start = stream_tell(s) - 4;
	    demuxer->movi_end = s->end_pos;
	    if (demuxer->movi_end > demuxer->movi_start) {
	      // try to find out approx. bitrate
	      int64_t size = demuxer->movi_end - demuxer->movi_start;
	      int64_t num_samples;
	      int32_t srate;
	      stream_skip(s, 14);
	      srate = stream_read_int24(s) >> 4;
	      num_samples  = stream_read_int24(s) << 16;
	      num_samples |= stream_read_word(s);
	      if (num_samples && srate)
	        sh_audio->i_bps = size * srate / num_samples;
	    }
	    if (sh_audio->i_bps < 1) // guess value to prevent crash
	      sh_audio->i_bps = 64 * 1024;
	    sh_audio->needs_parsing = 1;
//	    get_flac_metadata (demuxer);
	    break;
  }

  priv = malloc(sizeof(da_priv_t));
  priv->frmt = frmt;
  priv->next_pts = 0;
  demuxer->priv = priv;
  demuxer->audio->id = 0;
  demuxer->audio->sh = sh_audio;
  sh_audio->ds = demuxer->audio;
  sh_audio->samplerate = sh_audio->audio.dwRate;

  if(stream_tell(s) != demuxer->movi_start)
  {
    mp_msg(MSGT_DEMUX, MSGL_V, "demux_audio: seeking from 0x%X to start pos 0x%X\n",
            (int)stream_tell(s), (int)demuxer->movi_start);
    stream_seek(s,demuxer->movi_start);
    if (stream_tell(s) != demuxer->movi_start) {
      mp_msg(MSGT_DEMUX, MSGL_V, "demux_audio: seeking failed, now at 0x%X!\n",
              (int)stream_tell(s));
      if (next_frame_pos) {
        mp_msg(MSGT_DEMUX, MSGL_V, "demux_audio: seeking to 0x%X instead\n",
                (int)next_frame_pos);
        stream_seek(s, next_frame_pos);
      }
    }
  }

  mp_msg(MSGT_DEMUX,MSGL_V,"demux_audio: audio data 0x%X - 0x%X  \n",(int)demuxer->movi_start,(int)demuxer->movi_end);

  return DEMUXER_TYPE_AUDIO;
}