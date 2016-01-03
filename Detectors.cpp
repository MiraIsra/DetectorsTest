//
//  Detectors.cpp
//  
//
//  Created by Israel Mira Antón on 26/12/15.
//
//

//*************************************************************************
// Declaracion de librerias
//*************************************************************************
#include <cassert>	// debugging
#include <iostream>	// c++ standar input/output
#include <sstream>  // string to number conversion
#include <string>	// handling strings
#include <vector>	// handling vectors
#include <math.h>	// math functions
#include <stdio.h>	// standar C input/ouput
#include <unistd.h>
#include <highgui.h>
#include <stdio.h>
#include <cv.h>
#include <time.h>
#include <cmath>
#include <cstdlib> //Para generar numeros aleatorios con random.
#include <time.h> //Para calcular el tiempo de computo de las operaciones.

#include <opencv2/opencv.hpp>  // OpenCV library headers
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/core/core.hpp"
//*************************************************************************
// C++ namespaces C++ (avoid using prefix for standard and openCV classes)
//*************************************************************************
using namespace std;
using namespace cv;
//*************************************************************************
// Funciones utilizadas en esta clase main.
//*************************************************************************
//Funcion de manejo de eventos
void MouseHandler (int event, int x, int y, int flags, void* param);

//Funciones para abrir y cerrar las ventanas de configuracion de los detectores
bool AbrirVentanaConfiguracion (string detector);
bool CerrarVentanaConfiguracion ();


//Funcion de lectura de imagenes de botones
Mat LeerImagenesBotones(Mat draw_botones);

Mat InicializarBotones(Mat draw_botones);

Mat ActualizarBotones (Mat draw_botones);

//Funcion detector que debera actualizar los descriptores cuando detecte nuevos puntos.
//Esta funcion hace deteccion de puntos y descripcion de caracteristicas dependiendo del matcher escogido.
vector <KeyPoint> DetectorHarris (Mat);
vector <KeyPoint> DetectorBrisk (Mat);
vector <KeyPoint> DetectorORB (Mat);
//vector <KeyPoint> DetectorFreak (Mat);  No hay se usa el ORB
vector <KeyPoint> DetectorStart (Mat);
vector <KeyPoint> DetectorDense (Mat);
vector <KeyPoint> DetectorMser (Mat);
vector <KeyPoint> DetectorSB (Mat);
vector <KeyPoint> DetectorSift (Mat);
vector <KeyPoint> DetectorSurf (Mat);
vector <KeyPoint> DetectorGeneral (Mat);


//Funcion para leer las imagenes.
Mat LeerImagenes(Mat imagenI, Mat draw_image, Mat gray_image1, Mat HSV_image1);

//*************************************************************************
// Constantes
//*************************************************************************
const char  * WINDOW_CAMERAS  = "Ventana Imagenes";	// windows id
const char * VENTANA_BOTONES = "Ventana Botones";
const char * VENTANA_CONFIGURACION = "Ventana Configuracion";
const char * IMAGENES_RECORTADAS = "Ventana Correspondencia";
const char* nombreTrackbar = "Distanciamiento:";

const char* ThreshlnombreTrackbar ="Threshl:";
const char* OctavesnombreTrackbar ="Octaves:";
const char* PatternScalesnombreTrackbar ="PatternScales:";

const char* maxSizeNombreBarra = "MaxSize:";
const char* responseThresholdNombreBarra = "Response Threshold:";
const char* lineThresholdProjectedNombreBarra = "Line Threshold Protected:";
const char* lineThresholdBinarizedNombreBarra = "Line Threshold Binarized";
const char* suppressNonmaxSizeNombreBarra = "Suppres Non-max Size:";

const char* initFeatureScaleNombreBarra = "Init feature scale:";
const char* featureScaleLevelsNombreBarra = "Feature scale levels:";
const char* featureScaleMulNombreBarra = "feature scale multiple:";
const char* initXyStepNombreBarra = "Initiation step in axis x-y:";
const char* initImgBoundNombreBarra = "initiation Image boundaries:";
const char* varyXyStepWithScaleNombreBarra = "Variation x-y step with scales:";
const char* varyImgBoundWithScaleNombreBarra = "Variation images boundaries:";

const char* deltaNombreBarra = "Delta:";
const char* minAreaNombreBarra = "Min. area:";
const char* maxAreaNombreBarra = "Max. Area:";
const char* maxVariationNombreBarra = "Max. variation:";
const char* minDiversityNombreBarra = "Min. diversity:";
const char* maxEvolutionNombreBarra = "Max. evolution:";
const char* areaThresholdNombreBarra = "Ares threshold:";
const char* minMarginNombreBarra = "Min. margin:";
const char* edgeBlurSizeNombreBarra = "Edge blur size:";

//const char* thresholdStepNB = "Treshold step:";
const char* minThresholdNB = "Min. Threshold:";
const char* maxThresholdNB = "Max. Threshold:";
//const char* minRepeatabilityNB = "Min. repeatability:";
const char* minDistBetweenBlobsNB = "Min. dist. vs blobs:";
const char* filterColourNB = "Filter by color(1-Yes):";
const char* blobColorNB = "Colours:255-light";
const char* filterAreaNB = "Filter by area (1-Yes):";
const char* minAreaNB = "Min. Area";
const char* maxAreaNB = "Max. Area:";
const char* filterCircularityNB = "Filter by circularity:";
const char* minCircularityNB = "Min. Circularity:";
const char* filterInertiaNB = "Filter by inertia:";
const char* minInertiaRatioNB = "Min. inertia ratio:";
const char* filterConvexityNB = "Filter by convexity:";
const char* minConvexityNB = "Min. Convexity:";

const Size camSize (640, 480);

//*************************************************************************
// Variables Globales
//*************************************************************************
Size buttonSize (140, 39);
Mat capture;


//Botones de deteccion
Mat botonHarris;
Mat botonBrisk;
Mat botonORB;
Mat botonFreak;
Mat botonMser;
Mat botonStar;
Mat botonDense;
Mat botonSimpleBlob;
Mat botonSift;
Mat botonSurf;
//Declaracion de las variables donde vamos a leer las imagenes de los botones
//Botones de deteccion
Mat botonHarrisOn;
Mat botonHarrisOff;
Mat botonBriskOn;
Mat botonBriskOff;
Mat botonORBOn;
Mat botonORBOff;
Mat botonFreakOn;
Mat botonFreakOff;
Mat botonStarOn;
Mat botonStarOff;
Mat botonDenseOn;
Mat botonDenseOff;
Mat botonMserOn;
Mat botonMserOff;
Mat botonSimpleBlobOn;
Mat botonSimpleBlobOff;
Mat botonSiftOn;
Mat botonSiftOff;
Mat botonSurfOn;
Mat botonSurfOff;
//Declaracion de las variables de los botones
//Botones de deteccion
bool botonHarrisPulsado = false;
bool botonBriskPulsado = false;
bool botonORBPulsado = false;
bool botonFreakPulsado = false;
bool botonStarPulsado = false;
bool botonDensePulsado = false;
bool botonMserPulsado = false;
bool botonSimpleBlobPulsado = false;
bool botonSiftPulsado = false;
bool botonSurfPulsado = false;

//Booleana para controlar la ventana de configuracion
bool ventanaConfiguracionAbierta = false;

