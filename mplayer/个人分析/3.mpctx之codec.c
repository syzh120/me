//================ SETUP AUDIO ==========================

        if (mpctx->sh_audio) {
            reinit_audio_chain();// djf 20151207 mark  : 初始化音频解码器及输出设备
            if (mpctx->sh_audio && mpctx->sh_audio->codec)
                mp_msg(MSGT_IDENTIFY, MSGL_INFO, "ID_AUDIO_CODEC=%s\n", mpctx->sh_audio->codec->name);
        }


void reinit_audio_chain(void)
{
    if (!mpctx->sh_audio)
        return;
    if (!(initialized_flags & INITIALIZED_ACODEC)) {
        current_module = "init_audio_codec";
        mp_msg(MSGT_CPLAYER, MSGL_INFO, "==========================================================================\n");
        if (!init_best_audio_codec(mpctx->sh_audio, audio_codec_list, audio_fm_list))//djf 20151207 mark : 初始化软件codec 1.
            goto init_error;
        initialized_flags |= INITIALIZED_ACODEC;
        mp_msg(MSGT_CPLAYER, MSGL_INFO, "==========================================================================\n");
    }

    if (!(initialized_flags & INITIALIZED_AO)) {
        current_module     = "af_preinit";
        ao_data.samplerate = force_srate;
        ao_data.channels   = 0;
        ao_data.format     = audio_output_format;
        // first init to detect best values
        if (!init_audio_filters(mpctx->sh_audio,  // preliminary init
                                // input:
                                mpctx->sh_audio->samplerate,
                                // output:
                                &ao_data.samplerate, &ao_data.channels, &ao_data.format)) {// djf 20151207 mark  : 初始化过滤器 2. 
            mp_msg(MSGT_CPLAYER, MSGL_ERR, MSGTR_AudioFilterChainPreinitError);
            exit_player(EXIT_ERROR);
        }
        current_module   = "ao2_init";
        mpctx->audio_out = init_best_audio_out(audio_driver_list,
                                               0, // plugin flag
                                               ao_data.samplerate,
                                               ao_data.channels,
                                               ao_data.format, 0);//djf 20151209 mark : 初始化硬件codec 3.
        if (!mpctx->audio_out) {
            mp_msg(MSGT_CPLAYER, MSGL_ERR, MSGTR_CannotInitAO);
            goto init_error;
        }
        initialized_flags |= INITIALIZED_AO;
        mp_msg(MSGT_CPLAYER, MSGL_INFO, "AO: [%s] %dHz %dch %s (%d bytes per sample)\n",
               mpctx->audio_out->info->short_name,
               ao_data.samplerate, ao_data.channels,
               af_fmt2str_short(ao_data.format),
               af_fmt2bits(ao_data.format) / 8);
        mp_msg(MSGT_CPLAYER, MSGL_V, "AO: Description: %s\nAO: Author: %s\n",
               mpctx->audio_out->info->name, mpctx->audio_out->info->author);
        if (strlen(mpctx->audio_out->info->comment) > 0)
            mp_msg(MSGT_CPLAYER, MSGL_V, "AO: Comment: %s\n", mpctx->audio_out->info->comment);
    }

    // init audio filters:
    current_module = "af_init";
    if (!build_afilter_chain(mpctx->sh_audio, &ao_data)) {
        mp_msg(MSGT_CPLAYER, MSGL_ERR, MSGTR_NoMatchingFilter);
        goto init_error;
    }
    mpctx->mixer.audio_out = mpctx->audio_out;
    mpctx->mixer.volstep   = volstep;
    return;

init_error:
    uninit_player(INITIALIZED_ACODEC | INITIALIZED_AO); // close codec and possibly AO
    mpctx->sh_audio    = mpctx->d_audio->sh = NULL; // -> nosound
    mpctx->d_audio->id = -2;
}




