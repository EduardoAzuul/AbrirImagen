#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace cv;
using namespace std;

int A8main() {

    Mat image,image2;


    image = imread("Kevin.png", IMREAD_GRAYSCALE);   // Read the file
    image2 = image;



    if (!image.data) {
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    namedWindow("flores", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("flores", image);                   // Show our image inside it.

    waitKey(10);


    const int tam = 5;
    int Borde = 2;
    int aux;

    for (int i = Borde; i < image.cols- Borde; i++) {  //vertical 
        for (int j = Borde; j < image.rows- Borde; j++) {  // horizontal
            aux = 0;
            for (int mono = -Borde; mono <= Borde; mono++) {
                for (int mango = -Borde; mango <= Borde; mango++) {
                    aux+= image2.at<uchar>(j+mono, i+mango);
                }
            }
            //tam = tam + tam + 1;
            image2.at<uchar>(j, i)=aux/(tam*tam);
            
        }
    }

    namedWindow("Blur", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("Blur", image2);                   // Show our image inside it.

    waitKey(10);

    /****************************************/
    Mat image3, image4;
    image3 = imread("paris.jpg", IMREAD_GRAYSCALE);   // Read the file
    image4 = imread("paris.jpg", IMREAD_GRAYSCALE);

    if (!image3.data) {
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    namedWindow("Sal & Pimienta", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("Sal & Pimienta", image3);                   // Show our image inside it.

    waitKey(10);

    const int tam2 = 3;
    int array[tam2*tam2] = { 0 };
    Borde = (tam2 - 1) / 2;

    vector < int > valores(tam2*tam2,0);  //vector de tam2*tam2, lleno de 0

    

    for (int i = Borde; i < image3.cols - Borde; i++) {  //vertical 
        for (int j = Borde; j < image3.rows - Borde; j++) {  // horizontal

            for (int mono = -Borde; mono <= Borde; mono++) {
                for (int mango = -Borde; mango <= Borde; mango++) {

                    valores.push_back(image3.at<uchar>(j + mono, i + mango));

                }
            }

            sort(valores.begin(), valores.end(), greater<int>());
            image4.at<uchar>(j, i) = valores[(tam2 * tam2)/2];
            valores.clear();

        }
    }


    namedWindow("Desabrido", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("Desabrido", image4);                   // Show our image inside it.

    waitKey(10);

    /*******************************************/

    Mat image5;
    image5 = imread("Kiwi.png", IMREAD_GRAYSCALE);   // Read the file

    if (!image5.data) {
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    
    Mat image6 = (Mat_<float>(3, 3) << 
        1,2,1,
        2,4,2,
        1,2,1);

    namedWindow("Kiwi", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("Kiwi", image5);                   // Show our image inside it.

    waitKey(10);
    aux = 0;

    for (int i = 1; i < image5.cols - 1; i++) {  //vertical 
        for (int j = 1; j < image5.rows - 1; j++) {  // horizontal

            for (int mono = -1; mono <= 1; mono++) {
                for (int mango = -1; mango <= 1; mango++) {

                    aux += (  image5.at<uchar>(j + mono, i + mango) * image6.at<float>(mono + 1, mango + 1)  );

                }
            }
            aux = aux / 16;

            image5.at<uchar>(j, i) = aux;

        }
    }

    

    
    int m = 19;
    int n = 19;
    int x0 = m / 2;
    int y0 = n / 2;
    float sigma = 1;
    int x = 0;
    int y = 0;
    float texp = 0, tconst=0;

    Mat mascara = (Mat_<float>(19, 19) ={ 0 });
    float total = 0;
    for (int i = 0; i < m - 1; i++) {  //vertical 
        for (int j = 0; j < n - 1; j++) {  // horizontal
            x = i - x0; 
            y = y0 - j;

            texp = (x * x + y * y) / (2 * sigma * sigma);
            tconst = 1 / sigma * sigma * 2 * 3.141516;

            mascara.at<float>(i, j)= tconst*exp(-texp);
            total += tconst * exp(-texp);

        }
    }

    namedWindow("Mascara", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("Mascara", mascara);                   // Show our image inside it.

    waitKey(10);


    Mat image10;
    image10 = imread("Kiwi.png", IMREAD_GRAYSCALE);   // Read the file
    Mat image11;
    image11 = imread("Kiwi.png", IMREAD_GRAYSCALE);   // Read the file

    for (int i = 9; i < image10.cols - 9; i++) {  //vertical 
        for (int j = 9; j < image10.rows - 9; j++) {  // horizontal

            for (int mono = -9; mono <= 9; mono++) {
                for (int mango = -9; mango <= 9; mango++) {

                    aux += (image10.at<uchar>(j + mono, i + mango) * mascara.at<float>(mono + 9, mango + 9));

                    
                }
            }
            aux = aux / total;
            image11.at<uchar>(j, i) = aux;

        }
    }

    namedWindow("Degradado Chido", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("Degradado Chido", image11);                   // Show our image inside it.

    waitKey(0);
}