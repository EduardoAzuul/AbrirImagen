#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int A5main() {

	Mat image, image2;

	image = imread("Ciudad.jpg", IMREAD_GRAYSCALE);   // Read the file
	image2 = imread("peces.jpg", IMREAD_GRAYSCALE);   // Read the file



	if (!image.data || !image2.data)                              // Check for invalid input

	{
		cout << "Could not open or find the image" << std::endl;
		return -1;

	}

	namedWindow("Ciudad", WINDOW_AUTOSIZE);// Create a window for display.
	imshow("Ciudad", image2);                   // Show our image inside it.

	waitKey(10);

	namedWindow("Peces", WINDOW_AUTOSIZE);// Create a window for display.
	imshow("Peces", image);                   // Show our image inside it.

	waitKey(10);

	if (!image.data || !image2.data)

	{

		cout << "Could not open or find the image" << std::endl;

		return -1;

	}

	int srows;
	int scols;

	if (image.rows < image2.rows) { // Compare rows and choose smallest one
		srows = image.rows;
	}
	else {
		srows = image2.rows;
	}

	if (image.cols < image2.cols) { // Compare cols and choose smallest one
		scols = image.cols;
	}
	else {
		scols = image2.cols;
	}

	/****SUMA****/
	Mat image3(srows, scols, CV_8UC1, Scalar(0)); // new image

	for (int i = 0; i < scols; i++) {
		for (int j = 0; j < srows; j++) {
			
			if ((image2.at<uchar>(j, i) + image.at<uchar>(j, i)) < 255) {
				image3.at<uchar>(j, i) = (image2.at<uchar>(j, i) + image.at<uchar>(j, i));
			}
			else {
				image3.at<uchar>(j, i) = 255;
			}
		}
	}

	namedWindow("resultado", WINDOW_NORMAL);// Create a window for display.

	imshow("resultado", image3);                   // Show our image inside it.

	waitKey(10);

	/**************************************/
	Mat image4(image.rows, image.cols, CV_8UC1, Scalar(0)); // new image

	for (int i = 0; i < image4.cols; i++) {
		for (int j = 0; j < image4.rows; j++) {
			if (image.at<uchar>(j, i) + 50 < 255) {
				image4.at<uchar>(j, i) = image.at<uchar>(j, i) + 50;
			}
			else {
				image4.at<uchar>(j, i) = 255;
			}
		}
	}

	namedWindow("Desface", WINDOW_NORMAL);// Create a window for display.

	imshow("Desface", image4);                   // Show our image inside it.


	waitKey(10);

	int col = 0;
	Mat deg(image.rows, image.cols, CV_8UC1, Scalar(0));
	float num1 = 0.0;
	float aux = 255.0 / (float)deg.cols;

	for (int i = 0; i < deg.rows; i++) {  //vertical
		num1 = 0;
		for (int j = 0; j < deg.cols; j++) {  // horizontal
			num1 += aux;

			deg.at<uchar>(i, j) = (uchar)(num1);
		}
	}
	//namedWindow("deg", WINDOW_NORMAL);
	//imshow("deg", deg);

	waitKey(10);


	Mat image5(image.rows, image.cols, CV_8UC1, Scalar(0)); // new image

	for (int i = 0; i < image5.cols; i++) {
		for (int j = 0; j < image5.rows; j++) {
			if ((image.at<uchar>(j, i) + deg.at<uchar>(j, i)) < 255) {
				image5.at<uchar>(j, i) = (image.at<uchar>(j, i) + deg.at<uchar>(j, i));
			}
		}
	}

	namedWindow("resultado3", WINDOW_NORMAL);// Create a window for display.
	imshow("resultado3", image5);

	waitKey(10);

	Mat image6(srows, scols, CV_8UC1, Scalar(0)); // new image

	for (int i = 0; i < scols; i++) {
		for (int j = 0; j < srows; j++) {
			image6.at<uchar>(j, i) = (0.25 * image2.at<uchar>(j, i)) + (0.75 * image.at<uchar>(j, i));
		}
	}

	namedWindow("resultado4", WINDOW_NORMAL);// Create a window for display.

	imshow("resultado4", image6);                   // Show our image inside it.

	waitKey(10);

	/*****************/

	Mat image7(image.rows, image.cols, CV_8UC1, Scalar(0)); // new image

	for (int i = 0; i < image6.cols; i++) {
		for (int j = 0; j < image6.rows; j++) {
			image7.at<uchar>(j, i) = (255 - (image.at<uchar>(j, i)));
		}
	}

	namedWindow("Inverso", WINDOW_NORMAL);// Create a window for display.
	imshow("Inverso", image7);

	waitKey(10);

	/********Resta********/

	Mat image8(srows, scols, CV_8UC1, Scalar(0)); // new image

	for (int i = 0; i < scols; i++) {
		for (int j = 0; j < srows; j++) {
			image8.at<uchar>(j, i) = (image2.at<uchar>(j, i)) - (image.at<uchar>(j, i));
		}
	}

	namedWindow("Resta", WINDOW_NORMAL);// Create a window for display.

	imshow("Resta", image8);                   // Show our image inside it.

	waitKey(0);
}