#ifndef MANDELBROTIMAGE_H
#define MANDELBROTIMAGE_H

#include <QImage>
#include <QPainter>
#include <QtWidgets>
#include <vector>

class MandelbrotImage : public QImage
{  
public:
  MandelbrotImage(const int width, const int height);


private:
  //image parameters
  double cx = -0.5;
  double cy = 0;
  double d = 1.0;

  double px_min = 0.0;
  double px_max = 599.0;
  double py_min = 0.0;
  double py_max = 399.0;

  //methods
  QRgb calc_in_out(double rx, double ry);
  double h_pixel2rect(double px, double cx, double d, double px_min, double px_max);
  double v_pixel2rect(double py, double cy, double d, double py_min, double py_max);
};

#endif // MANDELBROTIMAGE_H

