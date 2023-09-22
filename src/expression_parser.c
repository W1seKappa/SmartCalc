#include "expression_parser.h"

#include <stdio.h>
#include <stdlib.h>

#include "stack_string.h"

int get_token(const char expression[EXPRESSION_MAX_LEN], int n, int i, char str[STACK_STR_MAX_LEN]) {
    /*
    получает токен, состоящий более чем из 1 символа
    (число (9302) или функция (sin))
    возвращает длину токена, а сам токен копируется в str
    */
    int n1 = 0;                                         /* длина токена */
    if (expression[i] >= 'a' && expression[i] <= 'z') { /* если токен - функция или х */
        while (expression[n1 + i] >= 'a' && expression[n1 + i] <= 'z' && n1 + i < n) { /* пока это токен */
            str[n1] = expression[n1 + i]; /* копируем токен в str */
            n1++;                         /* увеличиваем счетчик длины */
        }
        str[n1] = '\0'; /* конец строки */
    } else {            /* если токен - число */
        while (expression[n1 + i] >= '0' && expression[n1 + i] <= '9' && n1 + i < n) { /* пока это токен */
            str[n1] = expression[n1 + i]; /* копируем токен в str */
            n1++;                         /* увеличиваем счетчик длины */
        }
        str[n1] = '\0'; /* конец строки */
    }
    return n1; /* возвращаем длину токена */
}

int compare_operators(char c1, char c2) {
    /* сравнивает приоритеты операторов:
        1  - у с1 выше приоритет
        -1 - у с2 выше приоритет
        0  - одинаковый
    */
    int res = 0;
    char table[5][2] = {{'+', '1'},
                        {'-', '1'},
                        {'*', '2'},
                        {'/', '2'},
                        {'~', '3'}}; /* операторы и их приоритет (чем больше тем выше) */
    int c1_pr = 0;
    int c2_pr = 0;
    for (int i = 0; i < 5; i++) { /* ищем приоритет с1 */
        if (c1 == table[i][0]) {
            c1_pr = table[i][1];
        }
        if (c2 == table[i][0]) { /* ищем приоритет с2 */
            c2_pr = table[i][1];
        }
    }
    if (c1_pr > c2_pr) { /* сравниваем приоритеты */
        res = 1;
    } else if (c1_pr < c2_pr) {
        res = -1;
    }
    return res;
}

int is_operator(char c) {
    /* проверяем является ли оператором:
    1 - является
    0 - нет
     */
    int res = 0;
    const char arr[6] = {'+', '-', '*', '/', '^', '~'}; /* массив операторов */
    for (int i = 0; i < 6; i++) {
        if (c == arr[i]) { /* если равен какому-то элементу массива, то является оператором */
            res = 1;
        }
    }
    return res;
}

void process_closing_bracket(struct stack_string *my_stack, char array[STACK_MAX_LEN][STACK_STR_MAX_LEN],
                             int *i_array, char cur_str[STACK_STR_MAX_LEN]) {
    /* обрабатываем закрывающуюся скобочку
     */
    while (1) { /* берем из стека строки и помещаем в array пока не встретим '(' */
        pop_stack_string(my_stack, cur_str);
        if (cur_str[0] == '(') {
            break;
        } else {
            my_strcpy(array[*i_array], cur_str); /* помещаем  cur_str в конец array*/
            (*i_array)++;
        }
    }
}

void process_operator(char c, char expression[EXPRESSION_MAX_LEN], int i, struct stack_string *my_stack,
                      char array[STACK_MAX_LEN][STACK_STR_MAX_LEN], int *i_array,
                      char cur_str[STACK_STR_MAX_LEN]) {
    /* обрабатываем оператор
     */
    if (c == '-' && (i == 0 || (i > 1 && (is_operator(expression[i - 1]) ||
                                          expression[i - 1] == '(')))) { /* если это унарный минус*/
        c = '~';
    }
    while (1) { /* пока в стеке операторы и их приоритет больше приоритеты текущего оператора, выталкиваем их
                   из стека и записываем в конец array*/
        cur_str[0] = '\0';
        if (my_stack->top != NULL && pop_stack_string(my_stack, cur_str) && is_operator(cur_str[0]) &&
            compare_operators(cur_str[0], c) >= 0) {
            my_strcpy(array[*i_array], cur_str);
            (*i_array)++;
        } else {
            if (cur_str[0] != '\0') {
                push_stack_string(my_stack, cur_str);
            }
            break;
        }
    }
    cur_str[0] = c;
    cur_str[1] = '\0';
    push_stack_string(my_stack, cur_str); /* кладем в стек текущий оператор*/
}

int fill_array(char expression[EXPRESSION_MAX_LEN], int n, struct stack_string *my_stack,
               char array[STACK_MAX_LEN][STACK_STR_MAX_LEN]) {
    /* основная функция, которая переводит выражение в польскую нотацию */
    int i = 0;                       /* индекс в стороке expression*/
    int i_array = 0;                 /* индекс array*/
    int n1 = 0;                      /* количество токенов(не используется)*/
    char cur_str[STACK_STR_MAX_LEN]; /* массив для строки */
    while (i < n) {                  /* идем по символам строки expression */
        char c = expression[i];      /* берем текущий символ */
        if ((c >= '0' && c <= '9') || c == 'x') { /* если это число или х */
            i += get_token(expression, n, i,
                           array[i_array]); /* получаем целый токен и записываем его в array */
            i_array++;                      /* увеличиваем счетчик */
        } else if (c >= 'a' && c <= 'z') { /* если это функция */
            i += get_token(expression, n, i, cur_str); /* получаем целый токен и записываем его в array */
            push_stack_string(my_stack, cur_str); /* увеличиваем счетчик */
        } else if (c == '(') {                    /* если это скобка ( */
            cur_str[0] = c;
            cur_str[1] = '\0';
            push_stack_string(my_stack, cur_str); /* кидаем в стек */
            i++;                                  /* увеличиваем счетчик */
        } else if (c == ')') {
            process_closing_bracket(my_stack, array, &i_array, cur_str); /* обрабатываем ) */
            i++; /* увеличиваем счетчик */
        } else {
            process_operator(c, expression, i, my_stack, array, &i_array,
                             cur_str); /* обрабатываем оператор */
            i++;                       /* увеличиваем счетчик */
        }
        n1++; /* увеличиваем счетчик */
    }
    while (my_stack->top != NULL &&
           pop_stack_string(my_stack, cur_str)) { /* если что-то есть в стеке, выталкиваем это в array */
        my_strcpy(array[i_array], cur_str); /* копируем cur_str в array[i_array] */
        i_array++;                          /* увеличиваем счетчик */
    }
    return n1; /* возвращаем кол-во токенов */
}
