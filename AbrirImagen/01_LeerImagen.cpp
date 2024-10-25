#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int A1main() {

    Mat image, image2;

	image = imread("CaraEspiral.jpg", IMREAD_GRAYSCALE);   // Read the file
    image2 = imread("floresVangoh.jpeg", IMREAD_GRAYSCALE);   // Read the file



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

    
    Mat Binario((image.rows-50), (image.cols), CV_8UC1, Scalar(0));

    int umbral = 45;
    for (int i = 0; i < Binario.cols; i++) {  //vertical 
        for (int j = 0; j < Binario.rows; j++) {  // horizontal
            if (image.at<uchar>(j, i) < umbral) {
                Binario.at<uchar>(j, i) = 0;
            }
            else {
                Binario.at<uchar>(j, i) = 255;
            }
        }
    }
    
    namedWindow("Degradado Binary", WINDOW_AUTOSIZE);
    imshow("Degradado Binary", Binario);

    waitKey(10);

    Mat resultado((image.rows - 50), (image.cols), CV_8UC1, Scalar(0));

    for (int i = 0; i < resultado.cols; i++) {  //vertical 
        for (int j = 0; j < resultado.rows; j++) {  // horizontal
            if (Binario.at<uchar>(j, i) == 255) {
                resultado.at<uchar>(j, i) = image.at<uchar>(j, i);
            }
            else
                resultado.at<uchar>(j, i) = image2.at<uchar>(j+100, i);
        }
    }

    namedWindow("resultado", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("resultado", resultado);                   // Show our image inside it.

    waitKey(0);

    return 0;
}