#include "mandelbrotimage.h"
#include <complex>
#include <cmath>

MandelbrotImage::MandelbrotImage(const int width, const int height): QImage (width, height, QImage::Format_RGB32){
    for(int py=0; py<height;py++){
        for(int px=0; px<width;px++){
            double rx= convert(px,py).first;
            double ry= convert(px,py).second;

            //auto[rx,ry] = convert(px,py);
            bool is_outside=calc_in_out(rx,ry).first;
            QRgb rgb_color =calc_in_out(rx,ry).second;
            //auto[is_outside, rgb_color] = calc_in_out(rx,ry);
            //setPixel(px, py, qRgb(255,218,103));
            //if(is_outside){
              //rgb_color=(255,218,103);
            //}
            setPixel(px, py, rgb_color);

        }
    }
}

double MandelbrotImage::v_pixel2rect(double px, double cx, double d, double px_min, double px_max){
    //linea interpolation with x
    //px: 0        ---           599
    //rx: xc-1.5d      ---       xc+1.5d
    //a , b
    double ax = (3.0*d/(px_max - px_min));
    double bx = cx -1.5*d;
    double rx = ax*px+bx;
    return rx;
}

double MandelbrotImage::h_pixel2rect(double py, double cy, double d, double py_min, double py_max){
    //linea interpolation with y
    //py: 0        ---           399
    //ry: yc+d      ---          yc-d
    //a , b
    double ay = (2.0*d/(py_max - py_min));
    double by = cy -d;
    double ry = -ay*py+by;
    return ry;
}

std::pair<double,double> MandelbrotImage::convert(double px, double py){
    double cx = -0.5;
    double cy = 0.0;
    double d = 1.0;

    double px_min=0.0;
    double px_max=599.0;
    double py_min=0.0;
    double py_max=399.0;

    //linear interpolation with x
    double rx = v_pixel2rect(px,cx,d,px_min,px_max);
    //linear interpolation with y
    double ry = h_pixel2rect(py,cy,d,py_min,py_max);
    return std::make_pair(rx,ry);

}       


std::pair<bool, QRgb> MandelbrotImage::calc_in_out(double rx, double ry)
{
    //c0= x0 +iy0
    //z0 = 0
    std::complex c0(rx,ry);
    std::complex z(0.0,0.0);
    for(int n=0; n<512; n++){
        z = z*z+c0;
    }
    double module= abs(z);
    bool is_outside;
    QRgb color;
    if(module <2){
        is_outside=false;
        color=qRgb(255, 255, 255);
    }
    else{
        color=qRgb(0,0,0);
    }
    return std::make_pair(is_outside, color);
}


