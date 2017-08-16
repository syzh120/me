mpctx->stream  = open_stream(filename, 0, &mpctx->file_format);// djf 20151202 mark : 打开音视频流


// stream/open.c
stream_t* open_stream(const char* filename,char** options, int* file_format){
  int dummy = DEMUXER_TYPE_UNKNOWN;
  if (!file_format) file_format = &dummy;
  // Check if playlist or unknown
  if (*file_format != DEMUXER_TYPE_PLAYLIST){
    *file_format=DEMUXER_TYPE_UNKNOWN;
  }

if(!filename) {
   mp_msg(MSGT_OPEN,MSGL_ERR,"NULL filename, report this bug\n");
   return NULL;
}

//============ Open STDIN or plain FILE ============

  return open_stream_full(filename,STREAM_READ,options,file_format);
}


// stream/stream.c
stream_t* open_stream_full(const char* filename,int mode, char** options, int* file_format) {
  int i,j,l,r;
  const stream_info_t* sinfo;
  stream_t* s;
  char *redirected_url = NULL;

  for(i = 0 ; auto_open_streams[i] ; i++) {
    sinfo = auto_open_streams[i];//djf 20151205 mark： 支持的所有协议,此协议应该是文件的传输协议，与文件的编解码协议不同
    if(!sinfo->protocols) {
      mp_msg(MSGT_OPEN,MSGL_WARN, MSGTR_StreamProtocolNULL, sinfo->name);
      continue;
    }
    for(j = 0 ; sinfo->protocols[j] ; j++) {
      l = strlen(sinfo->protocols[j]);
      // l == 0 => Don't do protocol matching (ie network and filenames)
      if((l == 0 && !strstr(filename, "://")) ||
         ((strncasecmp(sinfo->protocols[j],filename,l) == 0) &&
		      (strncmp("://",filename+l,3) == 0))) {
	*file_format = DEMUXER_TYPE_UNKNOWN;
	s = open_stream_plugin(sinfo,filename,mode,options,file_format,&r,
				&redirected_url); //djf 20151203 mark : open stream
	if(s) return s;
	if(r == STREAM_REDIRECTED && redirected_url) {
	  mp_msg(MSGT_OPEN,MSGL_V, "[%s] open %s redirected to %s\n",
		 sinfo->info, filename, redirected_url);
	  s = open_stream_full(redirected_url, mode, options, file_format);
	  free(redirected_url);
	  return s;
	}
	else if(r != STREAM_UNSUPPORTED) {
	  mp_msg(MSGT_OPEN,MSGL_ERR, MSGTR_FailedToOpen,filename);
	  return NULL;
	}
	break;
      }
    }
  }

  mp_msg(MSGT_OPEN,MSGL_ERR, MSGTR_StreamCantHandleURL,filename);
  return NULL;
}

static stream_t* open_stream_plugin(const stream_info_t* sinfo, const char* filename,
                                    int mode, char** options, int* file_format,
                                    int* ret, char** redirected_url)
{
  void* arg = NULL;
  stream_t* s;
  m_struct_t* desc = (m_struct_t*)sinfo->opts;

  // Parse options
  if(desc) {
    arg = m_struct_alloc(desc);
    if(sinfo->opts_url) {
      m_option_t url_opt =
	{ "stream url", arg , CONF_TYPE_CUSTOM_URL, 0, 0 ,0, sinfo->opts };
      if(m_option_parse(&url_opt,"stream url",filename,arg,M_CONFIG_FILE) < 0) {
	mp_msg(MSGT_OPEN,MSGL_ERR, MSGTR_URLParsingFailed,filename);
	m_struct_free(desc,arg);
	return NULL;
      }
    }
    if(options) {
      int i;
      for(i = 0 ; options[i] != NULL ; i += 2) {
	mp_msg(MSGT_OPEN,MSGL_DBG2, "Set stream arg %s=%s\n",
	       options[i],options[i+1]);
	if(!m_struct_set(desc,arg,options[i],options[i+1]))
	  mp_msg(MSGT_OPEN,MSGL_WARN, MSGTR_FailedSetStreamOption,
		 options[i],options[i+1]);
      }
    }
  }
  s = new_stream(-2,-2);
  s->capture_file = NULL;
  s->url=strdup(filename);
  s->flags |= mode;
  *ret = sinfo->open(s,mode,arg,file_format);// djf 20151203 mark : open stream
  if((*ret) != STREAM_OK) {
#ifdef CONFIG_NETWORKING
    if (*ret == STREAM_REDIRECTED && redirected_url) {
        if (s->streaming_ctrl && s->streaming_ctrl->url
            && s->streaming_ctrl->url->url)
          *redirected_url = strdup(s->streaming_ctrl->url->url);
        else
          *redirected_url = NULL;
    }
    streaming_ctrl_free(s->streaming_ctrl);
#endif
    free(s->url);
    free(s);
    return NULL;
  }
  if(s->type <= -2)
    mp_msg(MSGT_OPEN,MSGL_WARN, MSGTR_StreamNeedType);
  if(s->flags & MP_STREAM_SEEK && !s->seek)
    s->flags &= ~MP_STREAM_SEEK;
  if(s->seek && !(s->flags & MP_STREAM_SEEK))
    s->flags |= MP_STREAM_SEEK;

  s->mode = mode;

  mp_msg(MSGT_OPEN,MSGL_V, "STREAM: [%s] %s\n",sinfo->name,filename);
  mp_msg(MSGT_OPEN,MSGL_V, "STREAM: Description: %s\n",sinfo->info);
  mp_msg(MSGT_OPEN,MSGL_V, "STREAM: Author: %s\n", sinfo->author);
  mp_msg(MSGT_OPEN,MSGL_V, "STREAM: Comment: %s\n", sinfo->comment);

  return s;
}

