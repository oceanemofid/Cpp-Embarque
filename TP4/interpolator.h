#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include <QImage>
#include <iostream>
#include <vector>
#include <algorithm>

class Interpolator : public QImage
{
private:
    std::vector<double> ai_;
    std::vector<double> bi_;
    std::vector<double> xs_;

public:
   /*
    * Role: Constructs an Interpolator object which sets up the ai and bi coefficients
    */
    Interpolator(std::vector<double> xs, std::vector<double> &y) : xs_(xs) {
       y.push_back(y.front());
       bi_ = y;
       xs_.push_back(1.0);
        for (unsigned int i = 0; i < xs_.size() - 1; i++) {
            ai_.push_back((y[i + 1] - y[i]) / (xs_[i + 1] - xs_[i]));
         }
    }

    /*
     * Role : Returns the @x interpolation with the current interpolator object
     */
    double get_value(const double x) const {
        unsigned long i = 0;
        while (i< xs_.size()-1 && x > xs_[i+1]) i++;
        return std::clamp(ai_[i] * (x - xs_[i]) + bi_[i], 0., 255.);
    }

    int operator()(const double x) {
        return static_cast<int>(get_value(x));
    }
};

#endif // INTERPOLATOR_H
