#include "player.hpp"

void play_music(CvSize img_size, Blob* blobs, int num_frames) {
    
    if (blobs[0].center.y > (img_size.height / 3)) {
        switch (((int)blobs[0].center.x) / ((int)(img_size.width / 4))) {
            case 0:
                music_beat(FIRST_DRUM);
                break;
            case 1:
                music_beat(SECOND_DRUM);
                break;
            case 2:
                music_beat(THIRD_DRUM);
                break;
            case 3:
                music_beat(FOURTH_DRUM);
                break;
        }
    }
}
