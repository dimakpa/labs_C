#include <stdio.h>
#include "Functions_Lab4b.h"


const char *msgs[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show", "5. Add with file", "6. Find and check time"};
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);



int (*fptr[])(struct Tree *) = {NULL, D_Add, D_Find, D_Delete, D_Show, D_File, D_FindTime};


int main() {

    int rc;
    struct Tree *root_tree = tree_new();


    while (rc = dialog(msgs, NMsgs))
        if(!(fptr[rc](root_tree)))
            break;


    printf("That's all. Bye!\n");
    return 0;
}