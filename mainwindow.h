#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButton_clicked();

 private:
  Ui::MainWindow* ui;
  int cameraId1 = -1, cameraId2 = -1;

 private:
  void openCam(int id, QLabel* output);
  QList<int> getCameraIds();
  void takePhoto();
  void defineCameraIds();
};

#endif // MAINWINDOW_H
