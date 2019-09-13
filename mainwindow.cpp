#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    VideoCapture cap; // open the default camera

//    int i = 2;
//    while(!cap.open(i)) {
//        i++;
//    }

    if(!cap.open(700))
            return;

    namedWindow("edges");
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        if( frame.empty()) break; // end of video stream

        imshow("edges", frame);
        if (waitKey(10) == 27) break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
