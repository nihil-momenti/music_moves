//VERSION: HAND DETECTION 1.0
//AUTHOR: ANDOL LI
//PROJECT: HAND DETECTION PROTOTYPE
//LAST UPDATED: 03/2009

#include "cv.h"
#include "highgui.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

#define BIGGEST 0
#define CLOSEST 1

typedef struct blob {
    double size;
    CvSeq* contour;
    CvPoint center;
} Blob;

void maskImage(CvArr* src, CvArr* dst) {
    static IplImage* hsv_image = cvCreateImage(cvGetSize(src), 8, 3);
    static CvScalar  hsv_min = cvScalar(0, 30, 80, 0);
    static CvScalar  hsv_max = cvScalar(12, 150, 255, 0);
    static IplConvKernel* element   = cvCreateStructuringElementEx(5, 5, 3, 3, CV_SHAPE_RECT);

    cvSmooth(src, src, CV_MEDIAN, 5);

    cvCvtColor(src, hsv_image, CV_BGR2HSV);
    cvInRangeS(hsv_image, hsv_min, hsv_max, dst);

    cvSmooth(dst, dst, CV_MEDIAN, 5);
    cvSmooth(dst, dst, CV_MEDIAN, 5);
    cvSmooth(dst, dst, CV_MEDIAN, 5);

    cvDilate(dst, dst, element, 2);
    cvErode( dst, dst, element, 2);

    cvDilate(dst, dst, element, 2);
    cvErode( dst, dst, element, 2);
}

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

void initialise_blobs(Blob* blobs, int size) {
    for (int i = 0; i < size; i++) {
        blobs[i].size = 0;
        blobs[i].contour = NULL;
        blobs[i].center = cvPoint(0,0);
    }
}

void clear_blob(Blob* blob) {
    blob->size = -10000;
    blob->contour = NULL;
    blob->center = cvPoint(-10000,-10000);
}

int diff(CvPoint a, CvPoint b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int main()
{
    CvCapture* capture = cvCaptureFromCAM(0);

    cvQueryFrame(capture) ? cout << "Video camera capture status: OK" << endl
                          : cout << "Video capture failed, please check the camera." << endl;

    CvSize sz = cvGetSize(cvQueryFrame(capture));

    IplImage* src            = cvCreateImage(sz, 8, 3);
    IplImage* background     = cvCreateImage(sz, 8, 3);
    IplImage* hsv_mask       = cvCreateImage(sz, 8, 1);
    IplImage* temp           = cvCreateImage(sz, 8, 1);
    IplImage* prev_mask      = cvCreateImage(sz, 8, 1);
    IplImage* diff_mask      = cvCreateImage(sz, 8, 1);

    int strategy = BIGGEST;
    int curr_mask = 0;

    Blob first_blob[10];
    initialise_blobs(first_blob, 10);
    Blob second_blob[10];
    initialise_blobs(second_blob, 10);

    CvMemStorage* storage    = cvCreateMemStorage();
    CvSeq* contour;
    CvMoments moments = {0};

    while( cvWaitKey(10) != 27) {
        if (src = cvQueryFrame(capture)) {
            // Much easy to hit the drums if we pretend it's a mirror.
            cvFlip(src, NULL, 1);
            for (int i = 8; i >= 0; i--) {
                first_blob[i+1] = first_blob[i];
                second_blob[i+1] = second_blob[i];
            }
            clear_blob(first_blob);
            clear_blob(second_blob);

            int first_diff = diff(first_blob[0].center, first_blob[1].center);
            int second_diff = diff(second_blob[0].center, second_blob[1].center);

            maskImage(src, hsv_mask);

            drawDrums(src);
            drawDrumRegions(src);

            // Try and locate the two hand blobs
            cvCopy(hsv_mask, temp);
            cvFindContours(temp, storage, &contour, sizeof(CvContour), CV_RETR_EXTERNAL);
            
            if (first_blob[1].center.x < 0 || second_blob[1].center.x < 0) {
                strategy = BIGGEST;
            } else {
                strategy = CLOSEST;
            }

            for (; contour != 0; contour = contour->h_next) {
                int size = cvArcLength(contour);
                cvMoments(contour, &moments);
                CvPoint center = cvPoint(moments.m10 / moments.m00, moments.m01 / moments.m00);

                switch (strategy) {
                    case BIGGEST: {
                        if (size > first_blob[0].size) {
                            if (first_blob[0].size > second_blob[0].size) {
                                second_blob[0].size = size;
                                second_blob[0].contour = contour;
                                second_blob[0].center = center;
                            }
                            first_blob[0].size = size;
                            first_blob[0].contour = contour;
                            first_blob[0].center = center;
                        }
                        break;
                    }
                    case CLOSEST: {
                        int diff_to_first = diff(center, first_blob[0].center);
                        int diff_to_second = diff(center, second_blob[0].center);

                        if (diff_to_first < diff_to_second) {
                            if (diff_to_first < first_diff) {
                                first_blob[0].size = size;
                                first_blob[0].contour = contour;
                                first_blob[0].center = center;
                            }
                        } else {
                            if (diff_to_second < second_diff) {
                                second_blob[0].size = size;
                                second_blob[0].contour = contour;
                                second_blob[0].center = center;
                            }
                        }
                        break;
                    }
                }
            }
            CvScalar colour = CV_RGB(rand()&255, rand()&255, rand()&255);
            cvDrawContours(src, first_blob[0].contour, colour, colour, -1, 3);
            
            colour = CV_RGB(rand()&255, rand()&255, rand()&255);
            cvDrawContours(src, second_blob[0].contour, colour, colour, -1, 3);

            for (int i = 0; i < 10; i++) {
                cvCircle(src, first_blob[i].center, 10, CV_RGB(200-15*i, 20, 20), CV_FILLED);
                cvCircle(src, second_blob[i].center, 10, CV_RGB(20, 20, 200-15*i), CV_FILLED);
            }
            // Find the center of each blob
            
            cvShowImage("src",     src);
            cvShowImage("hsv-mask", hsv_mask);
        }
    }

    cvReleaseCapture( &capture);
    cvDestroyAllWindows();
}

