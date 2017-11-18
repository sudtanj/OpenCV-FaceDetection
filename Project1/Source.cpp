#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int input_Mode = 0;
Mat image;
string windowName = "Face Detection";
CascadeClassifier face_cascade;
std::vector<Rect> faces;
void scanFaces() {
	face_cascade.detectMultiScale(image, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
}

int main()
{
	namedWindow(windowName);
	VideoCapture cap;
	createTrackbar("Input Mode", windowName, &input_Mode, 1);
	face_cascade.load("lbpcascade_frontalface.xml");

	while (!(waitKey(30) >= 0)) {
		if (input_Mode==1) {
			if (!cap.isOpened()) 
				cap.open(0);
			cap >> image;
		}
		else {
			if (cap.isOpened()) 
				cap.release();
			image = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
		}
		scanFaces();
		for (Rect temp : faces) 
			rectangle(image, temp, Scalar(255, 0, 255));
		imshow(windowName, image);
	}

	return EXIT_SUCCESS;
}