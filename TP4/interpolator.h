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
    * contructeur crée affecte les coef de pente du ys passé en paramètre dans ai
    */
    Interpolator(std::vector<double> xs, std::vector<double> y) : xs_(xs) {
        bi_ = y;
        bi_.push_back(y.back());
        xs_.push_back(1.0);
        for (unsigned long long i = 0; i < xs_.size() - 1; i++) {
            ai_.push_back((y[i + 1] - y[i]) / (xs_[i + 1] - xs_[i]));
         }
    }

    /*
     * get value prend l'objet courant (un interpolator) et va return la valeur y=f(x)
     */
    double get_value(const double x) const {
        for (unsigned int i = 0; i < xs_.size(); i++) {
          if (xs_[i] <= x and x <= xs_[i+1]) {
              return std::clamp(ai_[i] * (x - xs_[i]) + bi_[i], 0., 255.);
          }
        }
        return 1.0;
    }
};

#endif // INTERPOLATOR_H
