#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int A6main() {

    Mat image;

    int hist[256] = { 0 };
    image = imread("Calle.jpg", IMREAD_GRAYSCALE);   // Read the file



    if (!image.data) {
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    namedWindow("flores", WINDOW_NORMAL);// Create a window for display.
    imshow("flores", image);                   // Show our image inside it.

    waitKey(10);



    for (int i = 0; i < image.cols; i++) {  //vertical 
        for (int j = 0; j < image.rows; j++) {  // horizontal
            hist[image.at<uchar>(j, i)] += 1;
        }
    }

    for (int i = 0; i <= 255; i++) {
        cout << hist[i] + " ";
    }

    Mat image2(500, 1005, CV_8UC1, Scalar(0));
    rectangle(image2, Point(0, 0), Point(200, 100), Scalar(255), FILLED, LINE_8, 0);

    /*namedWindow("Rectangulo", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("Rectangulo", image2);                   // Show our image inside it.

    waitKey(10);*/
    


    Mat image3(500, 1275, CV_8UC1, Scalar(0));
    for (int i = 0; i <= 255; i++) {
        rectangle(image3, Point(i*5, 500), Point((i*5)+5, 500-(hist[i]/20)), Scalar(255), FILLED, LINE_8, 0);
    }

    namedWindow("Histograma", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("Histograma", image3);                   // Show our image inside it.

    waitKey(10);

    /***CDF****/
    int  max = 0;

    float pmf[255];
    float pixeles = image.rows * image.cols;

    for (int x = 0; x < 255; x++) {
        pmf[x] = (float(hist[x]) / pixeles);
    }

    Mat image4(500, 1275, CV_8UC1, Scalar(0));
    for (int i = 0; i <= 255; i++) {
        rectangle(image4, Point(i * 5, 500), Point((i * 5) + 5, 500 - (pmf[i]*20000)), Scalar(255), FILLED, LINE_8, 0);
    }

    namedWindow("PMF", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("PMF", image4);                   // Show our image inside it.

    waitKey(10);

    float CDF[255];

    for (int x = 0; x <= 255; x++) {
        CDF[x] = pmf[x];
    }

    for (int x = 1; x <= 255; x++) {
        CDF[x] = CDF[x]+CDF[x-1];
    }


    Mat image5(500, 1275, CV_8UC1, Scalar(0));
    for (int i = 0; i <= 255; i++) {
        rectangle(image5, Point(i * 5, 500), Point((i * 5) + 5, 500 - (CDF[i] * 480)), Scalar(255), FILLED, LINE_8, 0);
    }

    namedWindow("CDF", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("CDF", image5);                   // Show our image inside it.

    waitKey(10);

    Mat image6=image;
    for (int i = 0; i < image.cols; i++) {
        for (int j = 0; j < image.rows; j++) {
            image6.at<uchar>(j, i) = floor(255 * CDF[image.at<uchar>(j, i)]);

        }
    }

    namedWindow("Equalization", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("Equalization", image6);                   // Show our image inside it.

    waitKey(10);

    for (int i = 0; i < image.cols; i++) {  //vertical 
        for (int j = 0; j < image.rows; j++) {  // horizontal
            hist[image.at<uchar>(j, i)] += 1;
        }
    }


    Mat image7(500, 1275, CV_8UC1, Scalar(0));
    for (int i = 0; i <= 255; i++) {
        rectangle(image7, Point(i * 5, 500), Point((i * 5) + 5, 500 - (hist[i] / 20)), Scalar(255), FILLED, LINE_8, 0);
    }

    namedWindow("Histograma2", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("Histograma2", image7);                   // Show our image inside it.

    waitKey(0);
}