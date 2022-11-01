#include <stdio.h>
#include <malloc.h>
#define NMAX 20
#include "Lab2_func.h"

#ifdef VEC
int prior(char a){
    switch(a)
    {
        case '*':
            return 3;
        case '/':
            return 3;

        case '-':
            return 2;
        case '+':
            return 2;

        case '(':
            return 1;
    }
}



void init(struct st *stk) {
    stk->top = 0;
}

void stack_init(struct st *stack2){

    char a[80], outstring[80];
    int k, point;
    k=0;
    point=0;

    printf("Put infix equation, on end use '=' :\n");
    gets(a);

    while (a[k] != '\0' && a[k] != '=')
    {

        if (a[k] == ')') {
            while ((stack2->c[stack2->top-1]) != '(')
                outstring[point++] = delet_vector(stack2);
            delet_vector(stack2);
        }

        if (a[k] >= 'a' && a[k] <= 'z')
            outstring[point++] = a[k];

        if (a[k] == '('){
            if ((stack2 == NULL) || (stack2->top) == 0) {
                stack2 = (struct st*)malloc(sizeof(struct st));
                init(stack2);
                push_vector(stack2, a[k]);
            }
            else
                push_vector(stack2, a[k]);}

        if (a[k] == '+' || a[k] == '-' || a[k] == '/' || a[k] == '*') {

            if ((stack2 == NULL) || (stack2->top == 0)){
                stack2 = (struct st*)malloc(sizeof(struct st));
                init(stack2);
                push_vector(stack2, a[k]);}

            else if ((prior(stack2->c[stack2->top-1])) < (prior(a[k])))
                push_vector(stack2, a[k]);

            else {
                while ((prior(stack2->c[stack2->top-1]) >= prior(a[k])) && (stack2->top != 0))
                    outstring[point++] = delet_vector(stack2);
                push_vector(stack2, a[k]);
            }
        }
        k++;
    }

    do {
        outstring[point++] = delet_vector(stack2);
    }while (stack2->top != 0);

    outstring[point] = '\0';
    printf("\n%s\n", outstring);
    free(stack2);
}

void push_vector(struct st *st1, char a) {

    if(st1->top < NMAX) {
        st1->c[st1->top] = a;
        st1->top++;
    } else
        printf("Стек полон, количество элементов: %d !\n", st1->top);
}

char delet_vector(struct st *st1){
    char a;
    if(st1->top>0) {
        st1->top--;
        a = st1->c[st1->top];
        return a;
    }else
        return 0;
}

#endif