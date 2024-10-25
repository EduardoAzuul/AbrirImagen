#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace cv;
using namespace std;

void funcionG(int j, int i, int contador, Mat A, Mat Marcados, queue<Point> q1) {
    if (A.at<uchar>(j, i) == 255 && Marcados.at<uchar>(j, i) == 0) {
        Marcados.at<uchar>(j, i) = contador;

        for (int a = -1; a <= 1; a++) {
            for (int b = -1; b <= 1; b++) {
                if (A.at<uchar>(j + a, i + b) == 255 && Marcados.at<uchar>(j + a, i + b) == 0)
                    q1.push(Point(i + a, b + j));
            }
        }
    }

    while (q1.empty() == false) {       //Mientras la cola no este vacia
        if (Marcados.at<uchar>(q1.front()) != 0) {
            Marcados.at<uchar>(q1.front()) = contador;

            for (int a = -1; a <= 1; a++) {
                for (int b = -1; b <= 1; b++) {
                    if (A.at<uchar>(q1.front().x + a, q1.front().y + b) == 255 && Marcados.at<uchar>(j + a, i + b) == 0)
                        q1.push(Point(q1.front().x + a, q1.front().y + j));
                }
            }
        }

    }
}

int A9main() {

    Mat image1;
    image1 = imread("Kiwi.png", IMREAD_GRAYSCALE);   // Read the file


    Mat A;
    A = imread("Kiwi.png", IMREAD_GRAYSCALE);   // Read the file
    int umbral = 50; 

    for (int i = 0; i < A.cols; i++) {
        for (int j = 0; j < A.rows; j++) {

            if (A.at<uchar>(j, i) > umbral) {   //Más grande que el umbral
                A.at<uchar>(j, i) = 255;
            }
            else {
                A.at<uchar>(j, i) = 0;
            }

        }
    }

    namedWindow("MASCARA", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("MASCARA", A);                   // Show our image inside it.
    waitKey(10);

    /*********************************/

    Mat matriz = (Mat_<float>(3, 3) <<
        0,   255,  0,
        255, 255, 255,
        0,   255,  0);

    bool erosion = false;
    Mat Erosion;
    Erosion = imread("Kiwi.png", IMREAD_GRAYSCALE);   // Read the file
    int sum = 0;

    

    for (int i = 1; i < A.cols - 1; i++) {      
        for (int j = 1; j < A.rows - 1; j++) {
            Erosion.at<uchar>(j, i) = 0;
        }
    }

    for (int i = 1; i < A.cols - 1; i++) {
        for (int j = 1; j < A.rows - 1; j++) {
            erosion=true;

            for (int mono = -(matriz.cols/2);             mono <= (matriz.cols / 2);     mono++) {
                if (erosion==false) break;
                for (int mango = -(matriz.cols / 2);     mango <= (matriz.cols / 2);    mango++) {

                    if (matriz.at<float>(1 + mango, 1 + mono) == 255 && (A.at<uchar>(j + mango , i + mono) == 0)) {
                            erosion=false;
                            break;
                    }
                }
            }

            if (erosion) Erosion.at<uchar>(j, i) = 255;
            else  Erosion.at<uchar>(j, i) = 0;
            
        }
    }


    
    //namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
    namedWindow("Erosion", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("Erosion", Erosion);                   // Show our image inside it.
    waitKey(10);

    /*****************************************************/
    Mat Marcados = imread("Kiwi.png", IMREAD_GRAYSCALE);   // Read the file


    for (int i = 1; i < Marcados.cols - 1; i++) {           //limpieza del archivo
        for (int j = 1; j < Marcados.rows - 1; j++) {
            Marcados.at<uchar>(j, i) = 0;
        }
    }

    int contador = 20;
    queue <Point> q1;
    Point aux2;
    for (int i = 1; i < A.cols - 1; i++) {
        for (int j = 1; j < A.rows - 1; j++) {
            if (A.at<uchar>(j, i) == 255) {
                funcionG(j, i, contador, A, Marcados, q1);
                contador++;
            }

        }
    }

    namedWindow("Marcados", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("Marcados", Marcados);                   // Show our image inside it.
    waitKey(0);

    return 0;
}


