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
