#include "blob.hpp"
#include <iostream>

int diff(CvPoint a, CvPoint b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

void initialise_blobs(Blob* blobs, int size) {
    for (int i = 0; i < size; i++) {
        blobs[i].size = 0;
        blobs[i].contour = NULL;
        blobs[i].center = cvPoint(0,0);
    }
}

void clear_blob(Blob* blob) {
    blob->size = 0;
    blob->contour = NULL;
    blob->center = cvPoint(0,0);
}

int calc_score(CvPoint center, int size, Blob last_blob) {
    return size * 100 - diff(center, last_blob.center);
}

void locate_blobs(CvArr* img, Blob* first_blob, Blob* second_blob, int num_frames) {
    static IplImage* temp = cvCreateImage(cvGetSize(img), 8, 1);
    static CvMemStorage* storage    = cvCreateMemStorage();
    static CvSeq* contour;
    static CvMoments moments = {0};

    for (int i = num_frames - 1; i > 0; i--) {
        first_blob[i] = first_blob[i-1];
        second_blob[i] = second_blob[i-1];
    }

    cvCopy(img, temp);
    cvFindContours(temp, storage, &contour, sizeof(CvContour), CV_RETR_EXTERNAL);

    int first_max = 0;
    int second_max = 0;
    for (int i = 0; contour != 0; contour = contour->h_next, i++) {
        int size = cvArcLength(contour);
        cvMoments(contour, &moments);
        CvPoint center = cvPoint(moments.m10 / moments.m00, moments.m01 / moments.m00);

        int first_score = calc_score(center, size, first_blob[1]);
        int second_score = calc_score(center, size, second_blob[1]);
        if (first_score > second_score) {
            if (first_score > first_max) {
                first_max = first_score;
                first_blob[0].center = center;
                first_blob[0].size = size;
                first_blob[0].contour = contour;
            }
        } else {
            if (second_score > second_max) {
                second_max = second_score;
                second_blob[0].center = center;
                second_blob[0].size = size;
                second_blob[0].contour = contour;
            }
        }
    }
}
