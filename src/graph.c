#include <stdio.h>
#include <stdlib.h>

#include "calculating.h"
#include "expression_parser.h"
#define STACK_STR_MAX_LEN 15
#define EXPRESSION_MAX_LEN 200
#define STACK_MAX_LEN 100

void read_expression(char expression[EXPRESSION_MAX_LEN], int *n) {
    /* читаем expression до энтера*/
    char c;
    *n = 0;
    while (scanf("%c", &c) == 1 && c != '\n') {
        *expression = c;
        expression++;
        (*n)++;
    }
    *expression = '\0';
}

double my_abs(double x) {
    /* возвращаем модуль х*/
    if (x < 0.0) x = -x;
    return x;
}

void init_grid(double x[80], double y[25]) {
    double start_x = 0.0; /*инициализируем начальную точку оси Х*/
    double step_x = (4.0 * M_PI) / 79; /*определеяем шаг по оси Х*/
    for (int i = 0; i < 80; i++) {     /*цикл шагов по оси Х*/
        x[i] = start_x + i * step_x; /*определение положение точки на оси Х, запись в массив*/
    }

    double start_y = -1.0;    /*инициализируем начальную точку на оси У*/
    double step_y = 2.0 / 24; /*определяем шаг по оси У*/
    for (int i = 0; i < 25; i++) { /*цикл шагов по оси У*/
        y[i] = start_y + i * step_y; /*определяем положение точки точки на оси У, запись в массив*/
    }
}

void fill_indexes(const double f_x[80], const double y[25], int ind_points[80]) {
    for (int i = 0; i < 80; i++) { /*цикл*/
        double closest = y[0];     /*инициализируем ближайшую точку*/
        int ind_closest = 0;       /*инициализируем индекс ближайшей точки*/
        for (int j = 1; j < 25; j++) {                              /*цикл перебора строк*/
            if (my_abs(f_x[i] - y[j]) < my_abs(f_x[i] - closest)) { /*если y[j] ближе, чем closest к f_x[i]*/
                closest = y[j];  /*присвоение ближайшей точки У*/
                ind_closest = j; /*присвоение ближайшей точки переменной J*/
            }
        }

        ind_points[i] = ind_closest; /*присвоение точки Х к точке У*/
        if (my_abs(f_x[i] - closest) >
            my_abs(y[1] - y[0])) { /*если ближайшая точка к f_x[i] на расстоянии больше, чем step_y, то ставим
                                      индекс, которого нету(не от 0 до 24)*/
            ind_points[i] = -1;
        }
    }
}

void print_function(const int ind_points[80]) {
    for (int y_ind = 0; y_ind < 25; y_ind++) {     /*цикл перебора индекса точки У*/
        for (int x_ind = 0; x_ind < 79; x_ind++) { /*цикл перебора индекса точки Х*/
            if (ind_points[x_ind] == y_ind) { /*условие совпадения индекса точки Х с индексом точки У*/
                printf("*"); /*Печать * при совпадении*/
            } else {
                printf("."); /*Печать точки при не совпадении*/
            }
        }
        printf("\n");
    }
}

int main() {
    double x[80];   /*массив оси Х*/
    double f_x[80]; /*массив ближайшего к значения в сетке y к реальному значению f_x */
    double y[25];   /*массив оси У*/
    int ind_points[80]; /*массив значений индексов точек по оси Х*/

    int expression_length;                               /* длина выражения */
    char expression[EXPRESSION_MAX_LEN];                 /* массив expression */
    struct stack_string *my_stack = init_stack_string(); /* инициализируем стек строк */
    char array[STACK_MAX_LEN][STACK_STR_MAX_LEN];        /* массив строк */
    HEAD head;

    read_expression(expression, &expression_length); /* читаем expression */

    init_stack_double(&head); /* инициализируем стек вещественных чисел */

    int array_length =
        fill_array(expression, expression_length, my_stack, array); /* парсим expression и заполняем array */

    init_grid(x, y); /* инициализируем сетку */

    for (int i = 0; i < 80; i++) { /*цикл перебора*/
        f_x[i] = counter(array, array_length, &head, x[i]); /*вычисляем точное значение введенной функции*/
    }
    fill_indexes(f_x, y, ind_points); /* заполняем индексы (ind_points) */
    print_function(ind_points);       /* печатаем стек */
    destroy_stack_string(my_stack);   /* освобождаем память (стек строк)*/
    destroy_stack_double(&head); /* освобождаем память (стек вещественных чисел)*/
}
