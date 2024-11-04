#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat Original = imread("CaraEspiral.jpg", IMREAD_GRAYSCALE);   // Leemos la imagen en escala de grises
    if (Original.empty()) {
        cout << "No se pudo cargar la imagen." << endl;
        return -1;
    }

    namedWindow("Original", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("Original", Original);                   // Show our image inside it.

    waitKey(10);

    Mat vertical (Original.rows, (Original.cols), CV_32FC1, Scalar(0));
    Mat horizontal(Original.rows, (Original.cols), CV_32FC1, Scalar(0));


    namedWindow("horizontal", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("horizontal", horizontal);                   // Show our image inside it.

    waitKey(10);

    namedWindow("vertical", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("vertical", vertical);                   // Show our image inside it.

    waitKey(0);



    Mat gx = (Mat_<float>(3, 3) <<
        -1, 0, 1,
        -2, 0, 2,
        -1, 0, 1);

    Mat gy = (Mat_<float>(3, 3) <<
        -1, -2, -1,
        0, 0, 0,
        1, 2, 1);

    
    for (int j = 1; j < Original.cols - 1; j++) {  //vertical 
        for (int i = 1; i < Original.rows - 1; i++) {  // horizontal
            float sum1 = 0;
            float sum2 = 0;

            for (int mono = -1; mono <= 1; mono++) {
                for (int mango = -1; mango <= 1; mango++) {

                    sum1 = sum1 + Original.at<uchar>(i + mono, j + mango) * gx.at<float>(1 + mono, 1 + mango);
                    sum2 = sum2 + Original.at<uchar>(i + mono, j + mango) * gy.at<float>(1 + mono, 1 + mango);

                }
            }
            horizontal.at<float>(i, j) = sum1;
            vertical.at<float>(i, j) = sum2;

        }
    }

    namedWindow("horizontal", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("horizontal", horizontal);                   // Show our image inside it.

    waitKey(0);

    namedWindow("vertical", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("vertical", vertical);                   // Show our image inside it.

    waitKey(0);



}