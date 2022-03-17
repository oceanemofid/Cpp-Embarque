#include "mandelbrotimage.h"
#include "Commify.h"
#include <iostream>
#include <complex>
#include <cmath>
#include <chrono>


MandelbrotImage::MandelbrotImage(const int width, const int height): QImage (width, height, QImage::Format_RGB32){
    auto start = std::chrono::high_resolution_clock::now();

    create_gradient_colors();

    std::vector<std::thread> threads;

    const int max_threads = 4;

    for(int i = 0; i < max_threads; i++) {
        threads.emplace_back([=]() {
            process_sub_image(i, max_threads);
        });
     }

    for(auto &thread_elem :threads){
        thread_elem.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto interval = end-start;
    int64_t t = std::chrono::duration_cast<std::chrono::microseconds>(interval).count();
    Commify exe_time(t);
    std::cout << "INFO: image calculated in  " << exe_time << " us\n";
}


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
    std::complex c0(rx, ry);
    std::complex z(0.0, 0.0);
    QRgb color= qRgb(0, 0, 0); //black

    bool is_inside = true;
    int i = 0;
    int cpt = 0;
    double mod = 0.0;

    for(int n = 0; n < 512; n++){
        z = z * z + c0;
        auto real = z.real();
        auto imag = z.imag();
        double module = std::sqrt(real * real + imag * imag);
        if (module > 2) {
            is_inside = false;
            mod = module;
         }
         if(!is_inside and module >= 256){
             cpt = n;
             double v = std::log2(std::log2(mod * mod));
             i = static_cast<int>(1024*sqrt(cpt + 5 -v)) % 2048;
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
    const double max_pixel = 2048;

    //we iterate to calculate the 2048 RGB colors
    for(int i = 0; i < max_pixel; i++) {
        //we add to the vector the new color
        double color = static_cast<double>(i) / static_cast<double>(max_pixel);
        tab_colors.push_back(interpolColors(color));
    }
}


/*
 * Role: create an QRgb object with the R G B values after interpolation
 */
QRgb MandelbrotImage::interpolColors(double x) {
    //compute our R,G,B components
    int R = interpolation_R.get_value(x);
    int G = interpolation_G.get_value(x);
    int B = interpolation_B.get_value(x);
    return qRgb(R,G,B);
}

/*
 * Role: Draw a section of the image
 *
 *  @current_thread: index of subsection to process
 *  @max_threads: number of threads available on machine
 */
void MandelbrotImage::process_sub_image(int current_thread, int max_threads)
{
    double cx = -0.5;
    double cy = 0;
    double d = 1.0;

    double px_min = 0.0;
    double px_max = 599.0;
    double py_min = 0.0;
    double py_max = 399.0;

    int sub_image_height = height() / max_threads;
    int yi = current_thread * sub_image_height;

    for (int py = yi; py < sub_image_height + yi; py++) {
        double ry = v_pixel2rect(py, cy, d, py_min, py_max);
        for (int px = 0; px < width(); px++) {
            double rx = h_pixel2rect(px, cx, d, px_min, px_max);
            QRgb rgb_color = calc_in_out(rx, ry);
            setPixel(px, py, rgb_color);
        }
    }
}
