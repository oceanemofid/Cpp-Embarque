#include "mandelbrotimage.h"
#include <complex>
#include <cmath>
#include <thread>

const int mandelbrot_width = 600;
const int mandelbrot_height = 400;
/*
MandelbrotImage::MandelbrotImage(const int width, const int height): QImage (width, height, QImage::Format_RGB32){
    // variable dasn le .h dans private avec const
    double cx = -0.5;
    double cy = 0.0;
    double d = 1.0;

    double px_min=0.0;
    double px_max=599.0;
    double py_min=0.0;
    double py_max=399.0;

    for(int py=0; py<height;py++){
        double ry= v_pixel2rect(py,cy,d,py_min,py_max);

        for(int px=0; px<width;px++){
            double rx = h_pixel2rect(px,cx,d,px_min,px_max);

            //auto[rx,ry] = convert(px,py);
            bool is_outside=calc_in_out(rx,ry).first;
            QRgb rgb_color =calc_in_out(rx,ry).second;
            setPixel(px, py, rgb_color);
            //auto[is_outside, rgb_color] = calc_in_out(rx,ry);
            //setPixel(px, py, qRgb(255,218,103));

        }
    }
}
*/

/*
MandelbrotImage::MandelbrotImage(const int width, const int height): QImage (width, height, QImage::Format_RGB32){

    int max_threads = 16;

    for(int i= 0; i < max_threads; i++) {
        process_sub_image(i, max_threads); }
}

*/
MandelbrotImage::MandelbrotImage(const int width, const int height): QImage (width, height, QImage::Format_RGB32){

    std::vector<std::thread> threads;
    int max_threads = 4;
    for(int i = 0; i < max_threads; i++) {
        threads.emplace_back([=]() {
            process_sub_image(i, max_threads);
        });
    }

    for(auto &thread_elem :threads){
        thread_elem.join();
    }
}

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


std::pair<bool, QRgb> MandelbrotImage::calc_in_out(double rx, double ry)
{
    //c0= x0 +iy0
    //z0 = 0
    std::complex c0(rx,ry);
    std::complex z(0.0,0.0);
    QRgb color= qRgb(0, 0, 0);
    bool is_inside =true;
    //tab of 2048 colors
    std::vector<std::tuple<int,int,int>> tab_color;
    for(int n=0; n<512; n++){
        z = z*z+c0;
        double module= sqrt(z.real()*z.real()+z.imag()*z.imag());
        if(module>2){
            color=qRgb(255,218,103);
            is_inside=false;
            break;
        }
    }
    return std::make_pair(is_inside, color);
}

void MandelbrotImage::process_sub_image(int current_thread, int max_threads)
{
    double cx = -0.5;
    double cy = 0.0;
    double d = 1.0;

    double px_min=0.0;
    double px_max=599.0;
    double py_min=0.0;
    double py_max=399.0;

    int yj = mandelbrot_height/max_threads;
    int yi = current_thread*yj;

    for(int py=yi; py<yj+yi; py++){
        double ry= v_pixel2rect(py,cy,d,py_min,py_max);

        for(int px=0; px<mandelbrot_width;px++){
            double rx = h_pixel2rect(px,cx,d,px_min,px_max);

            //auto[rx,ry] = convert(px,py);
            bool is_outside=calc_in_out(rx,ry).first;
            QRgb rgb_color =calc_in_out(rx,ry).second;
            setPixel(px, py, rgb_color);
        }
    }
}
