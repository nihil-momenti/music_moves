#include "drums.hpp"

void drawDrums(CvArr* img) {
    static int width  = cvGetSize(img).width;
    static int height = cvGetSize(img).height;

    static int xCenter[] = {
        1 * width / 8,
        3 * width / 8,
        5 * width / 8,
        7 * width / 8
    };

    static int drumWidth = width / 8 - width / 32;
    static int drumBase  = height - height / 6;
    static int drumTop   = height - height / 3;

    static CvScalar lightBrown = CV_RGB(160, 95, 10);
    static CvScalar darkBrown  = CV_RGB(150, 75,  0);

    for (int i = 0; i < 4; i++) {
        cvRectangle(img, cvPoint(xCenter[i] - drumWidth, drumTop), cvPoint(xCenter[i] + drumWidth, drumBase), lightBrown, CV_FILLED);
        cvEllipse(  img, cvPoint(xCenter[i], drumBase), cvSize(drumWidth, drumWidth / 3), 0, 0, 360, lightBrown, CV_FILLED);
        cvEllipse(  img, cvPoint(xCenter[i], drumTop ), cvSize(drumWidth, drumWidth / 3), 0, 0, 360, darkBrown , CV_FILLED);
    }
}

void drawDrumRegions(CvArr* img) {
    static int width  = cvGetSize(img).width;
    static int height = cvGetSize(img).height;

    for (int i = 0; i < 4; i++) {
        cvRectangle(img, cvPoint(i * width / 4, height / 3), cvPoint((i + 1) * width, height), CV_RGB(0,0,0), 1);
    }
}
