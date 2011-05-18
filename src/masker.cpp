#include "masker.hpp"

void maskImage(CvArr* src, CvArr* dst) {
    static IplImage* hsv_image = cvCreateImage(cvGetSize(src), 8, 3);
    static CvScalar  hsv_min = cvScalar(0, 30, 80, 0);
    static CvScalar  hsv_max = cvScalar(20, 150, 255, 0);
    static IplConvKernel* element   = cvCreateStructuringElementEx(5, 5, 3, 3, CV_SHAPE_ELLIPSE);

    cvSmooth(src, src, CV_MEDIAN, 5);
    //cvSmooth(src, src, CV_MEDIAN, 5);
    cvSmooth(src, src, CV_MEDIAN, 5);

    cvCvtColor(src, hsv_image, CV_BGR2HSV);
    cvInRangeS(hsv_image, hsv_min, hsv_max, dst);

    //cvSmooth(dst, dst, CV_MEDIAN, 5);

    cvDilate(dst, dst, element, 2);
    cvErode( dst, dst, element, 1);

    //cvSmooth(dst, dst, CV_MEDIAN, 5);
    //cvSmooth(dst, dst, CV_MEDIAN, 5);
    //cvSmooth(dst, dst, CV_MEDIAN, 5);

    //cvDilate(dst, dst, element, 2);
    //cvErode( dst, dst, element, 2);
}
