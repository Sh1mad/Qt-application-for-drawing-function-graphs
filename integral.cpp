#include "integral.h"

double integral(tokens tok, double a, double b){
    double h = 0.1;
    double n;
    double integ = 0.0;
    double step = 0;
    n = (b-a) / h;
    integ = h * (ResultExpr(tok, a) + ResultExpr(tok, b)) / 2.0;
    for (int i = 1; i <= n-1; i++){
        step = a + h * i;
        integ += h * ResultExpr(tok, step);
    }
    return integ;
}

void find_roots(tokens tok, double a, double b, QVector<double> &x_mas, QVector<double> &y_mas)
{
    x_mas.clear();
    y_mas.clear();
    double section = b-a;
    double func, cord;
    for (int i = 0; i < section * 10000 + 1; i++){
        cord = i/10000.0 + a;
        func = ResultExpr(tok, cord);
        if (abs(func) <= 0.0001){
            x_mas << cord;
            y_mas << 0;
        }
    }
}
