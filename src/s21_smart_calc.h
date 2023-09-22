#ifndef S21_SMART_CALC
#define S21_SMART_CALC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>





// help_func for valid
void skip_spaces(char* expression);
int validation(char* expression);
int is_digit(char expression_i);
int is_operand(char expression_i);
int is_func(char* expression, int i);





#endif