//Variables de entrada de imagen
bool entradaCorrecta = false;
int main (int argc, char * const argv[])
{
    float altura_camaras = 0;
    //*************************
    //  Declaracion de variables utilizadas en el main.
    //************************
    Mat draw_image;
    Mat draw_botones;
    Mat gray_image;
    Mat HSV_image;
    Mat imagenI;
    Mat imagenD;
    //Variables de la toma de fotos
    VideoCapture camera;
    int CAMERA_ID  = 0;
    int key;
    
    //Variables para leer las imagenes.
    string nombreImagenI;
    string nombreImagenD;
    
    //Variables para la deteccion de puntos caracteristicos
    vector<KeyPoint> keypoints;
    Mat descriptors;
    //Se leen e inicializan los botones
    draw_botones = LeerImagenesBotones(draw_botones);
    draw_botones = InicializarBotones (draw_botones);
    draw_botones = ActualizarBotones (draw_botones);
    
    //Se monta y muestra la ventana de los botones
    namedWindow (VENTANA_BOTONES, WINDOW_AUTOSIZE);
    
    //************************************
    //  Leemos las imagenes de entrada
    //************************************
    if (!argv[1]){
        //Comprovacion de que las dos camaras estan conectadas.
        
            camera.open(CAMERA_ID);
            if (!camera.isOpened()){
                cout << "Conecta las dos camaras por favor, sino no va a ir." << endl;
                //getchar();
                return -1;
            }
            camera.set(CV_CAP_PROP_FRAME_WIDTH, camSize.width);
            camera.set(CV_CAP_PROP_FRAME_HEIGHT, camSize.height);
        
    }
    
    else {
        entradaCorrecta = true;
        nombreImagenI = argv[1];
    }
    
    //Montamos la imagenes ya sean leidas por camara o por archivo de imanen.
    draw_image = LeerImagenes(imagenI, draw_image, gray_image, HSV_image);
    
    //Mostramos las imagenes
    imshow (VENTANA_BOTONES, draw_botones);
    imshow (WINDOW_CAMERAS, WINDOW_AUTOSIZE);
    
    //Añadimos la interacción con el raton.
    // 	Mouse Handler
    setMouseCallback( VENTANA_BOTONES, MouseHandler, NULL );
    
    //Para salir del programa.
    cout << "Presione q/Q para salir.\n";
    
    while (1) {
        if (!argv[1]){
            //Para cada camara...
            
                //Lee la imagen
                camera.read(capture);
                waitKey (50);
                capture.copyTo(imagenI);
            
        }
        else{
            imagenI = imread (nombreImagenI, CV_LOAD_IMAGE_COLOR);
            
            draw_image = LeerImagenes(imagenI, draw_image, gray_image, HSV_image);
            //Limpiar lsa imagenes de  puntos y maching
            waitKey(50);
        }
        
        //Pasamos la imagen a escala de grises y separamos en HSV.
        cvtColor (capture, gray_image, CV_BGR2GRAY);
        cvtColor (capture, HSV_image, CV_BGR2HSV);
        
        
        //Limpiamos los keypoints encontrados en la iteracion de antes
        
            keypoints.clear();
        
        //********************************************
        //Interacciones con los botones de deteccion
        //********************************************
        if (botonHarrisPulsado) {
            botonHarrisOn.copyTo(botonHarris);
            float inicio, fin, t;
            inicio=clock();
            
                keypoints = DetectorHarris (gray_image);
            
        }
        else botonHarrisOff.copyTo(botonHarris);
        
        if (botonBriskPulsado) {
            botonBriskOn.copyTo(botonBrisk);
            //Creamos las barras para controlar los parámetros
            if (!ventanaConfiguracionAbierta) {
                //ventanaConfiguracionAbierta = AbrirVentanaConfiguracion ("brisk");
                //Configuramos las barras para el detector sift
                //Declaracion variables
                //int Threshl=60;
                //int Octaves=4; //(pyramid layer) from which the keypoint has been extracted
                //float PatternScales=1.0f;
                //Variables relacionadas con la inicializacion de la barra
                //int thresh = 200;
                //int max_thresh = 255;
                int ThreshlInicial = 60;
                int MaxThreshl = 100;
                int OctavesInicial = 4;
                int MaxOctaves = 10;
                int PatternScalesInicial = 100;
                int MaxPatternScales = 200;
                
                createTrackbar (ThreshlnombreTrackbar, VENTANA_CONFIGURACION, &ThreshlInicial, MaxThreshl);
                createTrackbar (OctavesnombreTrackbar, VENTANA_CONFIGURACION, &OctavesInicial, MaxOctaves);
                createTrackbar (PatternScalesnombreTrackbar, VENTANA_CONFIGURACION, &PatternScalesInicial, MaxPatternScales);
                
                //Se monta y muestra la ventana de los botones
                namedWindow (VENTANA_CONFIGURACION, WINDOW_NORMAL);
                //Añadimos la interacción con el raton.
                // 	Mouse Handler
                setMouseCallback( VENTANA_CONFIGURACION, MouseHandler, NULL );
                //draw_configuracion.create (camSize.height, camSize.width, CV_8UC3);
                //Mostramos las imagenes
                imshow (VENTANA_CONFIGURACION, WINDOW_AUTOSIZE);
                waitKey (1000);
            }
            
            float inicio, fin, t;
            inicio=clock();
            
                keypoints = DetectorBrisk (gray_image);
            
            fin=clock();
            t = fin - inicio;
            cout << "Tiempo de ejecucion: " << t << endl;
            
        }
        else botonBriskOff.copyTo(botonBrisk);
        
        if (botonORBPulsado) {
            botonORBOn.copyTo(botonORB);
            //Abrimos la ventana de configuracion.
            
            float inicio, fin, t;
            inicio=clock();
            
                keypoints = DetectorORB (gray_image);
            
            fin=clock();
            t = fin - inicio;
            cout << "Tiempo de ejecucion: " << t << endl;
        }
        else    botonORBOff.copyTo(botonORB);
        
        if (botonFreakPulsado) {
            float inicio, fin, t;
            
            inicio=clock();
            botonFreakOn.copyTo(botonFreak);
            int minHessian = 1000;
            SurfFeatureDetector detector(minHessian);
            //Deteccion de puntos
            detector.detect (capture, keypoints);
            fin=clock();
            t = fin - inicio;
            cout << "Tiempo de ejecucion: " << t << endl;
        }
        else    botonFreakOff.copyTo(botonFreak);
        
        if(botonStarPulsado){
            botonStarOn.copyTo(botonStar);
            float inicio, fin, t;
            
            //Establecemos los parametros iniciales.
            //int maxSize=16, int responseThreshold=30, int lineThresholdProjected = 10, int lineThresholdBinarized=8, int suppressNonmaxSize=5 );
            int maxSizeInit = 40;
            int maxSizeMax = 128;
            int responseThresholdInit= 20;
            int responseThresholdMax = 100;
            int lineThresholdProjectedInit = 10;
            int lineThresholdProjectedMax = 50;
            int lineThresholdBinarizedInit = 8;
            int lineThresholdBinarizedMax = 50;
            int suppressNonmaxSizeInit = 5;
            int suppressNonmaxSizeMax = 10;
            
            createTrackbar (maxSizeNombreBarra, VENTANA_CONFIGURACION, &maxSizeInit, maxSizeMax);
            createTrackbar ( responseThresholdNombreBarra, VENTANA_CONFIGURACION, &responseThresholdInit, responseThresholdMax);
            createTrackbar (lineThresholdProjectedNombreBarra, VENTANA_CONFIGURACION, &lineThresholdProjectedInit, lineThresholdProjectedMax);
            createTrackbar (lineThresholdBinarizedNombreBarra, VENTANA_CONFIGURACION, &lineThresholdBinarizedInit, lineThresholdBinarizedMax);
            createTrackbar (suppressNonmaxSizeNombreBarra, VENTANA_CONFIGURACION, &suppressNonmaxSizeInit, suppressNonmaxSizeMax);
            
            //Se monta y muestra la ventana de los botones
            namedWindow (VENTANA_CONFIGURACION, WINDOW_NORMAL);
            //Añadimos la interacción con el raton.
            // 	Mouse Handler
            setMouseCallback( VENTANA_CONFIGURACION, MouseHandler, NULL );
            //draw_configuracion.create (camSize.height, camSize.width, CV_8UC3);
            //Mostramos las imagenes
            imshow (VENTANA_CONFIGURACION, WINDOW_AUTOSIZE);
            waitKey (1000);
            
            inicio=clock();
            //Extractor de caracteristicas SIFT.
            
                keypoints = DetectorStart (gray_image);
                //descriptors[i] = ExtractorSift (gray_image[i], keypoints[i]);
            
            fin=clock();
            t = fin - inicio;
            cout << "Tiempo de ejecucion: " << t << endl;
            
        }
        else    botonStarOff.copyTo(botonStar);
        
        if (botonDensePulsado){
            botonDenseOn.copyTo(botonDense);
            float inicio, fin, t;
            
            int initFeatureScaleInit = 10;
            int initFeatureScaleMax = 20;
            int featureScaleLevelsInit = 1;
            int featureScaleLevelsMax = 5;
            int featureScaleMulInit = 10;
            int featureScaleMulMax = 20;
            int initXyStepInit = 6;
            int initXyStepMax = 20;
            int initImgBoundInit = 0;
            int initImgBoundMax = 10;
            int varyXyStepWithScaleInit = 1;
            int varyXyStepWithScaleMax = 1;
            int varyImgBoundWithScaleInit = 0;
            int varyImgBoundWithScaleMax = 1;
            
            createTrackbar (initFeatureScaleNombreBarra, VENTANA_CONFIGURACION, &initFeatureScaleInit, initFeatureScaleMax);
            createTrackbar (featureScaleLevelsNombreBarra, VENTANA_CONFIGURACION, &featureScaleLevelsInit, featureScaleLevelsMax);
            createTrackbar (featureScaleMulNombreBarra, VENTANA_CONFIGURACION, &featureScaleMulInit, featureScaleMulMax);
            createTrackbar (initXyStepNombreBarra, VENTANA_CONFIGURACION, &initXyStepInit, initXyStepMax);
            createTrackbar (initImgBoundNombreBarra, VENTANA_CONFIGURACION, &initImgBoundInit, initImgBoundMax);
            createTrackbar (varyXyStepWithScaleNombreBarra, VENTANA_CONFIGURACION, &varyXyStepWithScaleInit, varyXyStepWithScaleMax);
            createTrackbar (varyImgBoundWithScaleNombreBarra, VENTANA_CONFIGURACION, &varyImgBoundWithScaleInit, varyImgBoundWithScaleMax);
            
            //Se monta y muestra la ventana de los botones
            namedWindow (VENTANA_CONFIGURACION, WINDOW_NORMAL);
            //Añadimos la interacción con el raton.
            // 	Mouse Handler
            setMouseCallback( VENTANA_CONFIGURACION, MouseHandler, NULL );
            //draw_configuracion.create (camSize.height, camSize.width, CV_8UC3);
            //Mostramos las imagenes
            imshow (VENTANA_CONFIGURACION, WINDOW_AUTOSIZE);
            waitKey (1000);
            
            inicio=clock();
            
                keypoints = DetectorDense (gray_image);
                //descriptors[i] = ExtractorSift (gray_image[i], keypoints[i]);
            
            fin=clock();
            t = fin - inicio;
            cout << "Tiempo de ejecucion: " << t << endl;
        }
        else    botonDenseOff.copyTo(botonDense);
        
        if (botonMserPulsado){
            botonMserOn.copyTo(botonMser);
            //Inicializacion de constantes
            //int _delta, int _min_area, int _max_area, float _max_variation, float _min_diversity, int _max_evolution, double _area_threshold, double _min_margin, int _edge_blur_size );
            //1,            20,             60,             0.25,                   0.2,                        200,                1.01,                   0.003,              5
            /*delta =2;
            minArea = 5;
            maxArea = 15;
            maxVariationG = 0.5;
            minDiversityG = 0.2;
            maxEvolution = 50;
            areaThresholdG = 1.01;
            minMarginG = 0.3;
            edgeBlurSize = 5;*/
            
            int deltaInit = 2;
            int deltaMax = 10;
            int minAreaInit = 5;
            int minAreaMax = 100;
            int maxAreaInit = 15;
            int maxAreaMax = 8000;
            int maxVariationInit = 50;
            int maxVariationMax = 100;
            int minDiversityInit = 20;
            int minDiversityMax = 100;
            int maxEvolutionInit = 50;
            int maxEvolutionMax = 500;
            int areaThresholdInit = 101;
            int areaThresholdMax = 199;
            int minMarginInit = 3;
            int minMarginMax = 10;
            int edgeBlurSizeInit = 5;
            int edgeBlurSizeMax = 20;
            
            createTrackbar (deltaNombreBarra, VENTANA_CONFIGURACION, &deltaInit, deltaMax);
            createTrackbar (minAreaNombreBarra, VENTANA_CONFIGURACION, &minAreaInit, minAreaMax);
            createTrackbar (maxAreaNombreBarra, VENTANA_CONFIGURACION, &maxAreaInit, maxAreaMax);
            createTrackbar (maxVariationNombreBarra, VENTANA_CONFIGURACION, &maxVariationInit, maxVariationMax);
            createTrackbar (minDiversityNombreBarra, VENTANA_CONFIGURACION, &minDiversityInit, minDiversityMax);
            createTrackbar (maxEvolutionNombreBarra, VENTANA_CONFIGURACION, &maxEvolutionInit, maxEvolutionMax);
            createTrackbar (areaThresholdNombreBarra, VENTANA_CONFIGURACION, &areaThresholdInit, areaThresholdMax);
            createTrackbar (minMarginNombreBarra, VENTANA_CONFIGURACION, &minMarginInit, minMarginMax);
            createTrackbar (edgeBlurSizeNombreBarra, VENTANA_CONFIGURACION, &edgeBlurSizeInit, edgeBlurSizeMax);
            
            //Se monta y muestra la ventana de los botones
            namedWindow (VENTANA_CONFIGURACION, WINDOW_NORMAL);
            //Añadimos la interacción con el raton.
            // 	Mouse Handler
            setMouseCallback( VENTANA_CONFIGURACION, MouseHandler, NULL );
            //draw_configuracion.create (camSize.height, camSize.width, CV_8UC3);
            //Mostramos las imagenes
            imshow (VENTANA_CONFIGURACION, WINDOW_AUTOSIZE);
            waitKey (1000);
            
            float inicio, fin, t;
            inicio=clock();
           
                keypoints = DetectorMser (gray_image);
               // descriptors[i] = ExtractorSift (gray_image[i], keypoints[i]);
            
            fin=clock();
            t = fin - inicio;
            cout << "Tiempo de ejecucion: " << t << endl;
        }
        else    botonMserOff.copyTo(botonMser);
        
        if (botonSimpleBlobPulsado){
            botonSimpleBlobOn.copyTo(botonSimpleBlob);
            float inicio, fin, t;
            
            /* Change thresholds
            params.minThreshold = 10;
            params.maxThreshold = 200;
            
            //  Change by Color
            params.filterByColor = 1;
            params.blobColor = 160;
            
            // Filter by Area.
            params.filterByArea = true;
            params.minArea = 5;
            params.maxArea = 20;
            
            // Filter by Circularity
            params.filterByCircularity = true;
            params.minCircularity = 0.9; //0.1
            
            // Filter by Convexity
            params.filterByConvexity = true;
            params.minConvexity = 0.87; //0.87
            
            // Filter by Inertia
            params.filterByInertia = true;
            params.minInertiaRatio = 0.01;*/
            int minThresholdInit = 10;
            int minThresholdMax = 20;
            int maxThresholdInit = 200;
            int maxThresholdMax = 500;
            int filterColorInit = 1;
            int filterColorMax = 1;
            int blobColorInit = 130;
            int blobColorMax = 255;
            int filterAreaInit = 1;
            int filterAreaMax = 1;
            int minAreaInit = 5;
            int minAreaMax = 200;
            int maxAreaInit = 20;
            int maxAreaMax = 8000;
            int filterCircularityInit = 1;
            int filterCircularityMax = 1;
            int minCircularityInit = 100; //  /1000
            int minCircularityMax = 1000;
            int filterConvexityInit = 1;
            int filterConvexityMax = 1;
            int minConvexityInit = 870;
            int minConvexityMax = 999;
            int filterInertiaInit = 1;
            int filterInertiaMax = 1;
            int minInertiaRatioInit = 1;
            int minInertiaRatioMax = 100;
            int minDistBetweenBlobsInit = 5;
            int minDistBetweenBlobsMax = 100;

            
            createTrackbar (minThresholdNB, VENTANA_CONFIGURACION, &minThresholdInit, minThresholdMax);
            createTrackbar (maxThresholdNB, VENTANA_CONFIGURACION, &maxThresholdInit, maxThresholdMax);
            createTrackbar (minDistBetweenBlobsNB, VENTANA_CONFIGURACION, &minDistBetweenBlobsInit, minDistBetweenBlobsMax);
            createTrackbar (filterColourNB, VENTANA_CONFIGURACION, &filterColorInit, filterColorMax);
            createTrackbar (blobColorNB, VENTANA_CONFIGURACION, &blobColorInit, blobColorMax);
            createTrackbar (filterAreaNB, VENTANA_CONFIGURACION, &filterAreaInit, filterAreaMax);
            createTrackbar (minAreaNB, VENTANA_CONFIGURACION, &minAreaInit, minAreaMax);
            createTrackbar (maxAreaNB, VENTANA_CONFIGURACION, &maxAreaInit, maxAreaMax);
            createTrackbar (filterCircularityNB, VENTANA_CONFIGURACION, &filterCircularityInit, filterCircularityMax);
            createTrackbar (minCircularityNB, VENTANA_CONFIGURACION, &minCircularityInit, minCircularityMax);
            createTrackbar (filterConvexityNB, VENTANA_CONFIGURACION, &filterConvexityInit, filterConvexityMax);
            createTrackbar (minConvexityNB, VENTANA_CONFIGURACION, &minConvexityInit, minConvexityMax);
            createTrackbar (filterInertiaNB, VENTANA_CONFIGURACION, &filterInertiaInit, filterInertiaMax);
            createTrackbar (minInertiaRatioNB, VENTANA_CONFIGURACION, &minInertiaRatioInit, minInertiaRatioMax);
            
            //Se monta y muestra la ventana de los botones
            namedWindow (VENTANA_CONFIGURACION, WINDOW_NORMAL);
            //Añadimos la interacción con el raton.
            // 	Mouse Handler
            setMouseCallback( VENTANA_CONFIGURACION, MouseHandler, NULL );
            //draw_configuracion.create (camSize.height, camSize.width, CV_8UC3);
            //Mostramos las imagenes
            imshow (VENTANA_CONFIGURACION, WINDOW_AUTOSIZE);
            waitKey (1000);
            
            inicio=clock();
            keypoints = DetectorSB (gray_image);
                //descriptors[i] = ExtractorSift (gray_image[i], keypoints[i]);
            fin=clock();
            t = fin - inicio;
        }
        else    botonSimpleBlobOff.copyTo(botonSimpleBlob);
        
        if(botonSiftPulsado){
            botonSiftOn.copyTo(botonSift);
            SIFT sift;
            float inicio, fin, t;
            inicio=clock();
            
            /* get keypoints on the images */
            sift(capture, Mat(), keypoints, descriptors);
            fin=clock();
            t = fin - inicio;
            cout << "Tiempo de ejecucion: " << t << endl;
        }
        else    botonSiftOff.copyTo(botonSift);
        
        if (botonSurfPulsado){
            botonSurfOn.copyTo(botonSurf);
            int minHessian = 1000;
            SurfFeatureDetector detector(minHessian);
            //Calculo descriptores
            SurfDescriptorExtractor extractor;
            float inicio, fin, t;
            inicio=clock();
            //Deteccion de puntos
            detector.detect (capture, keypoints);
            extractor.compute(gray_image, keypoints, descriptors);
            fin=clock();
            t = fin - inicio;
            cout << "Tiempo de ejecucion: " << t << endl;
        }
        else    botonSurfOff.copyTo(botonSurf);
        
        
        //Si no hay ningun boton pulsado leemos la imagen
        if ((!botonHarrisPulsado) && (!botonBriskPulsado) && (!botonORBPulsado) && (!botonFreakPulsado) && (!botonSimpleBlobPulsado) && (!botonStarPulsado) && (!botonDensePulsado) && (!botonMserPulsado) && (!botonSiftPulsado) && (!botonSurfPulsado)
            ) {
            //Cerramos la ventana de configuracion
            ventanaConfiguracionAbierta = CerrarVentanaConfiguracion ();
            
            draw_image = LeerImagenes(imagenI, draw_image, gray_image, HSV_image);
            
        }
        draw_botones = ActualizarBotones (draw_botones);
        //Dibujamos los puntos detectados
        if  (keypoints.data()){
            //Dibujamos los puntos caracteristicos localizados.
            drawKeypoints (capture, keypoints, capture, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
        }

        
        imshow (WINDOW_CAMERAS, draw_image);
        imshow (VENTANA_BOTONES, draw_botones);
        key = waitKey (50);
        
        //Añadimos la opcion de salir del sistema.
        key = waitKey (10);
        if (key == 'q') {
            break;
        }
    }
    return 0;
}

Mat InicializarBotones (Mat draw_botones){
    //******************************
    //Inicializacion de la ventana de los botones.
    //******************************
    //botones de deteccion
    botonHarrisOff.copyTo(botonHarris);
    botonBriskOff.copyTo(botonBrisk);
    botonORBOff.copyTo(botonORB);
    botonFreakOff.copyTo(botonFreak);
    botonStarOff.copyTo(botonStar);
    botonDenseOff.copyTo(botonDense);
    botonMserOff.copyTo(botonMser);
    botonSimpleBlobOff.copyTo(botonSimpleBlob);
    botonSiftOff.copyTo(botonSift);
    botonSurfOff.copyTo(botonSurf);
    //Almacenamiento memoria de la ventana de botones
    draw_botones.create (buttonSize.height, buttonSize.width*10, CV_8UC3);
    return draw_botones;
}
Mat ActualizarBotones(Mat draw_botones){
    //******************************
    //Posicionamiento de los botones
    //******************************
    //Botones de detectores.
    botonHarris.copyTo (draw_botones.rowRange(0, buttonSize.height).colRange(0, buttonSize.width));
    botonBrisk.copyTo (draw_botones.rowRange(0,buttonSize.height).colRange(buttonSize.width,buttonSize.width*2));
    botonORB.copyTo (draw_botones.rowRange(0,buttonSize.height).colRange(buttonSize.width*2, buttonSize.width*3));
    botonFreak.copyTo (draw_botones.rowRange(0,buttonSize.height).colRange(buttonSize.width*3,buttonSize.width*4));
    botonStar.copyTo (draw_botones.rowRange(0,buttonSize.height).colRange(buttonSize.width*4,buttonSize.width*5));
    botonDense.copyTo (draw_botones.rowRange(0,buttonSize.height).colRange(buttonSize.width*5,buttonSize.width*6));
    botonMser.copyTo (draw_botones.rowRange(0,buttonSize.height).colRange(buttonSize.width*6,buttonSize.width*7));
    botonSimpleBlob.copyTo (draw_botones.rowRange(0,buttonSize.height).colRange(buttonSize.width*7,buttonSize.width*8));
    botonSift.copyTo (draw_botones.rowRange(0,buttonSize.height).colRange(buttonSize.width*8,buttonSize.width*9));
    botonSurf.copyTo (draw_botones.rowRange(0,buttonSize.height).colRange(buttonSize.width*9, buttonSize.width*10));
    
    return draw_botones;
}
//********************
//Funcion que lee las imagenes de los botones.
//********************
Mat LeerImagenesBotones (Mat draw_botones){
    //Configuracion inicial de los botones(leyendo la imagen de los botones)
    //Botones de deteccion.
    botonHarrisOn = imread ("botonHarris_pulsado.jpeg", CV_LOAD_IMAGE_COLOR);
    botonHarrisOff = imread ("botonHarris.jpeg", CV_LOAD_IMAGE_COLOR);
    botonBriskOn = imread ("botonBrisk_pulsado.jpeg", CV_LOAD_IMAGE_COLOR);
    botonBriskOff = imread ("botonBrisk.jpeg", CV_LOAD_IMAGE_COLOR);
    botonORBOn = imread ("botonORB_pulsado.jpeg", CV_LOAD_IMAGE_COLOR);
    botonORBOff = imread ("botonORB.jpeg" ,CV_LOAD_IMAGE_COLOR);
    botonFreakOn = imread ("botonFreak_pulsado.jpeg", CV_LOAD_IMAGE_COLOR);
    botonFreakOff = imread ("botonFreak.jpeg", CV_LOAD_IMAGE_COLOR);
    botonStarOn = imread ("botonStar_pulsado.jpeg", CV_LOAD_IMAGE_COLOR);
    botonStarOff = imread ("botonStar.jpeg", CV_LOAD_IMAGE_COLOR);
    botonDenseOn = imread ("botonDense_pulsado.jpeg", CV_LOAD_IMAGE_COLOR);
    botonDenseOff = imread ("botonDense.jpeg", CV_LOAD_IMAGE_COLOR);
    botonMserOn = imread ("botonMser_pulsado.jpeg", CV_LOAD_IMAGE_COLOR);
    botonMserOff = imread ("botonMser.jpeg", CV_LOAD_IMAGE_COLOR);
    botonSimpleBlobOn = imread ("botonSimpleBlob_pulsado.jpeg", CV_LOAD_IMAGE_COLOR);
    botonSimpleBlobOff = imread ("botonSimpleBlob.jpeg", CV_LOAD_IMAGE_COLOR);
    botonSiftOff = imread ("botonSift.jpeg", CV_LOAD_IMAGE_COLOR);
    botonSiftOn = imread ("botonSift_pulsado.jpeg", CV_LOAD_IMAGE_COLOR);
    botonSurfOn = imread ("botonSurf_pulsado.jpeg" , CV_LOAD_IMAGE_COLOR);
    botonSurfOff = imread ("botonSurf.jpeg", CV_LOAD_IMAGE_COLOR);
    //Si no se habre las imagenes se muertra un error.
    if ((!botonHarrisOn.data) || (!botonHarrisOff.data) || (!botonBriskOff.data) || (!botonBriskOn.data) || (!botonORBOff.data) || (!botonORBOn.data) || (!botonFreakOff.data) || (!botonFreakOn.data)||(!botonStarOn.data) || (!botonStarOff.data) || (!botonDenseOn.data) || (!botonDenseOff.data) || (!botonMserOn.data) || (!botonMserOff.data) ||(!botonSimpleBlobOn.data) || (!botonSimpleBlobOff.data)|| (!botonSurfOn.data) || (!botonSurfOff.data) || (!botonSiftOn.data) || (!botonSiftOff.data)){
        cout << "Error al cargar la imagen de los botones de deteccion." << endl;
    }
    
    return draw_botones;
}
//********************
//Funcion que lee las imagenes introducidas como argumento.
//********************
Mat LeerImagenes(Mat imagenI, Mat draw_image, Mat gray_image1, Mat HSV_image1){
    //Asignacion de memoria para la imagen montada
    draw_image.create(camSize.height, camSize.width, CV_8UC3);
    
    
    //Montamos las dos imagenes
    capture=draw_image.colRange(0,camSize.width);
    
    //Copiamos la variable imagen en capture
    imagenI.copyTo(capture);
    
    
    //Pasamos la imagen a escala de grises y separamos en HSV.
    cvtColor (capture, gray_image1, CV_BGR2GRAY);
    cvtColor (capture, HSV_image1, CV_BGR2HSV);
    
    // Create the visualization windows
    namedWindow (WINDOW_CAMERAS, WINDOW_AUTOSIZE);
    
    return draw_image;
}

void MouseHandler(int event, int x, int y, int flags, void* param)
{
    //Controlamos los eventos del raton
    switch (event) {
            //Para eventos del boton derecho del raton
        case CV_EVENT_LBUTTONDOWN:
            //Si hemos pulsado en la zona de botones...
            if ((y > 0) && (y < buttonSize.height)) {
                //Si ademas de estar en la zona de los botones de arriba estamos en la zona del primer boton.
                if (x < buttonSize.width) {
                    //Se cambia el color del boton a color pulsado y se desactiva el boton de otro modo de deteccion
                    if (botonHarrisPulsado == false){
                        botonHarrisPulsado = true;
                        botonBriskPulsado = false;
                        botonORBPulsado = false;
                        botonFreakPulsado = false;
                        botonStarPulsado = false;
                        botonDensePulsado = false;
                        botonMserPulsado = false;
                        botonSimpleBlobPulsado = false;
                        botonSiftPulsado = false;
                        botonSurfPulsado = false;
                        
                    }
                    else{
                        botonHarrisPulsado = false;
                    }
                    
                }
                //Si ademas de estar en la zona de los botones de arriba estamos pulsando en la zona del segundo boton.
                if ((x > buttonSize.width) && (x < buttonSize.width*2)) {
                    if (botonBriskPulsado == false){
                        botonBriskPulsado = true;
                        botonHarrisPulsado = false;
                        botonORBPulsado = false;
                        botonFreakPulsado = false;
                        botonStarPulsado = false;
                        botonDensePulsado = false;
                        botonMserPulsado = false;
                        botonSiftPulsado = false;
                        botonSurfPulsado = false;
                    }
                    else{
                        botonBriskPulsado = false;
                    }
                    
                }
                
                if ((x > buttonSize.width*2) && (x < buttonSize.width*3)){
                    if (botonORBPulsado == false) {
                        botonORBPulsado = true;
                        botonHarrisPulsado = false;
                        botonFreakPulsado = false;
                        botonStarPulsado = false;
                        botonDensePulsado = false;
                        botonMserPulsado = false;
                        botonSimpleBlobPulsado = false;
                        botonSiftPulsado = false;
                        botonBriskPulsado = false;
                        botonSurfPulsado = false;
                    }
                    else{ botonORBPulsado = false;
                    }
                }
                
                if ((x > buttonSize.width*3) && (x < buttonSize.width*4)) {
                    if (botonFreakPulsado == false) {
                        botonFreakPulsado = true;
                        botonHarrisPulsado = false;
                        botonORBPulsado = false;
                        botonStarPulsado = false;
                        botonDensePulsado = false;
                        botonMserPulsado = false;
                        botonSimpleBlobPulsado = false;
                        botonSiftPulsado = false;
                        botonBriskPulsado = false;
                        botonSurfPulsado = false;
                        
                    }
                    else {   botonFreakPulsado = false;
                    }
                }
                
                if ((x > buttonSize.width*4) && (x < buttonSize.width*5)) {
                    if (botonStarPulsado == false) {
                        botonStarPulsado = true;
                        botonHarrisPulsado = false;
                        botonBriskPulsado = false;
                        botonORBPulsado = false;
                        botonFreakPulsado = false;
                        botonDensePulsado = false;
                        botonMserPulsado = false;
                        botonSimpleBlobPulsado = false;
                        botonSiftPulsado = false;
                        botonSurfPulsado = false;
                    }
                    else    botonStarPulsado = false;
                }
                if ((x > buttonSize.width*5) && (x < buttonSize.width*6)) {
                    if (botonDensePulsado == false) {
                        botonDensePulsado = true;
                        botonHarrisPulsado = false;
                        botonBriskPulsado = false;
                        botonORBPulsado = false;
                        botonFreakPulsado = false;
                        botonStarPulsado = false;
                        botonMserPulsado = false;
                        botonSimpleBlobPulsado = false;
                        botonSiftPulsado = false;
                        botonSurfPulsado = false;
                    }
                    else    botonDensePulsado = false;
                }
                
                if ((x > buttonSize.width*6) && (x < buttonSize.width*7)) {
                    if (botonMserPulsado == false) {
                        botonMserPulsado = true;
                        botonHarrisPulsado = false;
                        botonBriskPulsado = false;
                        botonORBPulsado = false;
                        botonFreakPulsado = false;
                        botonStarPulsado = false;
                        botonDensePulsado = false;
                        botonSimpleBlobPulsado = false;
                        botonSiftPulsado = false;
                        botonSurfPulsado = false;
                    }
                    else    botonMserPulsado = false;
                }
                
                if ((x > buttonSize.width*7) && (x < buttonSize.width*8)) {
                    if (botonSimpleBlobPulsado == false) {
                        botonSimpleBlobPulsado = true;
                        botonHarrisPulsado = false;
                        botonBriskPulsado = false;
                        botonORBPulsado = false;
                        botonFreakPulsado = false;
                        botonStarPulsado = false;
                        botonDensePulsado = false;
                        botonMserPulsado = false;
                        botonSiftPulsado = false;
                        botonSurfPulsado = false;
                        
                    }
                    else    botonSimpleBlobPulsado = false;
                }
                
                if ((x > buttonSize.width*8) && (x < buttonSize.width*9)) {
                    if (botonSiftPulsado == false) {
                        botonSiftPulsado = true;
                        botonHarrisPulsado = false;
                        botonORBPulsado = false;
                        botonFreakPulsado = false;
                        botonBriskPulsado = false;
                        botonStarPulsado = false;
                        botonDensePulsado = false;
                        botonMserPulsado = false;
                        botonSimpleBlobPulsado = false;
                        botonSurfPulsado = false;
                        
                    }
                    else {botonSiftPulsado = false;
                    }
                }
                
                if ((x > buttonSize.width*9) && (x < buttonSize.width*10)){
                    if (botonSurfPulsado == false) {
                        botonSurfPulsado = true;
                        botonHarrisPulsado = false;
                        botonORBPulsado = false;
                        botonFreakPulsado = false;
                        botonBriskPulsado = false;
                        botonStarPulsado = false;
                        botonDensePulsado = false;
                        botonMserPulsado = false;
                        botonSimpleBlobPulsado = false;
                        botonSiftPulsado = false;
                        
                    }
                    else{
                        botonSurfPulsado = false;
                    }
                }
                //...
            }
            
            
        default:
            break;
    }
}
//********************
//Funcion que realiza la deteccion de puntos y extraccion de caracteristica
//********************
vector <KeyPoint> DetectorHarris (Mat imagen){
    //Deteccion de puntos con el metodo Harris
    GoodFeaturesToTrackDetector detector;
    vector <KeyPoint> keypoints;
    keypoints.clear();
    detector.detect(imagen, keypoints);
    return keypoints;
}

vector <KeyPoint> DetectorBrisk (Mat imagen){
    vector<KeyPoint> keypoints;
    keypoints.clear();
    //Declaracion variables
    int Threshl= getTrackbarPos(ThreshlnombreTrackbar, VENTANA_CONFIGURACION);
    int Octaves= getTrackbarPos(OctavesnombreTrackbar, VENTANA_CONFIGURACION); //(pyramid layer) from which the keypoint has been extracted
    float PatternScales = (getTrackbarPos(PatternScalesnombreTrackbar, VENTANA_CONFIGURACION))/100;
    cout << "Threshl value: " << Threshl << endl;
    cout << "octaves value: " << Octaves << endl;
    cout << "PatternScales value: " << PatternScales << endl;
    if (Threshl == -1 && Octaves == -1 && PatternScales == 0) {
        Threshl = 30;//Se pone a 30 porque luego se multiplica por 2 (60).
        Octaves = 4;
        PatternScales = 1.0f;
    }
    Threshl = Threshl * 2;
    
    //Utilizamos el detector y extractor de BRISK
    //cout << "Llego" << endl;
    BRISK  BRISKD(Threshl,Octaves,PatternScales);//initialize algoritm
    //cout << "Llego1" << endl;
    BRISKD.create("Feature2D.BRISK");
    //cout << "Llego2" << endl;
    BRISKD.detect(imagen, keypoints);
    //cout << "Llego3" << endl;
    return keypoints;
}

vector <KeyPoint> DetectorORB (Mat imagen){
    vector <KeyPoint> keypoints;
    OrbFeatureDetector detector;
    keypoints.clear();
    detector.detect(imagen, keypoints);
    return keypoints;
}



vector <KeyPoint> DetectorStart (Mat imagen){
    //int maxSize=16, int responseThreshold=30, int lineThresholdProjected = 10, int lineThresholdBinarized=8, int suppressNonmaxSize=5 ); 20 o 40
    // a 60 cm -> maxSize = 40 treshold = 20
    // a 80 cm -> maxSize = 80 tresdhold = 30.
    // a 120 cm -> maxSize = 40
    // a 140 cm -> maxSize = 20 treshhold = 40
    int maxSize = getTrackbarPos (maxSizeNombreBarra, VENTANA_CONFIGURACION);
    int responseThreshold = getTrackbarPos (responseThresholdNombreBarra, VENTANA_CONFIGURACION);
    int lineThresholdProjected = getTrackbarPos (lineThresholdProjectedNombreBarra, VENTANA_CONFIGURACION);
    int lineThresholdBinarized = getTrackbarPos (lineThresholdBinarizedNombreBarra, VENTANA_CONFIGURACION);
    int suppressNonmaxSize = getTrackbarPos (suppressNonmaxSizeNombreBarra, VENTANA_CONFIGURACION);
    cout << "maxSize:" << maxSize << endl;
    cout << "responseThreshold: " << responseThreshold << endl;
    cout << "lineThresholdProjected:" << lineThresholdProjected << endl;
    cout << "lineThresholdBinarized:" << lineThresholdBinarized << endl;
    cout << "SuppressNonMaxSize: " << suppressNonmaxSize << endl;
    if (maxSize == -1 && responseThreshold == -1 && lineThresholdProjected == -1 && lineThresholdBinarized == -1 && suppressNonmaxSize == -1) {
        maxSize = 40;
        responseThreshold = 20;
        lineThresholdProjected = 10;
        lineThresholdBinarized = 8;
        suppressNonmaxSize = 5;
    }
    StarFeatureDetector detector( maxSize, responseThreshold, lineThresholdProjected, lineThresholdBinarized, suppressNonmaxSize );
    vector <KeyPoint> keypoints;
    keypoints.clear();
    detector.detect(imagen, keypoints);
    return keypoints;
}

vector <KeyPoint> DetectorDense (Mat imagen){
    //float initFeatureScale=1.f, int featureScaleLevels=1, float featureScaleMul=0.1f, int initXyStep=6, int initImgBound=0, bool varyXyStepWithScale=true, bool varyImgBoundWithScale=false );
    int initFeatureScale = getTrackbarPos (initFeatureScaleNombreBarra, VENTANA_CONFIGURACION);
    int featureScaleLevels = getTrackbarPos (featureScaleLevelsNombreBarra, VENTANA_CONFIGURACION);
    int featureScaleMul = getTrackbarPos (featureScaleMulNombreBarra, VENTANA_CONFIGURACION);
    int initXyStep = getTrackbarPos (initXyStepNombreBarra, VENTANA_CONFIGURACION);
    int initImgBound = getTrackbarPos (initImgBoundNombreBarra, VENTANA_CONFIGURACION);
    int varyXyStepWithScale = getTrackbarPos (varyXyStepWithScaleNombreBarra, VENTANA_CONFIGURACION);
    int varyImgBoundWithScale = getTrackbarPos (varyImgBoundWithScaleNombreBarra, VENTANA_CONFIGURACION);
    //Normalizacion de valores.
    float initFeatureScaleG = initFeatureScale/10;
    float featureScaleMulG = featureScaleMul/100;
    bool varyXyStepWithScaleG;
    bool varyImgBoundWithScaleG;
    if (varyXyStepWithScale == 0) {
        varyXyStepWithScaleG = false;
    }
    else{
        varyXyStepWithScaleG = true;
    }
    if (varyImgBoundWithScale == 0) {
        varyImgBoundWithScaleG = false;
    }
    else{
        varyImgBoundWithScaleG = true;
    }
    cout << "init feature scale:" << initFeatureScaleG << endl;
    cout << "featureScaleLevels:" << featureScaleLevels << endl;
    cout << "featureScaleMul:" << featureScaleMulG << endl;
    cout << "initXyStep:" << initXyStep << endl;
    cout << "initImgBound:" << initImgBound << endl;
    cout << "varyXyStepWithScale:" << varyXyStepWithScale << endl;
    cout << "varyImgBoundWithScale:" << varyImgBoundWithScale << endl;
    if (initFeatureScaleG == 0 && featureScaleLevels == -1 && featureScaleMulG == 0 && initXyStep == -1 && initImgBound == -1 && varyXyStepWithScale == -1 && varyImgBoundWithScale == -1) {
        initFeatureScaleG = 1.f;
        featureScaleLevels = 1;
        featureScaleMulG = 0.1f;
        initXyStep = 6;
        initImgBound = 10;
        varyXyStepWithScaleG = false;
        varyImgBoundWithScaleG = true;
    }
    DenseFeatureDetector detector (initFeatureScaleG, featureScaleLevels, featureScaleMulG, initXyStep, initImgBound, varyXyStepWithScaleG, varyImgBoundWithScaleG );
    
    vector <KeyPoint> keypoints;
    keypoints.clear();
    detector.detect(imagen, keypoints);
    return keypoints;
}

vector <KeyPoint> DetectorMser (Mat imagen){
    //int _delta, int _min_area, int _max_area, float _max_variation, float _min_diversity, int _max_evolution, double _area_threshold, double _min_margin, int _edge_blur_size );
    //1,            20,             60,             0.25,                   0.2,                200,                1.01,                   0.003,              5
    // delta : Valor mas pequeño detecta mas puntos, nada que ver con la zona de los puntos detectados.
    //min_area y max_area : la idea es que cubran el área que puede tener un grano de uva.
    //max_variation :
    //min_diversity :
    
    /*
     imagen de 60 a 80 cm: (1, 30, 100, 0.25, 0.5, 50, 1.01, 0.003, 5)
     imagen de 80 a 100 cm: (1, 15, 60, 0.5, 0.5, 50, 1.01, 0.003, 5)
     imagen de 100 a 120 cm: (2, 5, 15, 0.5, 0.2, 50, 1.01, 0.3, 5)
     */
    int delta = getTrackbarPos (deltaNombreBarra, VENTANA_CONFIGURACION);
    int minArea = getTrackbarPos (minAreaNombreBarra, VENTANA_CONFIGURACION);
    int maxArea = getTrackbarPos (maxAreaNombreBarra, VENTANA_CONFIGURACION);
    int maxVariation = getTrackbarPos (maxVariationNombreBarra, VENTANA_CONFIGURACION);
    int minDiversity = getTrackbarPos (minDiversityNombreBarra, VENTANA_CONFIGURACION);
    int maxEvolution = getTrackbarPos (maxEvolutionNombreBarra, VENTANA_CONFIGURACION);
    int areaThreshold = getTrackbarPos (areaThresholdNombreBarra, VENTANA_CONFIGURACION);
    int minMargin = getTrackbarPos (minMarginNombreBarra, VENTANA_CONFIGURACION);
    int edgeBlurSize = getTrackbarPos (edgeBlurSizeNombreBarra, VENTANA_CONFIGURACION);
    
    //Normalizacion de valores.
    double maxVariationG = ((double) maxVariation) / 100;
    double minDiversityG = ((double) minDiversity) / 100;
    double areaThresholdG = ((double) areaThreshold) / 100;
    double minMarginG = ((double)minMargin) / 10;
    
    //Restricciones para el funcionamiento.
    if (delta == -1 && minArea == -1 && maxArea == -1 && maxVariation == -1 && minDiversity == -1 && maxEvolution == -1 && areaThreshold == -1 && minMargin == -1 && edgeBlurSize == -1) {
        delta =2;
        minArea = 5;
        maxArea = 15;
        maxVariationG = 0.5;
        minDiversityG = 0.2;
        maxEvolution = 50;
        areaThresholdG = 1.01;
        minMarginG = 0.3;
        edgeBlurSize = 5;
    }
    if (maxVariationG == 0 && minDiversityG == 0 && minMarginG == 0) {
        maxVariationG = 0.5;
        minDiversityG = 0.2;
        minMarginG = 0.3;
    }
    cout << "Delta:" << delta << endl;
    cout << "minArea:" << minArea << endl;
    cout << "maxArea:" << maxArea << endl;
    cout << "maxVariation:" << double(maxVariationG) << endl;
    cout << "minDiversity:" << minDiversityG << endl;
    cout << "maxEvolution:" << maxEvolution << endl;
    cout << "areaThreshold:" << areaThresholdG << endl;
    cout << "minMargin:" << minMarginG << endl;
    cout << "edgeBlurSize:" << edgeBlurSize << endl;
    
    vector <KeyPoint> keypoints;
    keypoints.clear();
    MserFeatureDetector detector(delta, minArea, maxArea, maxVariationG, minDiversityG, maxEvolution, areaThresholdG, minMarginG, edgeBlurSize);
    
    detector.detect(imagen, keypoints);
    return keypoints;
}

vector <KeyPoint> DetectorSB (Mat imagen){
    //Falta arreglarlo para que encuentre mas racimos.. Animo
    vector <KeyPoint> keypoints;
    // Setup SimpleBlobDetector parameters.
    SimpleBlobDetector::Params params;
    
    params.minThreshold = getTrackbarPos(minThresholdNB, VENTANA_CONFIGURACION);
    params.maxThreshold = getTrackbarPos (maxThresholdNB, VENTANA_CONFIGURACION);
    params.minDistBetweenBlobs = getTrackbarPos (minDistBetweenBlobsNB, VENTANA_CONFIGURACION);
    int filterColour = getTrackbarPos(filterColourNB, VENTANA_CONFIGURACION);//bool
    params.blobColor = getTrackbarPos (blobColorNB, VENTANA_CONFIGURACION);
    int filterByArea = getTrackbarPos (filterAreaNB, VENTANA_CONFIGURACION);//bool
    params.minArea = getTrackbarPos (minAreaNB, VENTANA_CONFIGURACION);
    params.maxArea = getTrackbarPos (maxAreaNB, VENTANA_CONFIGURACION);
    int filterByCircularity = getTrackbarPos (filterCircularityNB, VENTANA_CONFIGURACION);//bool
    int minCircularity = getTrackbarPos (minCircularityNB, VENTANA_CONFIGURACION);
    int filterByConvexity = getTrackbarPos(filterConvexityNB, VENTANA_CONFIGURACION);//Bool
    int minConvexity = getTrackbarPos (minConvexityNB, VENTANA_CONFIGURACION);
    int filterByInertia = getTrackbarPos (filterInertiaNB, VENTANA_CONFIGURACION);//bool
    int minInertiaRatio = getTrackbarPos (minInertiaRatioNB, VENTANA_CONFIGURACION);
    
    //Adaptamos las variables para introducirlas en el detector.
    if (filterColour == 1) {
        params.filterByColor = true;
    }
    else    params.filterByColor = false;
    if (filterByArea == 1){
        params.filterByArea = true;
    }
    else    params.filterByArea = false;
    if (filterByCircularity == 1) {
        params.filterByCircularity = true;
    }
    else    params.filterByCircularity = false;
    if (filterByConvexity == 1) {
        params.filterByConvexity = true;
    }
    else    params.filterByConvexity = false;
    if (filterByInertia ==1) {
        params.filterByInertia = true;
    }
    else    params.filterByInertia = false;
    params.minCircularity = ((float) minCircularity) / 1000;
    params.minConvexity = ((float)minConvexity) / 1000;
    params.minInertiaRatio = ((float) minInertiaRatio) / 1000;
    
    //Configuracion inicial.
    if (params.minThreshold == -1) { //Habrá que poner mas restricciones.
        // Change thresholds
        params.minThreshold = 10;
        params.maxThreshold = 200;
        
        params.minDistBetweenBlobs = 5;
        
        //  Change by Color
        params.filterByColor = 1;
        params.blobColor = 160;
        
        // Filter by Area.
        params.filterByArea = true;
        params.minArea = 5;
        params.maxArea = 20;
        
        // Filter by Circularity
        params.filterByCircularity = true;
        params.minCircularity = 0.9; //0.1
        
        // Filter by Convexity
        params.filterByConvexity = true;
        params.minConvexity = 0.87; //0.87
        
        // Filter by Inertia
        params.filterByInertia = true;
        params.minInertiaRatio = 0.01;
    }
    
    cout << "minThreshold:" << params.minThreshold << endl;
    cout << "maxThreshold:" << params.maxThreshold << endl;
    cout << "min. dist. between blobs:" << params.minDistBetweenBlobs << endl;
    cout << "filterColor:" << filterColour << endl;
    cout << "Color value:" << params.blobColor << endl;
    cout << "filter by area:" << filterByArea << endl;
    cout << "Min area:" << params.minArea << endl;
    cout <<"Max area:" << params.maxArea << endl;
    cout << "filter by circularity:" << filterByCircularity << endl;
    cout << "Min. circularity:" << minCircularity << endl;
    cout << "Filter by Convexity:" << filterByConvexity << endl;
    cout << "Min. convexity:" << params.minConvexity << endl;
    cout << "Filter by inertia:" << filterByInertia << endl;
    cout << "min. Inertia ratio:" << params.minInertiaRatio << endl;

    keypoints.clear();
    // Set up detector with params
    SimpleBlobDetector detector(params);
    detector.detect(imagen, keypoints);
    
    return keypoints;
}

vector<KeyPoint> DetectorSift (Mat imagen){
    SiftFeatureDetector sift(200);
    vector <KeyPoint> keypoints;
    keypoints.clear();
    Mat descriptors;
    sift(imagen, Mat(), keypoints, descriptors);
    return keypoints;
}

vector <KeyPoint> DetectorSurf (Mat imagen){
    //Le damos valor al coeficiente, en este caso valdra:
    vector <KeyPoint> keypoints;
    keypoints.clear();
    int minHessian = 1000;
    SurfFeatureDetector detector(minHessian);
    //Deteccion de puntos
    detector.detect (imagen, keypoints);
    return keypoints;
}

vector <KeyPoint> DetectorGeneral (Mat imagen){
    Ptr<FeatureDetector> detector;
    vector <KeyPoint> keypoints;
    keypoints.clear();
    detector = FeatureDetector::create("ORB");
    
    if(!detector)
    {
        cout << "Error creating feature detector" << endl;
        getchar();	// wait for a keystroke and exits
    }
    (*detector).detect(imagen, keypoints);
    return keypoints;
}

bool CerrarVentanaConfiguracion (){
    destroyWindow(VENTANA_CONFIGURACION);
    return false;
}



