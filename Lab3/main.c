#include <stdio.h>
#include "Lab3_func.h"


const char *msgs[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show"};
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);


int dialog(const char *msgs[], int);
int (*fptr[])(struct Table *) = {NULL, D_Add, D_Find, D_Delete, D_Show};


int main() {

    struct Table* table = table_new();
    int rc;


    while (rc = dialog(msgs, NMsgs))
        if(!(fptr[rc](table)))
            break;


    printf("That's all. Bye!\n");
    return 0;
}
