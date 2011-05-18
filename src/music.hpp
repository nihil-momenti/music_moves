#ifndef MUSIC_HPP
#define MUSIC_HPP

typedef enum {
    FIRST_DRUM,
    SECOND_DRUM,
    THIRD_DRUM,
    FOURTH_DRUM
} SoundID;

void music_init();

void music_destroy();

void music_beat(SoundID sound_id, int volume);
#endif
