#include "func_realisations.h"
using namespace std;

double op_plus(stack <double> &s) {
    double a,b;
    a = s.top();
    s.pop();
    b = s.top();
    s.pop();
    return a+b;
}
double op_minus(stack <double> &s) {
    double a,b;
    a = s.top();
    s.pop();
    b = s.top();
    s.pop();
    return b-a;
}
double op_mul(stack <double> &s) {
    double a,b;
    a = s.top();
    s.pop();
    b = s.top();
    s.pop();
    return a*b;
}
double op_div(stack <double> &s) {
    double a,b;
    a = s.top();
    s.pop();
    b = s.top();
    s.pop();
    return b/a;
}
double op_deg(stack <double> &s) {
    double a,b;
    a = s.top();
    s.pop();
    b = s.top();
    s.pop();
    //b^a!!
    return pow(b,a);
}
double op_sqrt(stack <double> &s) {
    double a;
    a = s.top();
    s.pop();
    return sqrt(a);
}
double op_opposite(stack <double> &s) {
    double a;
    a = s.top();
    s.pop();
    return -a;
}

double op_not(stack <double> &s) {
    double a;
    a = s.top();
    s.pop();
    return !a;
}
double op_sin(stack <double> &s) {
    double a;
    a = s.top();
    s.pop();
    return sin(a);
}
double op_cos(stack <double> &s) {
    double a;
    a = s.top();
    s.pop();
    return cos(a);
}
double op_tan(stack <double> &s) {
    double a;
    a = s.top();
    s.pop();
    return tan(a);
}
double op_asin(stack <double> &s) {
    double a;
    a = s.top();
    s.pop();
    return asin(a);
}
double op_acos(stack <double> &s) {
    double a;
    a = s.top();
    s.pop();
    return acos(a);
}
double op_atan(stack <double> &s) {
    double a;
    a = s.top();
    s.pop();
    return atan(a);
}
double op_abs(std::stack <double> &s){
    double a;
    a = s.top();
    s.pop();
    return abs(a);
}
double op_exp(std::stack <double> &s){
    double a;
    a = s.top();
    s.pop();
    return exp(a);
}
double op_log(std::stack <double> &s){
    double a;
    a = s.top();
    s.pop();
    return log(a);
}
double op_log10(std::stack <double> &s){
    double a;
    a = s.top();
    s.pop();
    return log10(a);
}
double op_log2(std::stack <double> &s){
    double a;
    a = s.top();
    s.pop();
    return log2(a);
}
