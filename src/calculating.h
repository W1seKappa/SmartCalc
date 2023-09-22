#ifndef CALCUL_H
#define CALCUL_H
#include "stack_double.h"
#define STACK_STR_MAX_LEN 15
#define STACK_MAX_LEN 100
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double counter(char array[STACK_MAX_LEN][STACK_STR_MAX_LEN], int n, HEAD *head, double x);

#endif