#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int A7main() {

    Mat image,image2;

    image = imread("code1_e5.BMP", IMREAD_GRAYSCALE);   // Read the file
    image2 = imread("code2_e5.BMP", IMREAD_GRAYSCALE);   // Read the file


    if (!image.data || !image2.data) {
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    namedWindow("Imagen 1", WINDOW_NORMAL);// Create a window for display.
    imshow("Imagen 1", image);                   // Show our image inside it.
    namedWindow("Imagen 2", WINDOW_NORMAL);// Create a window for display.
    imshow("Imagen 2", image2);                   // Show our image inside it.


    waitKey(10);

    Mat Binario, image3;
    Binario = imread("cebra.BMP", IMREAD_GRAYSCALE);   // Read the file
    image3 = imread("cebra.BMP", IMREAD_GRAYSCALE);   // Read the file

    int tc = 46;
    for (int i = 0; i < Binario.cols; i++) {  //vertical 
        for (int j = 0; j < Binario.rows; j++) {  // horizontal
            if (Binario.at<uchar>(j, i) > tc) {
                Binario.at<uchar>(j, i) = 0;
            }
            else {
                Binario.at<uchar>(j, i) = 255;
            }
        }
    }
    
    namedWindow("marscara", WINDOW_AUTOSIZE);
    imshow("marscara Binary", Binario);
    waitKey(10);

    /***********************/
    Mat desInv, desInv2;
    desInv = imread("code1_e5.BMP", IMREAD_GRAYSCALE);   // Read the file
    desInv2 = imread("code2_e5.BMP", IMREAD_GRAYSCALE);   // Read the file

    for (int i = 0; i < image.cols; i++) {  //vertical 
        for (int j = 0; j < image.rows; j++) {  // horizontal
            if (Binario.at<uchar>(j, i) == 255) {
                desInv.at<uchar>(j, i) = image2.at<uchar>(j, i);
                desInv2.at<uchar>(j, i) = image.at<uchar>(j, i);
            }
        }
    }

    namedWindow("DesInv", WINDOW_NORMAL);
    imshow("DesInv", desInv);
    namedWindow("DesInv2", WINDOW_NORMAL);
    imshow("DesInv2", desInv2);
    waitKey(10);

    Mat optimismo, optimismo2;

    optimismo = desInv;   // Read the file
    optimismo2 = desInv2;   // Read the file

    for (int i = 0; i < image.cols; i++) {  //vertical 
        for (int j = 0; j < image.rows; j++) {  // horizontal
                optimismo.at<uchar>(j, i) = 255 - desInv.at<uchar>(j, i);
                optimismo2.at<uchar>(j, i) = 255 - desInv2.at<uchar>(j, i);
        }
    }

    namedWindow("optimismo", WINDOW_NORMAL);
    imshow("optimismo", optimismo);
    namedWindow("optimismo2", WINDOW_NORMAL);
    imshow("optimismo2", optimismo2);
    waitKey(10); 

    /******************* NORMALIZACION *****************/
    Mat norm, norm2;
    norm = imread("bodegon1.BMP", IMREAD_GRAYSCALE);   // Read the file;
    norm2 = imread("bodegon2.BMP", IMREAD_GRAYSCALE);   // Read the file;
    int max1 = 0;
    int max2 = 0;


    for (int i = 0; i < norm.cols; i++) {  //vertical 
        for (int j = 0; j < norm.rows; j++) {  // horizontal
            if (max1 <= norm.at<uchar>(j, i)) {
                max1 = norm.at<uchar>(j, i);
            }
            if (max2 <= norm2.at<uchar>(j, i)) {
                max2 = norm2.at<uchar>(j, i);
            }
        }
    }
    waitKey(10);
    float aux1 = (237.0 / max1);
    float aux2 = (237.0 / max2) - 0.025;

    for (int i = 0; i < norm.cols; i++) {  //vertical 
        for (int j = 0; j < norm.rows; j++) {  // horizontal
            norm.at<uchar>(j, i) = norm.at<uchar>(j, i) * aux1;
            norm2.at<uchar>(j, i) = norm2.at<uchar>(j, i) * aux2;
        }
    }

    namedWindow("norm", WINDOW_NORMAL);
    imshow("norm", norm);
    namedWindow("norm2", WINDOW_NORMAL);
    imshow("norm2", norm2);
    waitKey(10);

    Mat fin, fin2;

    fin = optimismo;
    fin2 = optimismo2;

    for (int i = 0; i < fin.cols; i++) {  //vertical 
        for (int j = 0; j < fin.rows; j++) {  // horizontal
            if (optimismo.at<uchar>(j, i) - norm2.at<uchar>(j, i) < 0) {   //Si se pasa
                fin.at<uchar>(j, i) = 0;
            }
            else {
                fin.at<uchar>(j, i) = optimismo.at<uchar>(j, i) - norm2.at<uchar>(j, i);
            }

            if (optimismo2.at<uchar>(j, i) - norm.at<uchar>(j, i) < 0) {   //Si se pasa
                fin2.at<uchar>(j, i) = 0;
            }
            else {
                fin2.at<uchar>(j, i) = optimismo2.at<uchar>(j, i) - norm.at<uchar>(j, i);
            }
            

            fin.at<uchar>(j, i) = fin.at<uchar>(j, i) * 255 /3;
            fin2.at<uchar>(j, i) = fin2.at<uchar>(j, i) * 255 / 7;
        }
    }

    namedWindow("fin", WINDOW_NORMAL);
    imshow("fin", fin);
    namedWindow("fin2", WINDOW_NORMAL);
    imshow("fin2", fin2);
    waitKey(0);







}