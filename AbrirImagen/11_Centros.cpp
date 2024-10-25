#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace cv;
using namespace std;

// Pasamos q1 por referencia y corregimos el acceso a vecinos
void funcionG(int j, int i, int contador, Mat& A, Mat& Marcados, queue<Point>& q1) {
    if (A.at<uchar>(j, i) == 255 && Marcados.at<uchar>(j, i) == 0) {
        Marcados.at<uchar>(j, i) = contador;

        for (int a = -1; a <= 1; a++) {
            for (int b = -1; b <= 1; b++) {
                // Verificamos que los índices estén dentro de los límites de la imagen
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
}


void detectarFormas(Mat& imagen) {
    vector<vector<Point>> contornos;
    vector<Vec4i> jerarquia;

    findContours(imagen, contornos, jerarquia, RETR_TREE, CHAIN_APPROX_SIMPLE);
    for (size_t i = 0; i < contornos.size(); i++) {
        drawContours(imagen, contornos, (int)i, Scalar(200), 2); // imagen a aplicar, vector de contornos, indica contornos a dibujar, color a dibujar, grosor


    }

}



int main() {
    Mat A = imread("figuresEq1.png", IMREAD_GRAYSCALE);   // Leemos la imagen en escala de grises
    if (A.empty()) {
        cout << "No se pudo cargar la imagen." << endl;
        return -1;
    }

    int umbral = 150;

    namedWindow("Circulos", WINDOW_AUTOSIZE);
    imshow("Circulos", A);
    waitKey(10);

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

    Mat image3 = A.clone();
    Mat image4 = A.clone();
    const int tam2 = 3;
    int array[tam2 * tam2] = { 0 };
    int Borde = 2;
    Borde = (tam2 - 1) / 2;

    vector < int > valores(tam2 * tam2, 0);  //vector de tam2*tam2, lleno de 0


    for (int i = Borde; i < image3.cols - Borde; i++) {  //vertical 
        for (int j = Borde; j < image3.rows - Borde; j++) {  // horizontal

            
            for (int mono = -Borde; mono <= Borde; mono++) {
                for (int mango = -Borde; mango <= Borde; mango++) {
                    valores.push_back(image3.at<uchar>(j + mono, i + mango));
                }
            }

            sort(valores.begin(), valores.end(), greater<int>());
            A.at<uchar>(j, i) = valores[(tam2 * tam2) / 2];
            valores.clear();

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
    int cantidadRegiones = 0;
    queue<Point> q1;

    for (int i = 1; i < A.cols - 1; i++) {
        for (int j = 1; j < A.rows - 1; j++) {
            if (A.at<uchar>(j, i) == 255 && Marcados.at<uchar>(j, i) == 0) {
                funcionG(j, i, contador, A, Marcados, q1);
                contador++;
                cantidadRegiones++; //contamos la cantidad de regiones que tenemos
            }
        }
    }


    namedWindow("Marcados", WINDOW_AUTOSIZE);
    imshow("Marcados", Marcados);
    waitKey(10);



    Mat Contornos = Marcados.clone();

    detectarFormas(Contornos);

    namedWindow("Contornos", WINDOW_AUTOSIZE);
    imshow("Contornos", Contornos);
    waitKey(0);

    vector<Point> lista2;
    vector<vector<Point>> listaReg;
    vector<Point> Region1;
    int aux = 0;
    for (int region = 0; region < cantidadRegiones; region++) {
        Region1.clear();
        for (int i = 1; i < Contornos.cols - 1; i++) {
            for (int j = 1; j < Contornos.rows - 1; j++) {
                if (Contornos.at<uchar>(j, i) == region + 20) {
                    Region1.push_back(Point(i, j));
                }
            }
        }

        listaReg.push_back(Region1);

    }

    sort(listaReg.begin(), listaReg.end(),[](const vector<Point>& a, const vector<Point>& b) {
            return a.size() > b.size();
        });

    Mat Prueba = Marcados.clone();

    for (int i = 1; i < Prueba.cols - 1; i++) {
        for (int j = 1; j < Prueba.rows - 1; j++) {
            Prueba.at<uchar>(j, i) = 0;
        }
    }

    vector<Point> AuxiliarDeRep;
    vector<Point> centros;          //vector que contiene los centros de las regiones como puntos
    vector<Point> esquinaInferior;
    vector<Point> esquinaSuperior;
    int xs = 0;
    int ys = 0;

    int xmin = 0, xmax = 0, ymin = 0, ymax = 0;
    bool primera = true;

    Point temo;
    for (int region = 0; region < cantidadRegiones; region++) {
        AuxiliarDeRep = listaReg[region];
        aux = 0;
        while (AuxiliarDeRep.empty() == false) {
            temo = AuxiliarDeRep.back(); // Obtén el último elemento
            AuxiliarDeRep.pop_back();
            Prueba.at<uchar>(temo.y, temo.x) = 255;

            if (primera) {
                xmin = temo.x;
                xmax = temo.x;
                ymin = temo.y;
                ymax = temo.y;
                primera = false;
            }

            else {
                if (temo.x < xmin) xmin = temo.x;
                if (temo.x > xmax) xmax = temo.x;
                if (temo.y < ymin) ymin = temo.y;
                if (temo.y > ymax) ymax = temo.y;
            }


            ys += temo.y;
            xs += temo.x;
            aux++;
        }
        primera = true;
        centros.push_back(Point(xs / aux, ys / aux));
        esquinaInferior.push_back(Point(xmin, ymin));
        esquinaSuperior.push_back(Point(xmax, ymax));

        xs = 0;
        ys = 0;
        /*
        Prueba.at<uchar>(centros.back()) = 0;
        Prueba.at<uchar>(esquinaInferior.back()) = 255;
        Prueba.at<uchar>(esquinaSuperior.back()) = 255;
        */
    }

    // Especifica la fuente, tamaño, color, grosor y tipo de línea
    int fuente = FONT_HERSHEY_SIMPLEX;
    double tamanoFuente = 0.6;
    Scalar color(150);
    int grosor = 1;
    int tipoLinea = LINE_AA;

    Mat canny_output;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    Canny(Prueba, canny_output, 200, 200);
    findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
    namedWindow("canny output", WINDOW_AUTOSIZE);
    imshow("canny output", canny_output);

    sort(contours.begin(), contours.end(), [](const vector<Point>& a, const vector<Point>& b) {
        return contourArea(a, false) > contourArea(b, false);
     });


    string texto = "CENTRO";
    int pixelesTotales = 0;
    int tamx = 0, tamy = 0;
    int circulos = 0;
    int cantidadContronos = 0;
    for (int region = 0; region < cantidadRegiones; region++) {

        texto = "cuadrado";

        

        aux = 0;
        pixelesTotales = 0;

        //Cuenta el area
        for (int i = esquinaInferior.at(region).y; i < esquinaSuperior.at(region).y; i++) {
            for (int j = esquinaInferior.at(region).x; j < esquinaSuperior.at(region).x; j++) {
                if (Prueba.at<uchar>(i, j) == 255) {
                    aux++;

                }
                pixelesTotales++;

            }
        }

        
        
        if (aux < (pixelesTotales * 0.80)) {
            texto = "Amalgama";
        }
        tamx = esquinaSuperior.at(region).x - esquinaInferior.at(region).x;
        tamy = esquinaSuperior.at(region).y - esquinaInferior.at(region).y;
        int redondez = 0;

        cantidadContronos = contours[region].size();
        if (aux < (pixelesTotales * 0.90) && aux >(pixelesTotales * 0.70)) {
            if (tamx < tamy * 1.15 && tamx > tamy * .85) {
                
                redondez = (pixelesTotales * 4 * 3.141516) / (cantidadContronos * cantidadContronos);
                
                if (redondez > 0.8) {
                    circulos++;
                    texto = "Circulo";
                }

            }
        }

        // Escribe el texto en la imagen
        putText(Prueba, texto, (centros.at(region)), fuente, tamanoFuente, color, grosor, tipoLinea);
        
    }

    putText(Prueba, to_string(circulos), (Point(50, 50)), fuente, 1, 250, grosor, tipoLinea);
    namedWindow("Prueba", WINDOW_AUTOSIZE);
    imshow("Prueba", Prueba);



    waitKey(0);
}