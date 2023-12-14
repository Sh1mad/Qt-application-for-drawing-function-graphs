#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <cmath>
#include "func_realisations.h"

// Типы токенов
enum tokentype {
    //Переменная, константа, (, ), функция, операция, массив, {, }
    var, num, op_br, cl_br, func, op
};
// Структура токена
struct token {
    std::string name;
    tokentype type;

    //Конструкторы
    token(std::string str, tokentype typ) {
        name = str;
        type = typ;
    }
    token() {}
};
//Массив токенов
typedef std::vector<token> tokens;

//Разделители
const std::string delimiters = " ()+/*-^";


//Функция выставляет приоритеты операций
void CreatePrior();

//Указатель на функцию(для операций)
typedef double(*func_type)(std::stack<double> &);

//Массив операций
typedef std::map<std::string, func_type> Ooops;


//Инициализация массива операций
void CreateOps();

void CreateSetOfDelimiters();

bool IsDelimiter(char sym);

void CreateTokensFromExpression(std::string &expr, tokens &texpr);

void CreatePostfixFromTokens(tokens &texpr, tokens &pexpr);

double ResultExpr(tokens &pexpr, double &param);

void ConvertToPostfix(std::string &func, tokens &tok);


#endif // PARSER_H
