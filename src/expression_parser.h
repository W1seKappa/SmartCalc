#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H
#define STACK_STR_MAX_LEN 15
#define EXPRESSION_MAX_LEN 200
#define STACK_MAX_LEN 100
#include "stack_string.h"

int fill_array(char expression[EXPRESSION_MAX_LEN], int n, struct stack_string *my_stack,
               char array[STACK_MAX_LEN][STACK_STR_MAX_LEN]);

#endif