//1.djf 20151207 mark : 初始化软件codec
int init_best_audio_codec(sh_audio_t *sh_audio, char **audio_codec_list,
			  char **audio_fm_list)
{
    stringset_t selected;
    char *ac_l_default[2] = { "", (char *) NULL };
    // hack:
    if (!audio_codec_list)
	audio_codec_list = ac_l_default;
    // Go through the codec.conf and find the best codec...
    sh_audio->initialized = 0;
    stringset_init(&selected);
    while (!sh_audio->initialized && *audio_codec_list) {
	char *audio_codec = *(audio_codec_list++);
	if (audio_codec[0]) {
	    if (audio_codec[0] == '-') {
		// disable this codec:
		stringset_add(&selected, audio_codec + 1);
	    } else {
		// forced codec by name:
		mp_msg(MSGT_DECAUDIO, MSGL_INFO, MSGTR_ForcedAudioCodec,
		       audio_codec);
		init_audio(sh_audio, audio_codec, NULL, -1, &selected);
	    }
	} else {
	    int status;
	    // try in stability order: UNTESTED, WORKING, BUGGY.
	    // never try CRASHING.
	    if (audio_fm_list) {
		char **fmlist = audio_fm_list;
		// try first the preferred codec families:
		while (!sh_audio->initialized && *fmlist) {
		    char *audio_fm = *(fmlist++);
		    mp_msg(MSGT_DECAUDIO, MSGL_INFO, MSGTR_TryForceAudioFmtStr,
			   audio_fm);
		    for (status = CODECS_STATUS__MAX;
			 status >= CODECS_STATUS__MIN; --status)
			if (init_audio(sh_audio, NULL, audio_fm, status, &selected))
			    break;
		}
	    }
	    if (!sh_audio->initialized)
		for (status = CODECS_STATUS__MAX; status >= CODECS_STATUS__MIN;
		     --status)
		    if (init_audio(sh_audio, NULL, NULL, status, &selected))// djf 20151217 mark : 初始化软件codec 1.1
			break;
	}
    }
    stringset_free(&selected);

    if (!sh_audio->initialized) {
	mp_msg(MSGT_DECAUDIO, MSGL_ERR, MSGTR_CantFindAudioCodec,
	       sh_audio->format);
	return 0;   // failed
    }

    mp_msg(MSGT_DECAUDIO, MSGL_INFO, MSGTR_SelectedAudioCodec,
	   sh_audio->codec->name, sh_audio->codec->drv, sh_audio->codec->info);
    return 1;   // success
}

//1.1 djf 20151217 mark : 初始化软件codec
static int init_audio(sh_audio_t *sh_audio, char *codecname, char *afm,
		      int status, stringset_t *selected)
{
    unsigned int orig_fourcc = sh_audio->wf ? sh_audio->wf->wFormatTag : 0;// djf 20151207 mark : sh_audio->wf->wFormatTag=0x50 或 0x55
    int force = 0;
    if (codecname && codecname[0] == '+') {
	codecname = &codecname[1];
	force = 1;
    }
    sh_audio->codec = NULL;
    while (1) {
	const ad_functions_t *mpadec;
	int i;
	sh_audio->ad_driver = 0;
	// restore original fourcc:
	if (sh_audio->wf)
	    sh_audio->wf->wFormatTag = i = orig_fourcc;
	if (!(sh_audio->codec = find_audio_codec(sh_audio->format,
						 sh_audio->wf ? (&i) : NULL,
						 sh_audio->codec, force))) //djf 20151208 mark: 根据sh_audio->format 匹配对应sh_audio->codec 1.1.1
	    break;
	if (sh_audio->wf)
	    sh_audio->wf->wFormatTag = i;
	// ok we found one codec
	if (stringset_test(selected, sh_audio->codec->name))
	    continue;	// already tried & failed
	if (codecname && strcmp(sh_audio->codec->name, codecname))
	    continue;	// -ac
	if (afm && strcmp(sh_audio->codec->drv, afm))
	    continue;	// afm doesn't match
	if (!force && sh_audio->codec->status < status)
	    continue;	// too unstable
	stringset_add(selected, sh_audio->codec->name);	// tagging it
	// ok, it matches all rules, let's find the driver!
	for (i = 0; mpcodecs_ad_drivers[i] != NULL; i++)
	    if (!strcmp(mpcodecs_ad_drivers[i]->info->short_name,//1.1.2
		 sh_audio->codec->drv))// djf 20151208 mark : 根据sh_audio->codec->drv  匹配mpcodecs_ad_drivers[]数组,mp3的drv=mp3lib; 另外ad_mp3lib.c 中定义了 mpcodecs_ad_mp3lib (见LIBAD_EXTERN(mp3lib))
		break;
	mpadec = mpcodecs_ad_drivers[i];//djf 20151208 mark:mp3 则为 mpcodecs_ad_mp3lib 在 ad_mp3lib.c 中定义
#ifdef CONFIG_DYNAMIC_PLUGINS
	if (!mpadec) {
	    /* try to open shared decoder plugin */
	    int buf_len;
	    char *buf;
	    ad_functions_t *funcs_sym;
	    ad_info_t *info_sym;

	    buf_len =
		strlen(MPLAYER_LIBDIR) + strlen(sh_audio->codec->drv) + 16;
	    buf = malloc(buf_len);
	    if (!buf)
		break;
	    snprintf(buf, buf_len, "%s/mplayer/ad_%s.so", MPLAYER_LIBDIR,
		     sh_audio->codec->drv);
	    mp_msg(MSGT_DECAUDIO, MSGL_DBG2,
		   "Trying to open external plugin: %s\n", buf);
	    sh_audio->dec_handle = dlopen(buf, RTLD_LAZY);
	    if (!sh_audio->dec_handle)
		break;
	    snprintf(buf, buf_len, "mpcodecs_ad_%s", sh_audio->codec->drv);
	    funcs_sym = dlsym(sh_audio->dec_handle, buf);
	    if (!funcs_sym || !funcs_sym->info || !funcs_sym->preinit
		|| !funcs_sym->init || !funcs_sym->uninit
		|| !funcs_sym->control || !funcs_sym->decode_audio)
		break;
	    info_sym = funcs_sym->info;
	    if (strcmp(info_sym->short_name, sh_audio->codec->drv))
		break;
	    free(buf);
	    mpadec = funcs_sym;
	    mp_msg(MSGT_DECAUDIO, MSGL_V,
		   "Using external decoder plugin (%s/mplayer/ad_%s.so)!\n",
		   MPLAYER_LIBDIR, sh_audio->codec->drv);
	}
#endif
	if (!mpadec) {		// driver not available (==compiled in)
	    mp_msg(MSGT_DECAUDIO, MSGL_ERR,
		   MSGTR_AudioCodecFamilyNotAvailableStr,
		   sh_audio->codec->name, sh_audio->codec->drv);
	    continue;
	}
	// it's available, let's try to init!
	// init()
	mp_msg(MSGT_DECAUDIO, MSGL_INFO, MSGTR_OpeningAudioDecoder,
	       mpadec->info->short_name, mpadec->info->name);
	sh_audio->ad_driver = mpadec;
	if (!init_audio_codec(sh_audio)) {
	    mp_msg(MSGT_DECAUDIO, MSGL_INFO, MSGTR_ADecoderInitFailed);
	    continue;		// try next...
	}
	// Yeah! We got it!
	return 1;
    }
    return 0;
}


