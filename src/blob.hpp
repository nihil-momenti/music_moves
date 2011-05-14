#ifndef blob_hpp
#define blob_hpp

#include <opencv/cv.h>

typedef struct blob {
    double size;
    CvSeq* contour;
    CvPoint center;
} Blob;

void initialise_blobs(Blob* blobs, int size);
void clear_blob(Blob* blob);
void locate_blobs(CvArr* img, Blob* first_blob, Blob* second_blob, int num_frames);

#endif
