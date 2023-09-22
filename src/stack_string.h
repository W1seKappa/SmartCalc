#ifndef STACK_STRING_H
#define STACK_STRING_H
#define STACK_STR_MAX_LEN 15

struct stack_string {
    struct elem *top;
};

struct elem {
    char str[STACK_STR_MAX_LEN];
    struct elem *prev;
};

void my_strcpy(char *str1, char *str2);

struct elem *push_stack_string(struct stack_string *my_stack, char str[STACK_STR_MAX_LEN]);

struct stack_string *init_stack_string();

int pop_stack_string(struct stack_string *my_stack, char str[STACK_STR_MAX_LEN]);

void destroy_stack_string(struct stack_string *my_stack);
#endif