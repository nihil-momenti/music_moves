#include "player.hpp"
#include <iostream>

void play_music(CvSize img_size, Blob* blobs, int num_frames) {
    int first_div[num_frames - 1];
    int second_div;

    first_div[0] = blobs[1].center.y - blobs[0].center.y;
    first_div[1] = blobs[2].center.y - blobs[1].center.y;
    second_div = first_div[1] - first_div[0];

    int vol = second_div * second_div / 128;

    if (blobs[0].center.y > (img_size.height / 3) && second_div > 20) {
        cout << "volume: " << vol << endl;
        switch (((int)blobs[0].center.x) / ((int)(img_size.width / 4))) {
            case 0:
                music_beat(FIRST_DRUM, vol);
                break;
            case 1:
                music_beat(SECOND_DRUM, vol);
                break;
            case 2:
                music_beat(THIRD_DRUM, vol);
                break;
            case 3:
                music_beat(FOURTH_DRUM, vol);
                break;
        }
    }
}
