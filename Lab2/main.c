#include <stdio.h>
#include "Lab2_func.h"



int main() {
    char rul=0;

    struct st *stack2 = NULL;
    do{
        stack_init(stack2);
        printf("\n Replay? Y or N?");
        scanf("%c", &rul);
    }while (rul != 'N');


    return 0;
}