//1.1.1 djf 20151208 mark: 根据sh_audio->format 匹配对应sh_audio->codec
codecs_t *find_audio_codec(unsigned int fourcc, unsigned int *fourccmap,
                           codecs_t *start, int force)
{
    return find_codec(fourcc, fourccmap, start, 1, force);
}

codecs_t* find_codec(unsigned int fourcc,unsigned int *fourccmap,
                     codecs_t *start, int audioflag, int force)
{
    int i, j;
    codecs_t *c;

#if 0
    if (start) {
        for (/* NOTHING */; start->name; start++) {
            for (j = 0; j < CODECS_MAX_FOURCC; j++) {
                if (start->fourcc[j] == fourcc) {
                    if (fourccmap)
                        *fourccmap = start->fourccmap[j];
                    return start;
                }
            }
        }
    } else
#endif
    {
        if (audioflag) {
            i = nr_acodecs;// djf 20151207 mark : nr_acodecs 在哪里赋值的?nr_acodecs = sizeof(builtin_audio_codecs)/sizeof(codecs_t);
            c = audio_codecs;// djf 20151208 mark : codecs.conf.h 中定义的builtin_audio_codecs 具体mp3如下：1.1.1.1
        } else {
            i = nr_vcodecs;
            c = video_codecs;
        }
        if(!i) return NULL;
        for (/* NOTHING */; i--; c++) {
            if(start && c<=start) continue;
            for (j = 0; j < CODECS_MAX_FOURCC; j++) {
                // FIXME: do NOT hardwire 'null' name here:
                if (c->fourcc[j]==fourcc || !strcmp(c->drv,"null")) {// djf 20151208 mark: fourcc为0x50 或0x55 ,如果为mp3的话
                    if (fourccmap)
                        *fourccmap = c->fourccmap[j];
                    return c;
                }
            }
            if (force) return c;
        }
    }
    return NULL;
}

