#include "s21_smart_calc.h"

void skip_spaces(char* expression) {
    setlocale(LC_ALL, "C");
    char* skip_values = " \n\t";
    char clean_expression[255];
    size_t j = 0;
    for (size_t i = 0; i < strlen(expression); i++) {
        if (!strchr(skip_values, expression[i]))
            clean_expression[j++] = expression[i];
    }
    clean_expression[j] = '\0';
    for (size_t i = 0; i < strlen(clean_expression); i++)
        expression[i] = clean_expression[i];
    expression[strlen(clean_expression)] = '\0';
}


int validation(char* expression) {
    int error = 0;
    int i = 0;
    int count_open = 0;
    int count_close = 0;
    while (expression[i] != '\n') {
        if (is_digt(expression[i]) == 0) { // если цифра
            if(is_digt(expression[i + 1]) != 0 && expression[i + 1] != '.' && expression[i + 1] != ',' && expression[i + 1] != ')' &&  is_operand(expression[i + 1]) == 1) {
                error = 1;
            }
        } else if (is_operand(expression[i]) == 0) { // если операнд
            if (is_digit(expression[i + 1]) == 1 && expression[i + 1] != 'x' && is_func(expression, i + 1) == 1 && expression[i + 1] != '(') {
                error = 1;
            }
        } else if (expression[i] == 'x') { // если икс
            if (is_digit(expression[i + 1] == 1 && is_operand(expression[i + 1]) == 1 && is_func(expression, i + 1) == 1 && expression[i + 1] != ')') {
                error = 1;
            }
        } else if (expression[i] == '(') { // открывающаяся скобка
            count_open += 1;
            if (expression[i + 1] != '(' && is_digit(expression[i + 1]) == 1 && is_func(expression, i + 1) == 1 && expression[i + 1] != '-' && expression[i + 1] != '+'){
                error = 1;
            }
        } else if (expression[i] == ')') { // закрывающаяся скобка
            count_close += 1;

        } else {
            error = 0;
        }
        i++;
    }
    if (count_open != count_close) {
        error = 1;
    } else {
        error = 0;
    }
    return error;
}




int is_digit(char expression_i) {
    int res = 0;
    if (0 <= (int)expression_i && (int)expression_i <= 9) {
        res = 0;
    } else {
        res = 1;
    }
    return res;
}

int is_operand(char expression_i) {
    int res = 0;
    if ((int)expression_i == 42 || (int)expression_i == 43 || (int)expression_i == 45 || (int)expression_i == 47 || (int)expression_i == 61) {
        res = 0;
    } else {
        res = 1;
    }
    return res;
}


int is_func(char* expression, int i) {
    int res = 0;
    if (expression[i] == 's' && expression [i + 1] == 'i' && expression[i + 2] == 'n') {
        res = 0;
    } else if (expression[i] == 'c' && expression[i + 1] == 'o' && expression[i + 2] == 'n') {
        res = 0;
    } else if (expression[i] == 't' && expression[i + 1] == 'a' && expression[i + 2] == 'n') {
        res = 0;
    } else if (expression[i] == 'a' && expression[i + 1] == 'c' && expression[i + 2] == 'o' && expression[i + 3] == 's') {
        res = 0;
    } else if (expression[i] == 'a' && expression[i + 1] == 's' && expression[i + 2] == 'i' && expression[i + 3] == 'n') {
        res = 0;
    } else if (expression[i] == 'a' && expression[i + 1] == 't' && expression[i + 2] == 'a' && expression[i + 3] == 'n') {
        res = 0;
    } else if (expression[i] == 's' && expression[i + 1] == 'q' && expression[i + 2] == 'r' && expression[i + 3] == 't') {
        res = 0;
    } else if (expression[i] == 'l' && expression[i + 1] == 'n') {
        res = 0;
    } else if (expression[i] == 'l' && expression[i + 1] == 'o' && expression[i + 2] == 'g') {
        res = 0;
    } else {
        res = 1;
    }
    return res;
}
