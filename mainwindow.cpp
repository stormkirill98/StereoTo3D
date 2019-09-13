#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include<QDebug>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    openCam(700);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openCam(int id) {
    VideoCapture cap; // open the default camera

    if (!cap.open(id))
        return;

    while(1) {
        Mat frame;
        cap >> frame; // get a new frame from camera
        if( frame.empty())
            break; // end of video stream

        imshow("Cam", frame);
        if (waitKey(10) == 27)
            break;
    }
}
