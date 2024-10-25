#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int A3main() {
	cout << "Hello world";

    
    Mat A, image2, image3;
    int umbral = 120;
    

    A = imread("dados.png", IMREAD_GRAYSCALE);   // Read the file
    image2 = imread("dados.png", IMREAD_GRAYSCALE);   // Read the file
    image3 = imread("dados.png", IMREAD_COLOR);   // Read the file

    if (!A.data || !image2.data || !image3.data)                              // Check for invalid input

    {

        cout << "Could not open or find the image" << std::endl;

        return -1;

    }

    //namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
    namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.

    imshow("Display window", A);                   // Show our image inside it.

    waitKey(10);

    int col = 0;
    for (int i = 0; i < A.cols; i++) {
        for (int j = 0; j < A.rows; j++) {
            
            if (A.at<uchar>(j, i) > umbral) {   //Más grande que el umbral
                image2.at<uchar>(j, i) = 255;
            }
            else {
                image2.at<uchar>(j, i) = 0;
            }

            if (A.at<uchar>(j, i) == 255) {
                image2.at<uchar>(j, i) = 0;
            }
            
        }
    }

    //namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
    namedWindow("luego", WINDOW_AUTOSIZE);// Create a window for display.

    imshow("luego", image2);                   // Show our image inside it.

    waitKey(0);

}