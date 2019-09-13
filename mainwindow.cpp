#include "camera.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include<QDebug>
#include <QThread>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //2 or 700
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openCam(int id) {
    Camera* cam = new Camera(id);
    QThread* thread = new QThread;
    cam->moveToThread(thread);

    connect(thread, SIGNAL(started()), cam, SLOT(start()));
    connect(cam, SIGNAL(finished()), thread, SLOT(quit()));
    //connect(this, SIGNAL(stopAll()), cam, SLOT(stop()));
    connect(cam, SIGNAL(finished()), cam, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
}

void MainWindow::on_pushButton_clicked()
{
    openCam(2);
}
