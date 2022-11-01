#include <stdio.h>
#include <malloc.h>
#define NMAX 20
#include "Lab2_func.h"

#ifdef LIST
void stack_init(struct st *stack1){
    char a[80], outstring[80];
    int k, point;
    k=0;
    point=0;

    printf("Put infix equation, on end use '=' :\n");
    gets(a);
    while (a[k] != '\0' && a[k] != '=')
    {
        if (a[k] == ')') {
            while ((stack1->c) != '(')
                outstring[point++] = delet(&stack1);
            delet(&stack1);
        }

        if (a[k] >= 'a' && a[k] <= 'z')
            outstring[point++] = a[k];

        if (a[k] == '(')
            stack1 = push(stack1, '(');

        if (a[k] == '+' || a[k] == '-' || a[k] == '/' || a[k] == '*') {

            if (stack1 == NULL)
                stack1 = push(stack1, a[k]);

            else if (prior(stack1->c) < prior(a[k]))
                stack1 = push(stack1, a[k]);

            else {
                while ((stack1 != NULL) && (prior(stack1->c) >= prior(a[k])))
                    outstring[point++] = delet(&stack1);
                stack1 = push(stack1, a[k]);
            }
        }
        k++;
    }

    while (stack1 != NULL)
        outstring[point++] = delet(&stack1);

    outstring[point] = '\0';
    printf("\n%s\n", outstring);
}

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

char delet(struct st **head){
    struct st *PTR;
    char a;
    if(*head==NULL)
        return '\0';
    PTR=*head;
    a=PTR->c;
    *head=PTR->next;
    free(PTR);
    return a;
}

struct st *push(struct  st *head, char a){
    struct st *ptr;
    ptr=malloc(sizeof(struct st));
    ptr->c=a;
    ptr->next=head;
    return ptr;
}
#endif