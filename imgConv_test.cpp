#include <stdio.h>
#include <hls_opencv.h>
#include <hls_stream.h>
#include <opencv2/core/core.hpp>
#include <ap_axi_sdata.h>
typedef ap_axiu<8,2,5,6> uint_8_side_channel;

void conv(uint8_t image_in[320*240],uint8_t image_out[320*240]);
#define INPUT_IMAGE_CORE "a.bmp"


int main()
{
printf("Load image %s\n",INPUT_IMAGE_CORE);
//cv::Mat imageSrc;
//imageSrc = cv::imread(INPUT_IMAGE_CORE);
IplImage* src;
IplImage* img;
IplImage* dstr;
src = cvLoadImage(INPUT_IMAGE_CORE);
img = cvCreateImage(cvSize(src->width, src->height), IPL_DEPTH_8U, 1);
cvCvtColor(src, img, CV_BGR2GRAY);
uint8_t* data    = (uint8_t *)img->imageData;
uint8_t image_in[320*240];
uint8_t image_out[320*240];
memcpy(image_in,data,sizeof(uint8_t)*320*240);
conv(image_in,image_out);
////convert to greyscale
////cv::cvtColor(imageSrc, imageSrc, CV_BGR2GRAY);
IplImage* dst = cvCreateImage(cvSize(src->width, src->height), IPL_DEPTH_8U, 1);
memcpy(img->imageData,image_out,sizeof(uint8_t)*320*240);
cvSaveImage("object-detection-output.jpg", img, 0);

cvReleaseImage(&src);
cvReleaseImage(&img);
cvReleaseImage(&dst);

return 0;
}
