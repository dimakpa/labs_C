#include <stdio.h>
#include "Lab5_functions.h"


const char *msgs[] = {"0. Quit", "1. Add Ver", "2. Add Rebro", "3. Delete Ver", "4. Delete Rebro", "5. Show", "6. Find from verch", "7. Graphviz", "8. Find shortest way", "9. Find shortest ostov", "10. Graphviz of Ostov"};
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);



int (*fptr[])(struct Graph *) = {NULL, D_Add_Ver, D_Add_Reb, D_Delete_Ver, D_Delete_Reb, D_Show, D_Find_From_Ver,D_VisualizeGraph, D_Find_Short_Way, D_Find_Short_Ostov, D_Graphviz_ostov};


int main() {

    int rc;
    struct Graph *root_graph = graph_new();



    while (rc = dialog(msgs, NMsgs))
        if(!(fptr[rc](root_graph)))
            break;


    printf("That's all. Bye!\n");
    return 0;
}