#include "mandelbrotimage.h"
#include <iostream>
#include <complex>
#include <cmath>


MandelbrotImage::MandelbrotImage(const int width, const int height, const double xc, const double yc, const double d): QImage (width, height, QImage::Format_RGB32){
    create_gradient_colors();
    std::vector<std::thread> threads;
    const int max_threads = 4;

    for(int i = 0; i < max_threads; i++) {
        threads.emplace_back([=]() {
            process_sub_image(i, max_threads, xc, yc, d);
        });
     }
    for(auto &thread_elem :threads){
        thread_elem.join();
    }
}
/*
 * Role : returns the corresponding real world x coordinate
 */

double MandelbrotImage::h_pixel2rect(double px, double cx, double d, double px_min, double px_max){
    //linea interpolation with x
    //px: 0        ---           599
    //rx: xc-1.5d      ---       xc+1.5d
    //a , b
    double ax = (3.0 * d / (px_max - px_min));
    double bx = cx -1.5 * d;
    double rx = ax * px + bx;
    return rx;
}

double MandelbrotImage::v_pixel2rect(double py, double cy, double d, double py_min, double py_max){
    //linea interpolation with y
    //py: 0        ---           399
    //ry: yc+d      ---          yc-d
    //a , b
    double ay = (2.0 * d / (py_max - py_min));
    double by = cy + d;
    double ry = -ay * py + by;
    return ry;
}

QRgb MandelbrotImage::calc_in_out(double rx, double ry)
{
    //c0= x0 +iy0
    //z0 = 0
    std::complex<double> c0(rx, ry);
    std::complex z(0.0, 0.0);
    QRgb color= qRgb(0, 0, 0); //black

    bool is_inside = true;
    int i = 0;
    double mod = 0.0;

    for(int n = 0; n < 512; n++){
        z = z * z + c0;
        //auto real = z.real();
        //auto imag = z.imag();
        //double module = std::sqrt(real * real + imag * imag);
        double module = abs(z);
        if (module > 2) {
            is_inside = false;
            mod = module;
         }
         if(!is_inside and module >= 256){
             double v = std::log2(std::log2(mod * mod));
             i = static_cast<int>(1024*sqrt(n + 5 -v)) % 2048;
             color = tab_colors[i];
             return color;
         }
        }
       return color;
    }


/*
 * Role: create a gradient of colors
 */
void MandelbrotImage::create_gradient_colors(){
    const double max_color = 2048;
    tab_colors.reserve(max_color);
    //we iterate to calculate the 2048 RGB colors
    for(int i = 0; i < max_color; i++) {
        //we add to the vector the new color
        double color = static_cast<double>(i) /max_color;
        tab_colors.emplace_back(interpolColors(color));
    }
}


/*
 * Role: create an QRgb object with the R G B values after interpolation
 */
QRgb MandelbrotImage::interpolColors(double x) {
    //compute our R,G,B components
    int R = static_cast<int>(interpolation_R.get_value(x));
    int G = static_cast<int>(interpolation_G.get_value(x));
    int B = static_cast<int>(interpolation_B.get_value(x));
    return qRgb(R,G,B);
}

/*
 * Role: Draw a section of the image
 *
 *  @current_thread: index of subsection to process
 *  @max_threads: number of threads available on machine
 */
void MandelbrotImage::process_sub_image(int current_thread, int max_threads, double xc, double yc, double d){

    int sub_image_height = height() / max_threads;
    int yi = current_thread * sub_image_height;

    for (int py = yi; py < sub_image_height + yi; py++) {
        double ry = v_pixel2rect(py, yc, d, py_min, py_max);
        for (int px = 0; px < width(); px++) {
            double rx = h_pixel2rect(px, xc, d, px_min, px_max);
            QRgb rgb_color = calc_Julia(rx, ry);
            setPixel(px, py, rgb_color);
        }
    }
}

QRgb MandelbrotImage::calc_Julia(double rx, double ry)
{
    //c0= -0.4 + 0.6i
    //z0 = rx + iry
    std::complex<double> c0(-0.4, 0.6);
    std::complex z(rx, ry);
    QRgb color= qRgb(0, 0, 0); //black

    bool is_inside = true;
    int i = 0;

    for(int n = 0; n < 512; n++){
        z = z * z + c0;
        //auto real = z.real();
        //auto imag = z.imag();
        //double module = std::sqrt(real * real + imag * imag);
        double module = abs(z);
        if (module > 2) {
            is_inside = false;
         }
         if(!is_inside and module >= 256){
             double v = std::log2(std::log2(norm(z)));
             i = static_cast<int>(1024*sqrt(n + 5 -v)) % 2048;
             color = tab_colors[i];
             return color;
         }
        }
       return color;
    }

