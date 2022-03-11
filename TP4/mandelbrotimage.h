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
    std::pair<bool, QColor> calc_in_out(double rx, double ry);

};

#endif // MANDELBROTIMAGE_H
