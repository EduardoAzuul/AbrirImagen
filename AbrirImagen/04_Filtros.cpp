
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int A4main() {

    Mat deg1, image2, image3;
    
    deg1 = imread("dados.png", IMREAD_GRAYSCALE);   // Read the file
    image2 = imread("dados.png", IMREAD_GRAYSCALE);   // Read the fil
    
    namedWindow("Gato", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("Gato", deg1); 

    waitKey(10);

    /******************************BINARY*********************************/
    Mat Binario((500), (920), CV_8UC1, Scalar(0));;

    
    int umbral = 125;
    for (int i = 0; i < Binario.cols; i++) {  //vertical 
        for (int j = 0; j < Binario.rows; j++) {  // horizontal
            if (deg1.at<uchar>(j, i) < umbral) {
                Binario.at<uchar>(j, i) = 0;
            }
            else {
                Binario.at<uchar>(j, i) = 255;
            }
        }
    }
    waitKey(10);
    namedWindow("Degradado Binary", WINDOW_AUTOSIZE);
    imshow("Degradado Binary", Binario);


    /***************************BINARY INV*******************************/
    Mat Binario2((500), (920), CV_8UC1, Scalar(0));


    umbral = 125;
    for (int i = 0; i < Binario2.cols; i++) {  //vertical 
        for (int j = 0; j < Binario2.rows; j++) {  // horizontal
            if (deg1.at<uchar>(j, i) > umbral) {
                Binario2.at<uchar>(j, i) = 0;
            }
            else {
                Binario2.at<uchar>(j, i) = 255;
            }
        }
    }
    
    namedWindow("Degradado Binary 2", WINDOW_AUTOSIZE);
    imshow("Degradado Binary 2", Binario2);

    waitKey(10);

    /******************************TRUNC*********************************/
    Mat deg4(deg1.rows, deg1.cols, CV_8UC1, Scalar(0));
    umbral = 125;
    for (int i = 0; i < deg4.cols; i++) {  //vertical 
        for (int j = 0; j < deg4.rows; j++) {  // horizontal
            if (deg1.at<uchar>(j, i) < umbral) {
                deg4.at<uchar>(j, i) = deg1.at<uchar>(j, i);
            }
            else {
                deg4.at<uchar>(j, i) = umbral;
            }
        }
    }

    namedWindow("Degradado TRUNC", WINDOW_AUTOSIZE);
    imshow("Degradado TRUNC", deg4);

    waitKey(10);

    /******************************TOZERO*********************************/
    Mat deg5(deg1.rows, deg1.cols, CV_8UC1, Scalar(0));
    umbral = 125;
    for (int i = 0; i < deg5.cols; i++) {  //vertical 
        for (int j = 0; j < deg4.rows; j++) {  // horizontal
            if (deg1.at<uchar>(j, i) > umbral) {
                deg5.at<uchar>(j, i) = deg1.at<uchar>(j, i);
            }
            else {
                deg5.at<uchar>(j, i) = 0;
            }
        }
    }

    namedWindow("Degradado TOZERO", WINDOW_AUTOSIZE);
    imshow("Degradado TOZERO", deg5);

    waitKey(10);

    /******************************TOZERO INV*********************************/
    Mat deg6(deg1.rows, deg1.cols, CV_8UC1, Scalar(0));
    umbral = 125;
    for (int i = 0; i < deg6.cols; i++) {  //vertical 
        for (int j = 0; j < deg6.rows; j++) {  // horizontal
            if (deg1.at<uchar>(j, i) < umbral) {
                deg6.at<uchar>(j, i) = deg1.at<uchar>(j, i);
            }
            else {
                deg6.at<uchar>(j, i) = 0;
            }
        }
    }

    namedWindow("Degradado TOZERO inv", WINDOW_AUTOSIZE);
    imshow("Degradado TOZERO inv", deg6);
    
    waitKey(0);


    return -1;

}