#include "Lab5_functions.h"
#include <stdio.h>
#include <stdlib.h>
int D_VisualizeGraph(struct Graph *root_graph){
    FILE *fn = NULL;
    if((fn = fopen("graph.dot", "wb")) == NULL){
        printf("Can't create file\n");
        return 0;
    }

    fprintf(fn, "digraph Graph {\n");
    fprintf(fn, "    node [fontname=\"Arial\"];\n");
    struct Ver *par = root_graph->ver;
    while (par != NULL){
        fprintf(fn, "    %s [pos = \"%d,%d!\"]\n", par->name, par->x, par->y);
        par = par->next;
    }
    struct Ver *par1 = root_graph->ver;
    while (par1 != NULL){
        struct Reb_to_ver *rebro = par1->reb_to_ver;
        while (rebro != NULL){
            fprintf(fn, "    %s -> %s [label = %f]\n", par1->name, rebro->smezg->name, rebro->weight);
            rebro = rebro->next;
        }
        par1 = par1->next;
    }

    fprintf(fn, "}\n");

    fclose(fn);

    system("dot -Kfdp -n -Tpng -o graph.png graph.dot");

    return 1;
}

