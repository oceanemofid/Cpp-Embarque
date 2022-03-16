
#include "mainwindow.h"
#include <iostream>
#include <string>
#include <QtWidgets>
#include "mandelbrotimage.h"


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


//Mandelbrot
const int mandelbrot_width = 600;
const int mandelbrot_height = 400;

void MainWindow::slot_load_Mandelbrot_image() {

  // The ~10 lines of code below must be changed with your code
  // Create a QImage of required size
  // Draw a simple black/white checker board

    MandelbrotImage mandelbrot_image(mandelbrot_width,mandelbrot_height);
    image_widget_->setPixmap(QPixmap::fromImage(mandelbrot_image));
    image_widget_->setFixedSize(mandelbrot_width,mandelbrot_height);
    adjustSize();
 }



  //
  // You probably don't want to change these lines 
  //
