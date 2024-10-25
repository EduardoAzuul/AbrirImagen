
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int A2main(){

    
    /*
    Mat image, image2, image3;

    image = imread("Fondo.png", IMREAD_GRAYSCALE);   // Read the file
    image2 = imread("Kevin.png", IMREAD_GRAYSCALE);   // Read the file
    image3 = imread("dados.png", IMREAD_COLOR);   // Read the file

    if (!image.data || !image2.data || !image3.data)                              // Check for invalid input

    {

        cout << "Could not open or find the image" << std::endl;

        return -1;

    }

    //namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
    namedWindow("Display window", WINDOW_NORMAL);// Create a window for display.

    imshow("Display window", image);                   // Show our image inside it.

    waitKey(10);                                          // Wait for a keystroke in the window

    namedWindow("Kevin", WINDOW_AUTOSIZE);// Create a window for display.
    //namedWindow("Display window", WINDOW_NORMAL);// Create a window for display.

    imshow("Kevin", image2);                   // Show our image inside it.

    waitKey(10);                                          // Wait for a keystroke in the window

    namedWindow("gato", WINDOW_AUTOSIZE);// Create a window for display.
    //namedWindow("Display window", WINDOW_NORMAL);// Create a window for display.

    imshow("Gato", image3);                   // Show our image inside it.

    waitKey(0);                                          // Wait for a keystroke in the window

    */

    Mat A33(500, 500, CV_8UC1, Scalar(0));

    namedWindow("negro", WINDOW_AUTOSIZE);// Create a window for display.
    //namedWindow("Display window", WINDOW_NORMAL);// Create a window for display.

    imshow("negro", A33);                   // Show our image inside it.

    waitKey(10);                                          // Wait for a keystroke in the window


    Mat A(500, 500, CV_8UC1, Scalar(0));
    int col = 0;
    for(int i=0; i<A.cols; i++){
            if (i == (A.cols / 2) || i == 0) {   //Cuando sea la mitad cambia el valor a el opuesto
                col ^= 0xff;
            }
        for (int j = 0; j < A.rows; j++) {
            if (j == (A.rows / 2) || j == 0) {   //Cuando sea la mitad cambia el valor a el opuesto
                col ^= 0xff;
            }
            A.at<uchar>(j, i) = (uchar)(col);
        }
    }

    namedWindow("A", WINDOW_AUTOSIZE);// Create a window for display.
    //namedWindow("Display window", WINDOW_NORMAL);// Create a window for display.

    imshow("A", A);                   // Show our image inside it.

    waitKey(10);                                          // Wait for a keystroke in the window

    Mat A2(500, 500, CV_8UC1, Scalar(0));   //Lineas horizontales
    
    for (int i = 0; i < A2.cols; i++) {
       
        for (int j = 0; j < A2.rows; j++) {
            if (j % 2 == 0) {
                col ^= 0xff;       //define tamaño de linea y cambia el color para rellenar
            }
           
            A2.at<uchar>(j, i) = (uchar)(col);
        }
    }

    namedWindow("A2", WINDOW_AUTOSIZE);// Create a window for display.
    //namedWindow("Display window", WINDOW_NORMAL);// Create a window for display.

    imshow("A2", A2);                   // Show our image inside it.

    waitKey(10);

    Mat A3(500, 500, CV_8UC1, Scalar(0));

    for (int i = 0; i < A3.cols; i++) {
        if (i % 3 == 0) {
            col ^= 0xff;
        }
        for (int j = 0; j < A3.rows; j++) {
            A3.at<uchar>(j, i) = (uchar)(col);
        }
    }

    namedWindow("A3", WINDOW_AUTOSIZE);// Create a window for display.
    //namedWindow("Display window", WINDOW_NORMAL);// Create a window for display.

    imshow("A3", A3);                   // Show our image inside it.

    waitKey(10);

    /**************          AJEDREZ           ***********/
    col = 0;
    Mat Chess(500, 500, CV_8UC1, Scalar(0));
    int num = 6;
    bool a = false;
    for (int i = 0; i < Chess.rows; i++) {  //vertical
        if ((i % (50)) == 0) {
            col ^= 0xff;
            
        }
        for (int j = 0; j < Chess.cols; j++) {  // horizontal

            if (j % 50 == 0) {
                col ^= 0xff;
            }
       
            Chess.at<uchar>(j, i) = (uchar)(col);
        }
    }

    namedWindow("Chess", WINDOW_AUTOSIZE);// Create a window for display.
    //namedWindow("Display window", WINDOW_NORMAL);// Create a window for display.

    imshow("Chess", Chess);                   // Show our image inside it.

    waitKey(10);

    
/**************          degradado HOR          ***********/
    col = 0;
    Mat deg(500, 500, CV_8UC1, Scalar(0));
    float num1 = 0;
    float aux = 255.0 / (float)deg.cols;
   
    for (int i = 0; i < deg.rows; i++) {  //vertical
        num1 += aux;
        for (int j = 0; j < deg.cols; j++) {  // horizontal
            //num1 += aux;

            deg.at<uchar>(j, i) = (uchar)(num1);
        }
    }

    namedWindow("deg", WINDOW_AUTOSIZE);// Create a window for display.
    //namedWindow("Display window", WINDOW_NORMAL);// Create a window for display.

    imshow("deg", deg);                   // Show our image inside it.

    waitKey(10);

    /**************          degradado DIAG         ***********/
    col = 0;
    Mat deg1(500, 500, CV_8UC1, Scalar(0));
    float inicial = 0.0;
    num1 = 0.0;
    aux = (255.0 / (float)deg.cols) /2;

    for (int i = 0; i < deg1.rows; i++) {  //vertical 
        inicial += aux;
        num1 = inicial;
        
        for (int j = 0; j < deg1.cols; j++) {  // horizontal
            num1 += aux;


            deg1.at<uchar>(j, i) = (uchar)(num1);
        }
    }

    namedWindow("Degradado Diagonal", WINDOW_AUTOSIZE);// Create a window for display.
    //namedWindow("Display window", WINDOW_NORMAL);// Create a window for display.

    imshow("Degradado Diagonal", deg1);                   // Show our image inside it.

    waitKey(10);

    /**************          Cuadrilatero         ***********/
    col = 255;
    int desface = 0;
    Mat cuad(500, 500, CV_8UC1, Scalar(0));
    for (int a = 0; a < 4; a++) {
        for (int i = desface; i < (cuad.rows - desface); i++) {  //vertical 
            for (int j = desface; j < (cuad.cols - desface); j++) {  // horizontal
                cuad.at<uchar>(j, i) = (uchar)(col);
            }
        }
        desface += 75;
        col ^= 255;
    }

    namedWindow("Cuadrilatero", WINDOW_AUTOSIZE);// Create a window for display.
    //namedWindow("Display window", WINDOW_NORMAL);// Create a window for display.

    imshow("Cuadrilatero", cuad);                   // Show our image inside it.

    waitKey(0);

    return 0;

}