// djf 20151208 mark : codecs.conf.h 中定义的builtin_audio_codecs 具体mp3如下：1.1.1.1
{{ 80, 85, 0x5500736D, 0x5000736D, 0x55005354, 0x33706D2E, 0x2033504D, 0x454D414C, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, /* fourcc */
{ 80, 85, 0x5500736D, 0x5000736D, 0x55005354, 0x33706D2E, 0x2033504D, 0x454D414C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* fourccmap */
{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, /* outfmt */
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* outflags */
{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, /* infmt */
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* inflags */
"mp3", /* name */
"mp3lib MPEG layer-2, layer-3", /* info */
"Barely maintained, miscompiles with newer gcc versions", /* comment */
NULL, /* dll */
"mp3lib", /* drv */
{ 0x00000000, 0, 0,{ 0, 0, 0, 0, 0, 0, 0, 0 } }, /* GUID */
0 /* flags */, 0 /* status */, 0 /* cpuflags */ }




//1.1.2 djf 20151208 mark : 根据sh_audio->codec->drv  匹配mpcodecs_ad_drivers[]数组,mp3的drv=mp3lib; 另外ad_mp3lib.c 中定义了 mpcodecs_ad_mp3lib (见LIBAD_EXTERN(mp3lib))
const ad_functions_t * const mpcodecs_ad_drivers[] =
{
#ifdef CONFIG_MPG123
  &mpcodecs_ad_mpg123,
#endif
#ifdef CONFIG_MP3LIB
  &mpcodecs_ad_mp3lib, //djf 20151217 mark: mp3用
#endif
#ifdef CONFIG_LIBA52
  &mpcodecs_ad_liba52,
#endif
  &mpcodecs_ad_hwac3,
  &mpcodecs_ad_hwmpa,
#ifdef CONFIG_FFMPEG
  &mpcodecs_ad_ffmpeg,
  &mpcodecs_ad_spdif,
#endif
  &mpcodecs_ad_pcm,
  &mpcodecs_ad_dvdpcm,
  &mpcodecs_ad_alaw,
  &mpcodecs_ad_imaadpcm,
  &mpcodecs_ad_msadpcm,
  &mpcodecs_ad_dk3adpcm,
#ifdef CONFIG_WIN32DLL
  &mpcodecs_ad_dshow,
  &mpcodecs_ad_dmo,
  &mpcodecs_ad_acm,
  &mpcodecs_ad_twin,
#endif
#ifdef CONFIG_QTX_CODECS
  &mpcodecs_ad_qtaudio,
#endif
#ifdef CONFIG_FAAD
  &mpcodecs_ad_faad,
#endif
#ifdef CONFIG_OGGVORBIS
  &mpcodecs_ad_libvorbis,
#endif
#ifdef CONFIG_SPEEX
  &mpcodecs_ad_speex,
#endif
#ifdef CONFIG_LIBMAD
  &mpcodecs_ad_libmad,
#endif
#ifdef CONFIG_REALCODECS
  &mpcodecs_ad_realaud,
#endif
#ifdef CONFIG_LIBDV095
  &mpcodecs_ad_libdv,
#endif
#ifdef CONFIG_MUSEPACK
  &mpcodecs_ad_libmusepack,
#endif
#ifdef CONFIG_LIBDCA
  &mpcodecs_ad_libdca,
#endif
  NULL
};

//djf 20151217 mark: mp3用
LIBAD_EXTERN(mp3lib)
#define LIBAD_EXTERN(x) const ad_functions_t mpcodecs_ad_##x = {\
	&info,\
	preinit,\
	init,\
  uninit,\
	control,\
	decode_audio\
};




//2. djf 20151207 mark  : 初始化过滤器

int init_audio_filters(sh_audio_t *sh_audio, int in_samplerate,
		       int *out_samplerate, int *out_channels, int *out_format)
{
    af_stream_t *afs = sh_audio->afilter;
    if (!afs) {
	afs = malloc(sizeof(af_stream_t));
	memset(afs, 0, sizeof(af_stream_t));
    }
    // input format: same as codec's output format:
    afs->input.rate   = in_samplerate;
    afs->input.nch    = sh_audio->channels;
    afs->input.format = sh_audio->sample_format;
    af_fix_parameters(&(afs->input));

    // output format: same as ao driver's input format (if missing, fallback to input)
    afs->output.rate   = *out_samplerate;
    afs->output.nch    = *out_channels;
    afs->output.format = *out_format;
    af_fix_parameters(&(afs->output));

    // filter config:
    memcpy(&afs->cfg, &af_cfg, sizeof(af_cfg_t));

    mp_msg(MSGT_DECAUDIO, MSGL_V,
           "Building audio filter chain for %dHz/%dch/%s -> %dHz/%dch/%s...\n",
	   afs->input.rate, afs->input.nch,
	   af_fmt2str_short(afs->input.format), afs->output.rate,
	   afs->output.nch, af_fmt2str_short(afs->output.format));

    // let's autoprobe it!
    if (0 != af_init(afs)) {
	sh_audio->afilter = NULL;
	free(afs);
	return 0;   // failed :(
    }

    *out_samplerate = afs->output.rate;
    *out_channels = afs->output.nch;
    *out_format = afs->output.format;

    // Do not reset a_out_buffer_len. This may cause some
    // glitches/slow adaption of changes but it is better than
    // losing audio even for minor adjustments and avoids sync issues.

    // ok!
    sh_audio->afilter = (void *) afs;
    return 1;
}





//3. djf 20151209 mark : 初始化硬件codec 
const ao_functions_t* init_best_audio_out(char** ao_list,int use_plugin,int rate,int channels,int format,int flags){
    int i;
    // first try the preferred drivers, with their optional subdevice param:
    if(ao_list && ao_list[0])
      while(ao_list[0][0]){
        char* ao=ao_list[0];
        int ao_len;
        if (strncmp(ao, "alsa9", 5) == 0 || strncmp(ao, "alsa1x", 6) == 0) {
            mp_msg(MSGT_AO, MSGL_FATAL, MSGTR_AO_ALSA9_1x_Removed);
            exit_player(EXIT_NONE);
        }
        free(ao_subdevice);
        ao_subdevice = NULL;
        ao_subdevice=strchr(ao,':');
        if(ao_subdevice){
            ao_len = ao_subdevice - ao;
            ao_subdevice = strdup(&ao[ao_len + 1]);
        }
        else
            ao_len = strlen(ao);

        mp_msg(MSGT_AO, MSGL_V, "Trying preferred audio driver '%.*s', options '%s'\n",
               ao_len, ao, ao_subdevice ? ao_subdevice : "[none]");

        for(i=0;audio_out_drivers[i];i++){
            const ao_functions_t* audio_out=audio_out_drivers[i];
            if(!strncmp(audio_out->info->short_name,ao,ao_len)){
                // name matches, try it
                if(audio_out->init(rate,channels,format,flags))
                    return audio_out; // success!
                else
                    mp_msg(MSGT_AO, MSGL_WARN, MSGTR_AO_FailedInit, ao);
                break;
            }
        }
	if (!audio_out_drivers[i]) // we searched through the entire list
            mp_msg(MSGT_AO, MSGL_WARN, MSGTR_AO_NoSuchDriver, ao_len, ao);
        // continue...
        ++ao_list;
        if(!(ao_list[0])) return NULL; // do NOT fallback to others
      }
    free(ao_subdevice);
    ao_subdevice = NULL;

    mp_msg(MSGT_AO, MSGL_V, "Trying every known audio driver...\n");

    // now try the rest...
    for(i=0;audio_out_drivers[i];i++){ 
        const ao_functions_t* audio_out=audio_out_drivers[i];//djf 20151217 mark : 3.1
//        if(audio_out->control(AOCONTROL_QUERY_FORMAT, (int)format) == CONTROL_TRUE)
        if(audio_out->init(rate,channels,format,flags))//djf 0151217 mark : 初始化硬件codec
            return audio_out; // success!
    }
    return NULL;
}

//djf 20151217 mark : 3.1
const ao_functions_t* const audio_out_drivers[] =
{
// native:
#ifdef CONFIG_DIRECTX
        &audio_out_dsound,
#endif
#ifdef CONFIG_WIN32WAVEOUT
        &audio_out_win32,
#endif
#ifdef CONFIG_KAI
        &audio_out_kai,
#endif
#ifdef CONFIG_DART
        &audio_out_dart,
#endif
#ifdef CONFIG_COREAUDIO
        &audio_out_coreaudio,
#endif
#ifdef CONFIG_OSS_AUDIO
        &audio_out_oss,
#endif
#ifdef CONFIG_ALSA
        &audio_out_alsa,//djf 0151217 mark: linux 应该使用这里
#endif
#ifdef CONFIG_SGI_AUDIO
        &audio_out_sgi,
#endif
#ifdef CONFIG_SUN_AUDIO
        &audio_out_sun,
#endif
// wrappers:
#ifdef CONFIG_ARTS
        &audio_out_arts,
#endif
#ifdef CONFIG_ESD
        &audio_out_esd,
#endif
#ifdef CONFIG_PULSE
        &audio_out_pulse,
#endif
#ifdef CONFIG_JACK
        &audio_out_jack,
#endif
#ifdef CONFIG_NAS
        &audio_out_nas,
#endif
#ifdef CONFIG_SDL
        &audio_out_sdl,
#endif
#ifdef CONFIG_OPENAL
        &audio_out_openal,
#endif
        &audio_out_mpegpes,
#ifdef CONFIG_DXR2
        &audio_out_dxr2,
#endif
#ifdef CONFIG_IVTV
        &audio_out_ivtv,
#endif
#ifdef CONFIG_V4L2_DECODER
        &audio_out_v4l2,
#endif
        &audio_out_null,
// should not be auto-selected:
        &audio_out_pcm,
        NULL
};

//djf 0151217 mark: linux 应该使用这里
LIBAO_EXTERN(alsa) //djf 20151205 mark : alsa codec 定义: audio_out_alsa /libao2/ao_alsa.c
#define LIBAO_EXTERN(x) const ao_functions_t audio_out_##x =\
{\
	&info,\
	control,\
	init,\
  uninit,\
	reset,\
	get_space,\
	play,\
	get_delay,\
	audio_pause,\
	audio_resume\
};

//djf 0151217 mark : 初始化硬件codec
static int init(int rate_hz, int channels, int format, int flags)
{
    unsigned int alsa_buffer_time = 500000; /* 0.5 s */
    unsigned int alsa_fragcount = 16;
    int err;
    int block;
    strarg_t device;
    snd_pcm_uframes_t chunk_size;
    snd_pcm_uframes_t bufsize;
    snd_pcm_uframes_t boundary;
    const opt_t subopts[] = {
      {"block", OPT_ARG_BOOL, &block, NULL},
      {"device", OPT_ARG_STR, &device, str_maxlen},
      {NULL}
    };

    char alsa_device[ALSA_DEVICE_SIZE + 1];
    // make sure alsa_device is null-terminated even when using strncpy etc.
    memset(alsa_device, 0, ALSA_DEVICE_SIZE + 1);

    mp_msg(MSGT_AO,MSGL_V,"alsa-init: requested format: %d Hz, %d channels, %x\n", rate_hz,
	channels, format);
    alsa_handler = NULL;
#if SND_LIB_VERSION >= 0x010005
    mp_msg(MSGT_AO,MSGL_V,"alsa-init: using ALSA %s\n", snd_asoundlib_version());
#else
    mp_msg(MSGT_AO,MSGL_V,"alsa-init: compiled for ALSA-%s\n", SND_LIB_VERSION_STR);
#endif

    snd_lib_error_set_handler(alsa_error_handler);

    ao_data.samplerate = rate_hz;
    ao_data.format = format;
    ao_data.channels = channels;

    switch (format)
      {
      case AF_FORMAT_S8:
	alsa_format = SND_PCM_FORMAT_S8;
	break;
      case AF_FORMAT_U8:
	alsa_format = SND_PCM_FORMAT_U8;
	break;
      case AF_FORMAT_U16_LE:
	alsa_format = SND_PCM_FORMAT_U16_LE;
	break;
      case AF_FORMAT_U16_BE:
	alsa_format = SND_PCM_FORMAT_U16_BE;
	break;
      case AF_FORMAT_AC3_LE:
      case AF_FORMAT_S16_LE:
      case AF_FORMAT_IEC61937_LE:
	alsa_format = SND_PCM_FORMAT_S16_LE;
	break;
      case AF_FORMAT_AC3_BE:
      case AF_FORMAT_S16_BE:
      case AF_FORMAT_IEC61937_BE:
	alsa_format = SND_PCM_FORMAT_S16_BE;
	break;
      case AF_FORMAT_U32_LE:
	alsa_format = SND_PCM_FORMAT_U32_LE;
	break;
      case AF_FORMAT_U32_BE:
	alsa_format = SND_PCM_FORMAT_U32_BE;
	break;
      case AF_FORMAT_S32_LE:
	alsa_format = SND_PCM_FORMAT_S32_LE;
	break;
      case AF_FORMAT_S32_BE:
	alsa_format = SND_PCM_FORMAT_S32_BE;
	break;
      case AF_FORMAT_U24_LE:
	alsa_format = SND_PCM_FORMAT_U24_3LE;
	break;
      case AF_FORMAT_U24_BE:
	alsa_format = SND_PCM_FORMAT_U24_3BE;
	break;
      case AF_FORMAT_S24_LE:
	alsa_format = SND_PCM_FORMAT_S24_3LE;
	break;
      case AF_FORMAT_S24_BE:
	alsa_format = SND_PCM_FORMAT_S24_3BE;
	break;
      case AF_FORMAT_FLOAT_LE:
	alsa_format = SND_PCM_FORMAT_FLOAT_LE;
	break;
      case AF_FORMAT_FLOAT_BE:
	alsa_format = SND_PCM_FORMAT_FLOAT_BE;
	break;
      case AF_FORMAT_MU_LAW:
	alsa_format = SND_PCM_FORMAT_MU_LAW;
	break;
      case AF_FORMAT_A_LAW:
	alsa_format = SND_PCM_FORMAT_A_LAW;
	break;

      default:
	alsa_format = SND_PCM_FORMAT_MPEG; //? default should be -1
	break;
      }

    //subdevice parsing
    // set defaults
    block = 1;
    /* switch for spdif
     * sets opening sequence for SPDIF
     * sets also the playback and other switches 'on the fly'
     * while opening the abstract alias for the spdif subdevice
     * 'iec958'
     */
    if (AF_FORMAT_IS_AC3(format) || AF_FORMAT_IS_IEC61937(format)) {
	device.str = "iec958";
	mp_msg(MSGT_AO,MSGL_V,"alsa-spdif-init: playing AC3/iec61937/iec958, %i channels\n", channels);
    }
  else
        /* in any case for multichannel playback we should select
         * appropriate device
         */
        switch (channels) {
	case 1:
	case 2:
	  device.str = "default";
	  mp_msg(MSGT_AO,MSGL_V,"alsa-init: setup for 1/2 channel(s)\n");
	  break;
	case 4:
	  if (alsa_format == SND_PCM_FORMAT_FLOAT_LE)
	    // hack - use the converter plugin
	    device.str = "plug:surround40";
	  else
	    device.str = "surround40";
	  mp_msg(MSGT_AO,MSGL_V,"alsa-init: device set to surround40\n");
	  break;
	case 6:
	  if (alsa_format == SND_PCM_FORMAT_FLOAT_LE)
	    device.str = "plug:surround51";
	  else
	    device.str = "surround51";
	  mp_msg(MSGT_AO,MSGL_V,"alsa-init: device set to surround51\n");
	  break;
	case 8:
	  if (alsa_format == SND_PCM_FORMAT_FLOAT_LE)
	    device.str = "plug:surround71";
	  else
	    device.str = "surround71";
	  mp_msg(MSGT_AO,MSGL_V,"alsa-init: device set to surround71\n");
	  break;
	default:
	  device.str = "default";
	  mp_msg(MSGT_AO,MSGL_ERR,MSGTR_AO_ALSA_ChannelsNotSupported,channels);
        }
    device.len = strlen(device.str);
    if (subopt_parse(ao_subdevice, subopts) != 0) {
        print_help();
        return 0;
    }
    parse_device(alsa_device, device.str, device.len);

    mp_msg(MSGT_AO,MSGL_V,"alsa-init: using device %s\n", alsa_device);

    if (!alsa_handler) {
      int open_mode = block ? 0 : SND_PCM_NONBLOCK;
      int isac3 =  AF_FORMAT_IS_AC3(format) || AF_FORMAT_IS_IEC61937(format);
      //modes = 0, SND_PCM_NONBLOCK, SND_PCM_ASYNC
      mp_msg(MSGT_AO,MSGL_V,"alsa-init: opening device in %sblocking mode\n", block ? "" : "non-");
      if ((err = try_open_device(alsa_device, open_mode, isac3)) < 0)//djf 20151209 mark : 打开PCM
	{
	  if (err != -EBUSY && !block) {
	    mp_msg(MSGT_AO,MSGL_INFO,MSGTR_AO_ALSA_OpenInNonblockModeFailed);
	    if ((err = try_open_device(alsa_device, 0, isac3)) < 0) {
	      mp_msg(MSGT_AO,MSGL_ERR,MSGTR_AO_ALSA_PlaybackOpenError, snd_strerror(err));
	      return 0;
	    }
	  } else {
	    mp_msg(MSGT_AO,MSGL_ERR,MSGTR_AO_ALSA_PlaybackOpenError, snd_strerror(err));
	    return 0;
	  }
	}

      if ((err = snd_pcm_nonblock(alsa_handler, 0)) < 0) {
         mp_msg(MSGT_AO,MSGL_ERR,MSGTR_AO_ALSA_ErrorSetBlockMode, snd_strerror(err));
      } else {
	mp_msg(MSGT_AO,MSGL_V,"alsa-init: device reopened in blocking mode\n");
      }

      snd_pcm_hw_params_alloca(&alsa_hwparams);
      snd_pcm_sw_params_alloca(&alsa_swparams);

      // setting hw-parameters
      if ((err = snd_pcm_hw_params_any(alsa_handler, alsa_hwparams)) < 0)
	{
	  mp_msg(MSGT_AO,MSGL_ERR,MSGTR_AO_ALSA_UnableToGetInitialParameters,
		 snd_strerror(err));
	  return 0;
	}

      err = snd_pcm_hw_params_set_access(alsa_handler, alsa_hwparams,
					 SND_PCM_ACCESS_RW_INTERLEAVED);
      if (err < 0) {
	mp_msg(MSGT_AO,MSGL_ERR,MSGTR_AO_ALSA_UnableToSetAccessType,
	       snd_strerror(err));
	return 0;
      }

      /* workaround for nonsupported formats
	 sets default format to S16_LE if the given formats aren't supported */
      if ((err = snd_pcm_hw_params_test_format(alsa_handler, alsa_hwparams,
                                             alsa_format)) < 0)
      {
         mp_msg(MSGT_AO,MSGL_INFO,
		MSGTR_AO_ALSA_FormatNotSupportedByHardware, af_fmt2str_short(format));
         alsa_format = SND_PCM_FORMAT_S16_LE;
         if (AF_FORMAT_IS_AC3(ao_data.format))
           ao_data.format = AF_FORMAT_AC3_LE;
         else if (AF_FORMAT_IS_IEC61937(ao_data.format))
           ao_data.format = AF_FORMAT_IEC61937_LE;
         else
         ao_data.format = AF_FORMAT_S16_LE;
      }

      if ((err = snd_pcm_hw_params_set_format(alsa_handler, alsa_hwparams,
					      alsa_format)) < 0)
	{
	  mp_msg(MSGT_AO,MSGL_ERR,MSGTR_AO_ALSA_UnableToSetFormat,
		 snd_strerror(err));
	  return 0;
	}

      if ((err = snd_pcm_hw_params_set_channels_near(alsa_handler, alsa_hwparams,
						     &ao_data.channels)) < 0)
	{
	  mp_msg(MSGT_AO,MSGL_ERR,MSGTR_AO_ALSA_UnableToSetChannels,
		 snd_strerror(err));
	  return 0;
	}

      /* workaround for buggy rate plugin (should be fixed in ALSA 1.0.11)
         prefer our own resampler, since that allows users to choose the resampler,
         even per file if desired */
#if SND_LIB_VERSION >= 0x010009
      if ((err = snd_pcm_hw_params_set_rate_resample(alsa_handler, alsa_hwparams,
						     0)) < 0)
	{
	  mp_msg(MSGT_AO,MSGL_ERR,MSGTR_AO_ALSA_UnableToDisableResampling,
		 snd_strerror(err));
	  return 0;
	}
#endif

      if ((err = snd_pcm_hw_params_set_rate_near(alsa_handler, alsa_hwparams,
						 &ao_data.samplerate, NULL)) < 0)
        {
	  mp_msg(MSGT_AO,MSGL_ERR,MSGTR_AO_ALSA_UnableToSetSamplerate2,
		 snd_strerror(err));
	  return 0;
        }

      bytes_per_sample = af_fmt2bits(ao_data.format) / 8;
      bytes_per_sample *= ao_data.channels;
      ao_data.bps = ao_data.samplerate * bytes_per_sample;

	if ((err = snd_pcm_hw_params_set_buffer_time_near(alsa_handler, alsa_hwparams,
							  &alsa_buffer_time, NULL)) < 0)
	  {
	    mp_msg(MSGT_AO,MSGL_ERR,MSGTR_AO_ALSA_UnableToSetBufferTimeNear,
		   snd_strerror(err));
	    return 0;
	  }

	if ((err = snd_pcm_hw_params_set_periods_near(alsa_handler, alsa_hwparams,
						      &alsa_fragcount, NULL)) < 0) {
	  mp_msg(MSGT_AO,MSGL_ERR,MSGTR_AO_ALSA_UnableToSetPeriods,
		 snd_strerror(err));
	  return 0;
	}

      /* finally install hardware parameters */
      if ((err = snd_pcm_hw_params(alsa_handler, alsa_hwparams)) < 0)
	{
	  mp_msg(MSGT_AO,MSGL_ERR,MSGTR_AO_ALSA_UnableToSetHwParameters,
		 snd_strerror(err));
	  return 0;
	}
      // end setting hw-params


      // gets buffersize for control
      if ((err = snd_pcm_hw_params_get_buffer_size(alsa_hwparams, &bufsize)) < 0)
	{
	  mp_msg(MSGT_AO,MSGL_ERR,MSGTR_AO_ALSA_UnableToGetBufferSize, snd_strerror(err));
	  return 0;
	}
      else {
	ao_data.buffersize = bufsize * bytes_per_sample;
	  mp_msg(MSGT_AO,MSGL_V,"alsa-init: got buffersize=%i\n", ao_data.buffersize);
      }

      if ((err = snd_pcm_hw_params_get_period_size(alsa_hwparams, &chunk_size, NULL)) < 0) {
	mp_msg(MSGT_AO,MSGL_ERR,MSGTR_AO_ALSA_UnableToGetPeriodSize, snd_strerror(err));
	return 0;
      } else {
	mp_msg(MSGT_AO,MSGL_V,"alsa-init: got period size %li\n", chunk_size);
      }
      ao_data.outburst = chunk_size * bytes_per_sample;

      /* setting software parameters */
      if ((err = snd_pcm_sw_params_current(alsa_handler, alsa_swparams)) < 0) {
	mp_msg(MSGT_AO,MSGL_ERR,MSGTR_AO_ALSA_UnableToGetSwParameters,
	       snd_strerror(err));
	return 0;
      }
#if SND_LIB_VERSION >= 0x000901
      if ((err = snd_pcm_sw_params_get_boundary(alsa_swparams, &boundary)) < 0) {
	mp_msg(MSGT_AO,MSGL_ERR,MSGTR_AO_ALSA_UnableToGetBoundary,
	       snd_strerror(err));
	return 0;
      }
#else
      boundary = 0x7fffffff;
#endif
      /* start playing when one period has been written */
      if ((err = snd_pcm_sw_params_set_start_threshold(alsa_handler, alsa_swparams, chunk_size)) < 0) {
	mp_msg(MSGT_AO,MSGL_ERR,MSGTR_AO_ALSA_UnableToSetStartThreshold,
	       snd_strerror(err));
	return 0;
      }
      /* disable underrun reporting */
      if ((err = snd_pcm_sw_params_set_stop_threshold(alsa_handler, alsa_swparams, boundary)) < 0) {
	mp_msg(MSGT_AO,MSGL_ERR,MSGTR_AO_ALSA_UnableToSetStopThreshold,
	       snd_strerror(err));
	return 0;
      }
#if SND_LIB_VERSION >= 0x000901
      /* play silence when there is an underrun */
      if ((err = snd_pcm_sw_params_set_silence_size(alsa_handler, alsa_swparams, boundary)) < 0) {
	mp_msg(MSGT_AO,MSGL_ERR,MSGTR_AO_ALSA_UnableToSetSilenceSize,
	       snd_strerror(err));
	return 0;
      }
#endif
      if ((err = snd_pcm_sw_params(alsa_handler, alsa_swparams)) < 0) {
	mp_msg(MSGT_AO,MSGL_ERR,MSGTR_AO_ALSA_UnableToGetSwParameters,
	       snd_strerror(err));
	return 0;
      }
      /* end setting sw-params */

      mp_msg(MSGT_AO,MSGL_V,"alsa: %d Hz/%d channels/%d bpf/%d bytes buffer/%s\n",
	     ao_data.samplerate, ao_data.channels, (int)bytes_per_sample, ao_data.buffersize,
	     snd_pcm_format_description(alsa_format));

    } // end switch alsa_handler (spdif)
    alsa_can_pause = snd_pcm_hw_params_can_pause(alsa_hwparams);
    return 1;
} // end init