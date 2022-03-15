#ifndef MANDELBROTIMAGE_H
#define MANDELBROTIMAGE_H

#include <QImage>
#include <QPainter>
#include <QtWidgets>

class MandelbrotImage : public QImage
{  
public:
  MandelbrotImage(const int width, const int height);


private:
    std::pair<double,double> convert(double px, double py);
    std::pair<bool, QRgb> calc_in_out(double rx, double ry);
    double v_pixel2rect(double px, double cx, double d, double px_min, double px_max);
    double h_pixel2rect(double py, double cy, double d, double py_min, double py_max);

};

#endif // MANDELBROTIMAGE_H
