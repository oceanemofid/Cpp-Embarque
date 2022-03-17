#include "mandelbrotimage.h"
#include <complex>
#include <cmath>

/*
 * Role : Constructs a MandelbrotImage of size width x height
 */
MandelbrotImage::MandelbrotImage(const int width, const int height): QImage (width, height, QImage::Format_RGB32){
    for(int py=0; py<height;py++){
        double ry = v_pixel2rect(py, cy, d, py_min, py_max);
        for(int px=0; px<width;px++){
            double rx = h_pixel2rect(px, cx, d, px_min, px_max);
            QRgb rgb_color =calc_in_out(rx,ry);
            setPixel(px, py, rgb_color);
        }
    }
}

/*
 * Role : returns the corresponding real world x coordinate of the @px pixel's row
 */
double MandelbrotImage::h_pixel2rect(double px, double cx, double d, double px_min, double px_max){
    //linea interpolation with x
    //px: 0        ---           599
    //rx: xc-1.5d      ---       xc+1.5d
    //a , b
    double ax = (3.0*d/(px_max - px_min));
    double bx = cx -1.5*d;
    double rx = ax*px+bx;
    return rx;
}

/*
 * Role : returns the corresponding real world y coordinate of the @py pixel's column
 */
double MandelbrotImage::v_pixel2rect(double py, double cy, double d, double py_min, double py_max){
    //linea interpolation with y
    //py: 0        ---           399
    //ry: yc+d      ---          yc-d
    //a , b
    double ay = (2.0*d/(py_max - py_min));
    double by = cy + d;
    double ry = -ay*py+by;
    return ry;
}

/*
 * Role : returns the QRgb color of the pixel of coordinates(rx,ry)
 *        depending on if it's inside the MandelbortImage.
 */
QRgb MandelbrotImage::calc_in_out(double rx, double ry)
{
    //c0= x0 +iy0
    //z0 = 0
    std::complex c0(rx,ry);
    std::complex z(0.0,0.0);
    QRgb color= qRgb(0, 0, 0);//black


    for(int n=0; n<512; n++){
        z = z*z+c0;
        double module= abs(z);
        if(module>2){
            color=qRgb(255,218,103);
        }
    }
    return color;
}

