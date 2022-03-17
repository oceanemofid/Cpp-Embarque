#include "mainwindow.h"
#include <iostream>
#include <string>
#include <QtWidgets>
#include "mandelbrotimage.h"
#include "Commify.h"
#include <chrono>

double cx = -0.5;
double cy = 0;
double d = 1;

const int mandelbrot_width = 600;
const int mandelbrot_height = 400;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  //
  // construct image_widget

  image_widget_ = new QLabel;
  image_widget_->setBackgroundRole(QPalette::Base);
  image_widget_->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  image_widget_->setScaledContents(true);
  image_widget_->setMinimumSize(300, 300);

  create_actions();
  create_menus();

  setCentralWidget(image_widget_);
  resize(QGuiApplication::primaryScreen()->availableSize() * 2 / 5);

}


void MainWindow::create_actions() {
  //
  action_Mandelbrot_image_ = new QAction(tr("Mandelbrot Image"), this);
  connect(action_Mandelbrot_image_, SIGNAL(triggered()), this, SLOT(slot_load_Mandelbrot_image()));

  action_exit_ = new QAction(tr("E&xit"), this);
  action_exit_->setShortcut(tr("Ctrl+Q"));
  connect(action_exit_, SIGNAL(triggered()), this, SLOT(slot_exit()));

  action_about_ = new QAction(tr("&About"), this);
  connect(action_about_, SIGNAL(triggered()), this, SLOT(slot_about()));
}

void MainWindow::slot_exit() {
  close();
}

void MainWindow::slot_about() {
    QMessageBox::about(this, tr("About Image Viewer"),
            tr("<p>The user can select several images to be displayed on the screen</p>"));
}


void MainWindow::create_menus() {
  menu_open_ = new QMenu(tr("&Open"), this);

  menu_open_->addAction(action_Mandelbrot_image_);
  menu_open_->addAction(action_exit_);


  menu_help_ = new QMenu(tr("&Help"), this);
  menu_help_->addAction(action_about_);

  menuBar()->addMenu(menu_open_);
  menuBar()->addMenu(menu_help_);
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
        case Qt::Key_Left:
            MandelbrotImage mandelbrot_image(mandelbrot_width, mandelbrot_height, cx-0.1, cy, d);
        break;
        case Qt::Key_Right:
            MandelbrotImage mandelbrot_image(mandelbrot_width, mandelbrot_height, cx+0.1, cy, d);
            break;
        case Qt::Key_Down:
            MandelbrotImage mandelbrot_image(mandelbrot_width, mandelbrot_height, cx+0.1, cy, d);
            break;
        case Qt::Key_Up:
            //
            break;
        case Qt::Key_Plus:
            //
            break;
        case Qt::Key_Minus:
            //
            break;
        default:
            MainWindow::keyPressEvent(event);
        }
}


//Mandelbrot


void MainWindow::slot_load_Mandelbrot_image() {

  // The ~10 lines of code below must be changed with your code
  // Create a QImage of required size
  // Draw a simple black/white checker board

    //image parameters

    auto start = std::chrono::high_resolution_clock::now();

    MandelbrotImage mandelbrot_image(mandelbrot_width, mandelbrot_height, cx, cy, d);

    auto end = std::chrono::high_resolution_clock::now();
    //compite exec time
    auto interval = end-start;
    int64_t t = std::chrono::duration_cast<std::chrono::microseconds>(interval).count();
    Commify exe_time(t);
    std::cout << "INFO: image calculated in  " << exe_time << " us\n";

    image_widget_->setPixmap(QPixmap::fromImage(mandelbrot_image));
    image_widget_->setFixedSize(mandelbrot_width, mandelbrot_height);
    adjustSize();
 }



  //
  // You probably don't want to change these lines 
  //
