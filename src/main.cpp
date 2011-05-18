//VERSION: HAND DETECTION 1.0
//AUTHOR: ANDOL LI
//PROJECT: HAND DETECTION PROTOTYPE
//LAST UPDATED: 03/2009

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
#include <pthread.h>

#include "masker.hpp"
#include "blob.hpp"
#include "drums.hpp"
#include "music.hpp"
#include "player.hpp"


void drawOverlay(CvArr* src, Blob* first_blob, Blob* second_blob, int num_frames) {
    drawDrums(src);
    drawDrumRegions(src);

    CvScalar colour = CV_RGB(rand()&255, rand()&255, rand()&255);
    cvDrawContours(src, first_blob[0].contour, colour, colour, -1, 3);
    
    colour = CV_RGB(rand()&255, rand()&255, rand()&255);
    cvDrawContours(src, second_blob[0].contour, colour, colour, -1, 3);

    for (int i = 0; i < num_frames; i++) {
        cvCircle(src, first_blob[i].center, 6, CV_RGB(200-15*i, 20, 20), 5);
        cvCircle(src, second_blob[i].center, 6, CV_RGB(20, 20, 200-15*i), 5);
    }
}

int main()
{
    music_init();

    CvCapture* capture = cvCaptureFromCAM(0);

    cvQueryFrame(capture) ? cout << "Video camera capture status: OK" << endl
                          : cout << "Video capture failed, please check the camera." << endl;

    CvSize sz = cvGetSize(cvQueryFrame(capture));

    IplImage* src            = cvCreateImage(sz, 8, 3);
    IplImage* hsv_mask       = cvCreateImage(sz, 8, 1);

    Blob first_blob[10];  initialise_blobs(first_blob, 10);
    Blob second_blob[10]; initialise_blobs(second_blob, 10);

    while( cvWaitKey(10) != 27) {
        if ((src = cvQueryFrame(capture))) {
            // Much easy to hit the drums if we pretend it's a mirror.
            cvFlip(src, NULL, 1);
            maskImage(src, hsv_mask);
            locate_blobs(hsv_mask, first_blob, second_blob, 10);
            play_music(sz, first_blob, 10);
            play_music(sz, second_blob, 10);

            drawOverlay(src, first_blob, second_blob, 10);
            
            cvShowImage("src",     src);
            cvShowImage("hsv-mask", hsv_mask);
        }
    }

    music_destroy();
    cvReleaseCapture( &capture);
    cvDestroyAllWindows();
    exit(0);
}

