
#include "calculating.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "stack_double.h"
/*Функция для прочтения чаров(чисел)*/
double str_to_int(char array[STACK_MAX_LEN][STACK_STR_MAX_LEN], int i) {
    int n = 0;
    double result = 0;
    double counter1 = 1;
    while (array[i][n] != '\0') {
        result = (result * counter1) + ((double)(array[i][n] - '0'));
        n++;
        counter1 = 10;
    }
    return result;
}
/*Функция считывающая обнаруживающая в поступающей массиве тригонометрические функции*/
void trigonometry(char array[STACK_MAX_LEN][STACK_STR_MAX_LEN], int i, HEAD *head) {
    double num1;
    if (array[i][0] == 's' && array[i][1] == 'i') { /*Встретился синус*/
        num1 = pop_stack_double(head); /*Достаем из стека последнее значение*/
        push_stack_double(sin(num1), head); /*Возвращаем посчитанное значение в стек*/
    } else if (array[i][0] == 'c' && array[i][1] == 'o') { /*Встертился косинус*/
        num1 = pop_stack_double(head); /*Достаем из стека последнее значение*/
        push_stack_double(cos(num1), head); /*Возвращаем посчитанное значение*/
    } else if (array[i][0] == 't' && array[i][1] == 'a') { /*Встретился тангенс*/
        num1 = pop_stack_double(head);      /*Достаем последнее значение*/
        push_stack_double(tan(num1), head); /*Возвращаем посчитанное значение*/
    } else if (array[i][0] == 'c' && array[i][1] == 't') { /*Встретился катангенс*/
        num1 = pop_stack_double(head); /*Достаем последнее значениие из стека*/
        push_stack_double(1 / tan(num1), head); /*Возращаем посчитанный катангенс*/
    } else if (array[i][0] == 's' && array[i][1] == 'q') { /*Встертился квадратный корень*/
        num1 = pop_stack_double(head); /*Достаем последний элемент(верхний) из стека*/
        push_stack_double(sqrt(num1), head); /*Возращаем посчитанное значение*/
    } else if (array[i][0] == 'l') {         /*Встретился натуральный логарифм*/
        num1 = pop_stack_double(head);
        push_stack_double(log(num1), head);
    } else if (array[i][0] == '~') { /*Унарный минус*/
        num1 = pop_stack_double(head);
        push_stack_double(-num1, head);
    }
}
/*Функуия для обнаружения и операций при обнаружении операнда*/
void operands(char array[STACK_MAX_LEN][STACK_STR_MAX_LEN], int i, HEAD *head) {
    double num1;
    double num2;
    if (array[i][0] == '+') {
        num2 = pop_stack_double(head);
        num1 = pop_stack_double(head);
        push_stack_double(num1 + num2, head);
    } else if (array[i][0] == '-') {
        num2 = pop_stack_double(head);
        num1 = pop_stack_double(head);
        push_stack_double(num1 - num2, head);
    } else if (array[i][0] == '*') {
        num2 = pop_stack_double(head);
        num1 = pop_stack_double(head);
        push_stack_double(num1 * num2, head);
    } else if (array[i][0] == '/') {
        num2 = pop_stack_double(head);
        num1 = pop_stack_double(head);
        if (num2 != 0) {
            push_stack_double(num1 / num2, head);
        } else {
            push_stack_double(num1 / 0.0001, head);
        }
    }
}
/*Основная функция подсчета значения, возвращающая посчитанный y*/
double counter(char array[STACK_MAX_LEN][STACK_STR_MAX_LEN], int n, HEAD *head, double x) {
    for (int i = 0; i < n; i++) {
        if (array[i][0] == 'x') {
            push_stack_double(x, head);
        } else if (array[i][0] >= '0' && array[i][0] <= '9') {
            double a = str_to_int(array, i);
            push_stack_double(a, head);
        } else if (array[i][0] == '+' || array[i][0] == '-' || array[i][0] == '*' || array[i][0] == '/') {
            operands(array, i, head);
        } else if (array[i][0] == 's' || array[i][0] == 'c' || array[i][0] == 't' || array[i][0] == 'l' ||
                   array[i][0] == '~') {
            trigonometry(array, i, head);
        }
    }
    double res = pop_stack_double(head);
    return res;
}