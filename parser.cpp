#include "parser.h"
using namespace std;

//Приоритеты операций
map <std::string, int> prior;

Ooops ops;

//Множество разделителей
set<char> DelimSet;

//Инициализирует множество разделителей
void CreateSetOfDelimiters() {
    for (size_t i = 0; i < delimiters.size(); i++)
        DelimSet.insert(delimiters[i]);
    return;
}

void CreatePrior() {
    prior.insert({"+", 10});
    prior.insert({"-", 10});
    prior.insert({"*", 20});
    prior.insert({"/", 20});
    prior.insert({"^", 30});
    prior.insert({"opposite", 10});
}

void CreateOps() {
    ops.insert({"+", op_plus});
    ops.insert({"-", op_minus});
    ops.insert({"*", op_mul});
    ops.insert({"/", op_div});
    ops.insert({"^", op_deg});
    ops.insert({"sqrt", op_sqrt});
    ops.insert({"opposite", op_opposite});
    ops.insert({"!", op_not});
    ops.insert({"sin", op_sin});
    ops.insert({"cos", op_cos});
    ops.insert({"tan", op_tan});
    ops.insert({"acos", op_acos});
    ops.insert({"asin", op_asin});
    ops.insert({"atan", op_atan});
    ops.insert({"abs", op_abs});
    ops.insert({"exp", op_exp});
    ops.insert({"log", op_log});
    ops.insert({"log2", op_log2});
    ops.insert({"log10", op_log10});

    return;
}

//Проверка, является ли символ разделителем
bool IsDelimiter(char sym) {
    return DelimSet.count(sym) > 0;
}

//Разбиваем выражение на токены
void CreateTokensFromExpression(string &expr, tokens &texpr) {
    CreateSetOfDelimiters();
    string ex = expr + " ";
    string name;

    //Получаем имя токена
    size_t i = 0;
    while (i < ex.size() - 1) {
        name = "";
        //Если текущий символ разделитель
        if (IsDelimiter(ex[i])) {
            if (ex[i] == ' ') { //Пробел просто перепрыгиваем
                i++;
                continue;
            }
            name = ex[i]; //Любой другой добавляем в имя токена
            i++;
        }

        else {
            while (!IsDelimiter(ex[i])) {
                /*Если не разделитель непример, переменная или имя массива,
            Считываем его польностью */
                name += ex[i];
                i++;
            }
        }
        //Заносим получившийся токен в список токенов
        texpr.push_back(token(name, var));
    }

    //Раздаем получившимся токенам типы
    for (size_t j = 0; j < texpr.size(); j++) {
                if (texpr[j].name[0] == '(') {
            texpr[j].type = op_br;
            continue;
        }
        if (texpr[j].name[0] == ')') {
            texpr[j].type = cl_br;
            continue;
        }
        if (isdigit(texpr[j].name[0])) {
            texpr[j].type = num;
            continue;
        }
        if (texpr[j].name[0] == 'x') {
            texpr[j].type = var;
            continue;
        }
        if (isalpha(texpr[j].name[0])) {
            if (j < texpr.size() - 1 && texpr[j+1].name[0] == '(')
                texpr[j].type = func;
            continue;
        }

        texpr[j].type = op;
    }

    //Проверяем минус и !, что это префиксные операции
    for (size_t j = 0; j < texpr.size(); j++) {
        if (texpr[j].name == "-" && (j == 0 || texpr[j - 1].type == op_br))
            texpr[j].name = "opposite";
    }

    return;
}


//Переводим выражение в постфиксную запись
void CreatePostfixFromTokens(tokens &texpr, tokens &pexpr) {
    //Задаем приоритеты операций
    CreatePrior();
    stack <token> TStack;

    //Ловим токены и работаем по алгоритму
    for (size_t i = 0; i < texpr.size(); i++) {
        switch (texpr[i].type) {
        case var:
        case num:
            pexpr.push_back(texpr[i]);
            break;

        case op_br:
            TStack.push(texpr[i]);
            break;

        case cl_br:
            while (TStack.top().type != op_br) {
                pexpr.push_back(TStack.top());
                TStack.pop();
            }
            TStack.pop();
            break;

        case op:
            if (TStack.size()) {
                while (TStack.size() && ((TStack.top().type == op && prior[texpr[i].name] <= prior[TStack.top().name]) || TStack.top().type == func)) {
                    pexpr.push_back(TStack.top());
                    TStack.pop();
                }
            }
            TStack.push(texpr[i]);
            break;

        case func:
            while (TStack.size() && TStack.top().type == func) {
                pexpr.push_back(TStack.top());
                TStack.pop();
            }
            TStack.push(texpr[i]);
            break;
        }
    }

    while (TStack.size()) {
        pexpr.push_back(TStack.top());
        TStack.pop();
    }

    return;
}

//Считаем результат выражения
double ResultExpr(tokens &pexpr, double &param) {
    CreateOps();
    stack <double> s;

    for (size_t i=0; i<pexpr.size(); i++) {
        switch(pexpr[i].type) {
        case num: {
            s.push(atoi(pexpr[i].name.c_str()));
        }
        break;

        case var: {
            if(pexpr[i].name == "x" || pexpr[i].name == "X") {
                s.push(param);
                break;
            }
        }
        break;

        case func:
        case op: {
            Ooops::iterator Oit;
            for(Oit=ops.begin(); Oit!=ops.end(); Oit++) {
                if(Oit->first == pexpr[i].name) {
                    s.push(Oit->second(s));
                    break;
                }
            }
        }
        break;
        }
    }

    return s.top();
}

void ConvertToPostfix(string &func, tokens &tok){
    tokens f_tok;
    CreateTokensFromExpression(func, f_tok);
    CreatePostfixFromTokens(f_tok, tok);
}