static const stream_info_t* const auto_open_streams[] = {//djf 20151205 mark： 支持的所有协议,此协议应该是文件的传输协议，与文件的编解码协议不同
  &stream_info_bd,
#ifdef CONFIG_VCD
  &stream_info_vcd,
#endif
#ifdef CONFIG_CDDA
  &stream_info_cdda,
#endif
#ifdef CONFIG_NETWORKING
  &stream_info_netstream,
  &stream_info_http1,
  &stream_info_asf,
  &stream_info_pnm,
  &stream_info_rtsp,
#ifdef CONFIG_LIVE555
  &stream_info_sdp,
  &stream_info_rtsp_sip,
#endif
  &stream_info_rtp,
  &stream_info_udp,
  &stream_info_http2,
#endif
#ifdef CONFIG_DVBIN
  &stream_info_dvb,
#endif
#ifdef CONFIG_TV
  &stream_info_tv,
#endif
#ifdef CONFIG_RADIO
  &stream_info_radio,
#endif
#ifdef CONFIG_PVR
  &stream_info_pvr,
#endif
#ifdef CONFIG_FTP
  &stream_info_ftp,
#endif
#ifdef CONFIG_VSTREAM
  &stream_info_vstream,
#endif
#ifdef CONFIG_LIBSMBCLIENT
  &stream_info_smb,
#endif
  &stream_info_cue,
#ifdef CONFIG_DVDREAD
  &stream_info_ifo,
  &stream_info_dvd,
#endif
#ifdef CONFIG_DVDNAV
  &stream_info_dvdnav,
#endif
#ifdef CONFIG_LIBBLURAY
  &stream_info_bluray,
#endif
#ifdef CONFIG_FFMPEG
  &stream_info_ffmpeg,
#endif

  &stream_info_null,
  &stream_info_mf,
  &stream_info_file,// djf 20151205 mark : open local file
  NULL
};


//stream/stream_file.c 以打开本地文件为例
const stream_info_t stream_info_file = {
  "File",
  "file",
  "Albeu",
  "based on the code from ??? (probably Arpi)",
  open_f,// djf 20151205 mark : open 函数　open_stream_plugin()中调用: *ret = sinfo->open(s,mode,arg,file_format);// djf 20151203 mark : open stream
  { "file", "", NULL },
  &stream_opts,
  1 // Urls are an option string
};

static int open_f(stream_t *stream,int mode, void* opts, int* file_format) {
  int f;
  mode_t m = 0;
  off_t len;
  unsigned char *filename;
  struct stream_priv_s* p = (struct stream_priv_s*)opts;

  if(mode == STREAM_READ)
    m = O_RDONLY;
  else if(mode == STREAM_WRITE)
    m = O_RDWR|O_CREAT|O_TRUNC;
  else {
    mp_msg(MSGT_OPEN,MSGL_ERR, "[file] Unknown open mode %d\n",mode);
    m_struct_free(&stream_opts,opts);
    return STREAM_UNSUPPORTED;
  }

  if(p->filename)
    filename = p->filename;
  else if(p->filename2)
    filename = p->filename2;
  else
    filename = NULL;
  if(!filename) {
    mp_msg(MSGT_OPEN,MSGL_ERR, "[file] No filename\n");
    m_struct_free(&stream_opts,opts);
    return STREAM_ERROR;
  }

#if HAVE_DOS_PATHS
  // extract '/' from '/x:/path'
  if( filename[ 0 ] == '/' && filename[ 1 ] && filename[ 2 ] == ':' )
    filename++;
#endif

  m |= O_BINARY;

  if(!strcmp(filename,"-")){
    if(mode == STREAM_READ) {
      // read from stdin
      mp_msg(MSGT_OPEN,MSGL_INFO,MSGTR_ReadSTDIN);
      f=0; // 0=stdin
#if HAVE_SETMODE
      setmode(fileno(stdin),O_BINARY);
#endif
    } else {
      mp_msg(MSGT_OPEN,MSGL_INFO,"Writing to stdout\n");
      f=1;
#if HAVE_SETMODE
      setmode(fileno(stdout),O_BINARY);
#endif
    }
  } else {
      mode_t openmode = S_IRUSR|S_IWUSR;
#ifndef __MINGW32__
      openmode |= S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH;
#endif
      f=open(filename,m, openmode);
    if(f<0) {
      mp_msg(MSGT_OPEN,MSGL_ERR,MSGTR_FileNotFound,filename);
      m_struct_free(&stream_opts,opts);
      return STREAM_ERROR;
    }
  }

  len=lseek(f,0,SEEK_END); lseek(f,0,SEEK_SET);
#ifdef __MINGW32__
  // seeks on stdin incorrectly succeed on MinGW
  if(f==0)
    len = -1;
#endif
  if(len == -1) {
    if(mode == STREAM_READ) stream->seek = seek_forward;
    stream->type = STREAMTYPE_STREAM; // Must be move to STREAMTYPE_FILE
    stream->flags |= MP_STREAM_SEEK_FW;
  } else if(len >= 0) {
    stream->seek = seek;
    stream->end_pos = len;
    stream->type = STREAMTYPE_FILE;
  }

  mp_msg(MSGT_OPEN,MSGL_V,"[file] File size is %"PRId64" bytes\n", (int64_t)len);

  stream->fd = f;
  stream->fill_buffer = fill_buffer;
  stream->write_buffer = write_buffer;
  stream->control = control;
  stream->read_chunk = 64*1024;

  m_struct_free(&stream_opts,opts);
  return STREAM_OK;
}
//至此，main函数中的 mpctx->stream 初始化基本完成，包含有stream的操作函数及信息描述等信息。

