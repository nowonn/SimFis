#ifndef __AUDIO_H__
#define __AUDIO_H__

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

ma_engine engine;

#ifndef _WIN32
#define MEDIA_START(filename, extension) _binary_##filename##_##extension##_start
#define MEDIA_END(filename, extension) _binary_##filename##_##extension##_end
#else
#define MEDIA_START(filename, extension) binary_##filename##_##extension##_start
#define MEDIA_END(filename, extension) binary_##filename##_##extension##_end
#endif
#define MEDIA_BINARY(filename, extension) \
  extern unsigned char MEDIA_START(filename, extension)[]; \
  extern unsigned char MEDIA_END(filename, extension)[];

struct AudioMedia{
    int initialized;
    char *binStart;
    unsigned long size;
    const char *name;

    void (*play)(struct AudioMedia*);
};

void MediaPlayAudio(struct AudioMedia* md){
    if(!md->initialized){
        HRSRC res = FindResource(NULL, md->name, RT_RCDATA);
        md->binStart = (char*)LockResource(LoadResource(NULL, res));
        md->size = SizeofResource(NULL, res);
        md->initialized = 1;
        ma_resource_manager_register_encoded_data(
            ma_engine_get_resource_manager(&engine), md->name,
            md->binStart, md->size);
    }
    ma_engine_play_sound(&engine, md->name, NULL);
}

#define PlayAudio(name) name.play(&name)

#define INCLUDE_AUDIO(filename, extension) \
    struct AudioMedia filename = { \
        .initialized = 0, \
        .name = #filename "_mp3", \
        .play = MediaPlayAudio, \
    };

#include "audio_files.h"
#endif
