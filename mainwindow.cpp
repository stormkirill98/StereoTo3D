#include "camera.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QDebug>
#include <QThread>

using namespace std;

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::openCam(int id, QLabel* output) {
  Camera* cam = new Camera(id, output);

  QThread* thread = new QThread;
  cam->moveToThread(thread);

  connect(thread, SIGNAL(started()), cam, SLOT(start()));
  connect(cam, SIGNAL(finished()), thread, SLOT(quit()));
  //connect(this, SIGNAL(stopAll()), cam, SLOT(stop()));
  connect(cam, SIGNAL(finished()), cam, SLOT(deleteLater()));
  connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

  thread->start();
}

QList<int> MainWindow::getCameraIds() {
  QList<int> ids;

  VideoCapture cap;
  int i = 0;

  while(i < 1024) {
    if (cap.open(++i)) {
      qDebug() << "Camera id = " << i;
      ids << i;
    }
  }

  return ids;
}

void MainWindow::on_pushButton_clicked() {
  QList<int> cameraIds = getCameraIds();
  if (cameraIds.isEmpty())
    return;

  openCam(cameraIds[0], ui->image1);
}
