#ifndef STACK_DOUBLE_H
#define STACK_DOUBLE_H

typedef struct operators {
    double oper;
    struct operators *point;
} operators;

typedef struct HEAD {
    struct operators *point;
} HEAD;

void init_stack_double(HEAD *head);
double pop_stack_double(HEAD *head);
void push_stack_double(double sym, HEAD *head);
void destroy_stack_double(HEAD *head);

#endif