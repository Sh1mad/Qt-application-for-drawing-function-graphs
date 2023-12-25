#ifndef INTEGRAL_H
#define INTEGRAL_H

#include <QVector>
#include <parser.h>


double integral(tokens tok, double a, double b);

void find_roots(tokens tok, double a, double b, QVector<double> &x_mas, QVector<double> &y_mas);

#endif // INTEGRAL_H
