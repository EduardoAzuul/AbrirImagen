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

// Pasamos q1 por referencia y corregimos el acceso a vecinos
/*
void funcionG(int j, int i, int contador, Mat& A, Mat& Marcados, queue<Point>& q1) {
    if (A.at<uchar>(j, i) == 255 && Marcados.at<uchar>(j, i) == 0) {
        Marcados.at<uchar>(j, i) = contador;

        for (int a = -1; a <= 1; a++) {
            for (int b = -1; b <= 1; b++) {
                
                if (j + a >= 0 && j + a < A.rows && i + b >= 0 && i + b < A.cols) {
                    if (A.at<uchar>(j + a, i + b) == 255 && Marcados.at<uchar>(j + a, i + b) == 0) {
                        q1.push(Point(i + b, j + a));
                    }
                }
            }
        }
    }

    while (!q1.empty()) {  // Mientras la cola no esté vacía
        Point current = q1.front();  // Tomamos el primer elemento
        q1.pop();  // Lo eliminamos de la cola

        if (Marcados.at<uchar>(current.y, current.x) == 0) {
            Marcados.at<uchar>(current.y, current.x) = contador;

            for (int a = -1; a <= 1; a++) {
                for (int b = -1; b <= 1; b++) {
                    // Verificamos que los índices estén dentro de los límites
                    if (current.y + a >= 0 && current.y + a < A.rows && current.x + b >= 0 && current.x + b < A.cols) {
                        if (A.at<uchar>(current.y + a, current.x + b) == 255 && Marcados.at<uchar>(current.y + a, current.x + b) == 0) {
                            q1.push(Point(current.x + b, current.y + a));
                        }
                    }
                }
            }
        }
    }
}*/

int A10main() {
    Mat A = imread("Kiwi.png", IMREAD_GRAYSCALE);   // Leemos la imagen en escala de grises
    if (A.empty()) {
        cout << "No se pudo cargar la imagen." << endl;
        return -1;
    }

    int umbral = 50;

    // Aplicamos el umbral
    for (int i = 0; i < A.cols; i++) {
        for (int j = 0; j < A.rows; j++) {
            if (A.at<uchar>(j, i) > umbral) {
                A.at<uchar>(j, i) = 255;
            }
            else {
                A.at<uchar>(j, i) = 0;
            }
        }
    }

    namedWindow("MASCARA", WINDOW_AUTOSIZE);
    imshow("MASCARA", A);
    waitKey(10);

    // Matriz de erosión
    Mat matriz = (Mat_<float>(3, 3) <<
        0, 255, 0,
        255, 255, 255,
        0, 255, 0);

    Mat Erosion = A.clone();  // Copiamos A para aplicar la erosión
    for (int i = 1; i < A.cols - 1; i++) {
        for (int j = 1; j < A.rows - 1; j++) {
            bool erosion = true;
            for (int mono = -(matriz.cols / 2); mono <= (matriz.cols / 2); mono++) {
                if (!erosion) break;
                for (int mango = -(matriz.cols / 2); mango <= (matriz.cols / 2); mango++) {
                    if (matriz.at<float>(mango + 1, mono + 1) == 255 && A.at<uchar>(j + mango, i + mono) == 0) {
                        erosion = false;
                        break;
                    }
                }
            }
            Erosion.at<uchar>(j, i) = erosion ? 255 : 0;
        }
    }

    namedWindow("Erosion", WINDOW_AUTOSIZE);
    imshow("Erosion", Erosion);
    waitKey(10);

    Mat Expansion = A.clone();  // Copiamos A para aplicar la erosión
    for (int i = 1; i < A.cols - 1; i++) {
        for (int j = 1; j < A.rows - 1; j++) {
            bool erosion = false;
            for (int mono = -(matriz.cols / 2); mono <= (matriz.cols / 2); mono++) {
                if (erosion) break;
                for (int mango = -(matriz.cols / 2); mango <= (matriz.cols / 2); mango++) {
                    if (matriz.at<float>(mango + 1, mono + 1) == 255 && A.at<uchar>(j + mango, i + mono) == 255) {
                        erosion = true;
                        break;
                    }
                }
            }
            Expansion.at<uchar>(j, i) = erosion ? 255 : 0;
        }
    }

    namedWindow("Expansion", WINDOW_AUTOSIZE);
    imshow("Expansion", Expansion);
    waitKey(10);


    Mat Growing = A.clone();  // Copiamos A para aplicar la erosión
    for (int i = 1; i < A.cols - 1; i++) {
        for (int j = 1; j < A.rows - 1; j++) {
            bool erosion = false;
            for (int mono = -(matriz.cols / 2); mono <= (matriz.cols / 2); mono++) {
                if (erosion) break;
                for (int mango = -(matriz.cols / 2); mango <= (matriz.cols / 2); mango++) {
                    if (matriz.at<float>(mango + 1, mono + 1) == 255 && A.at<uchar>(j + mango, i + mono) == 255) {
                        erosion = true;
                        break;
                    }
                }
            }
            Growing.at<uchar>(j, i) = erosion ? 255 : 0;
        }
    }

    namedWindow("Growing", WINDOW_AUTOSIZE);
    imshow("Growing", Growing);
    waitKey(10);

    // Iniciamos la matriz de marcados
    Mat Marcados = Mat::zeros(A.size(), CV_8UC1);  // Matriz de ceros del tamaño de A

    int contador = 20;  // Iniciamos el contador para las regiones conectadas
    queue<Point> q1;

    for (int i = 1; i < A.cols - 1; i++) {
        for (int j = 1; j < A.rows - 1; j++) {
            if (A.at<uchar>(j, i) == 255 && Marcados.at<uchar>(j, i) == 0) {
                //funcionG(j, i, contador, A, Marcados, q1);
                contador++;
            }
        }
    }

    namedWindow("Marcados", WINDOW_AUTOSIZE);
    imshow("Marcados", Marcados);
    waitKey(0);

    return 0;
}
