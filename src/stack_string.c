#include "stack_string.h"

#include <stdio.h>
#include <stdlib.h>

void my_strcpy(char *str1, char *str2) { /* копируем строку str2 в str1 */
    while (*str2 != '\0') {
        *str1 = *str2;
        str1++;
        str2++;
    }
    *str1 = '\0';
}

struct elem *push_stack_string(struct stack_string *my_stack, char str[STACK_STR_MAX_LEN]) {
    /* кладем в стек строку str */
    struct elem *cur =
        (struct elem *)malloc(sizeof(struct elem)); /* выделяем динамическую память под элемент стека */
    my_strcpy(cur->str, str); /* копируем в элемент стека  строку str*/
    if (my_stack != NULL) {
        if (my_stack->top == NULL) { /* если стек пустой */
            my_stack->top = cur;     /* вершина стека указывает на cur */
            cur->prev = NULL;
        } else {                       /* если стек не пустой */
            cur->prev = my_stack->top; /* cur указывает на предыдущую вершину*/
            my_stack->top = cur;       /* вершина стека указывает на cur */
        }
    }
    return cur;
}

struct stack_string *init_stack_string() {
    /* инициализируем стек, выделяем память и возвращаем его */
    struct stack_string *head = (struct stack_string *)malloc(sizeof(struct stack_string));
    head->top = NULL;
    return head;
}

int pop_stack_string(struct stack_string *my_stack, char str[STACK_STR_MAX_LEN]) {
    /* выталкиваем из стекa в строку str */
    int k = 0;
    if (my_stack != NULL && my_stack->top != NULL) { /* если в стеке есть элементы */
        struct elem *cur = my_stack->top; /* выталкиваем из стекa в строку str */
        my_stack->top = cur->prev; /* перемещаем указатель на следующий элемент стекa */
        my_strcpy(str, cur->str); /* копируем cur->str в строку str */
        free(cur);                /* освобождаем память */
        k = 1;
    } else {
        str[0] = '\0'; /* если в стеке ничего нет возвращяем пустую строку str */
    }
    return k;
}

void destroy_stack_string(struct stack_string *my_stack) {
    /* удаляем все элементы и освобождаем память */
    while (my_stack->top != NULL) { /* пока в стеке что-то есть выталкиваем элементы */
        char cur_str[STACK_STR_MAX_LEN];
        pop_stack_string(my_stack, cur_str);
    }
    free(my_stack); /* освобождаем память */
}
