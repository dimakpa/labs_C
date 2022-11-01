#include "Lab5_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const char *errmsgs[] = {"Error", "Ok", "Add to Ver", "Add to Reb", "Duplicate ver", "Element not founded", "Element deleted", "Koren"};

const char *msgs_find[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show", "5. Add with file"};
const int NMsgs_Find = sizeof(msgs_find) / sizeof(msgs_find[0]);
int (*fptr_find[])(struct Graph *) = {NULL, D_Add_Ver, D_Add_Reb, D_Delete_Ver, D_Delete_Reb, D_Show};

int D_Add_Ver(struct Graph* root_graph){
    int key1, key2, rc, n;
    char *inform;

    printf("Enter the X: ");
    n = getInt(&key1);
    if (n == 0)
        return 0;

    scanf("%*c");

    printf("Enter the Y: ");
    n = getInt(&key2);
    if (n == 0)
        return 0;

    scanf("%*c");

    printf("Enter the string of info: ");
    inform = get_str();
    if (inform == NULL) {
        return 0; //EOF
    }

    struct Ver *new_ver = ver_new();
    new_ver->x = key1;
    new_ver->y = key2;
    new_ver->name = inform;
    new_ver->reb_to_ver = NULL;
    new_ver->queue = NULL;
    new_ver->next = NULL;

    rc = inseart_ver(new_ver, root_graph);
    printf("%d", rc);
    return 1;
}

int inseart_ver(struct Ver *new_element, struct Graph *root){
    if(root->ver == NULL) {
        root->ver = new_element;
        return 2;
    }else{
        struct Ver *par = root->ver;
        while(par->next != NULL){
            if (new_element->x == par->x && new_element->y == par->y)
                return 4;
            par = par->next;
        }
        par->next = new_element;
    return 2;}
}

struct Ver *ver_new(){
    struct Ver *new_ver = (struct Ver*)calloc(1, sizeof(struct Ver));
    return new_ver;
}

int D_Add_Reb(struct Graph* root_graph){
    int key1, key2, key11, key22, rc, n;

    printf("Enter the X1: ");
    n = getInt(&key1);
    if (n == 0)
        return 0;

    scanf("%*c");

    printf("Enter the Y1: ");
    n = getInt(&key2);
    if (n == 0)
        return 0;

    printf("Enter the X2: ");
    n = getInt(&key11);
    if (n == 0)
        return 0;

    scanf("%*c");

    printf("Enter the Y2: ");
    n = getInt(&key22);
    if (n == 0)
        return 0;


    struct Ver *ver2 = find_ver(root_graph, key11, key22);
    struct Ver *ver1 = find_ver(root_graph, key1, key2);
    if (ver1 == NULL)
        rc = 0;
    else if (ver2 == NULL)
        rc = 0;
    else {
    inseart_reb(root_graph, ver1, ver2);
    inseart_reb(root_graph, ver2, ver1);
    rc = 3;
    }

    printf("%d", rc);
    ver1 = NULL;
    ver2 = NULL;
    return 1;

}

void inseart_reb(struct Graph *root, struct Ver *ver1, struct Ver *ver2){
    struct Reb_to_ver *par = ver1->reb_to_ver;
    struct Reb_to_ver *new_reb = (struct Reb_to_ver*)calloc(1, sizeof(struct Reb_to_ver));
    new_reb->smezg = ver2;
    new_reb->weight = calculations(ver1, ver2);
    new_reb->parent = ver1;
    if (par == NULL)
        ver1->reb_to_ver = new_reb;
    else{
        if(par == NULL)
            ver1->reb_to_ver = new_reb;
        else{
        while (par->next != NULL)
            par = par->next;
        par->next = new_reb;}
    }

}

double calculations(struct Ver *ver1, struct Ver *ver2){
    int a, b;
    double c;
    a = abs(ver1->x - ver2->x);
    b = abs(ver1->y - ver2->y);
    c = hypot(a, b);
    return c;
}

struct Ver *find_ver(struct Graph* root, int key1, int key2){
    if(root->ver == NULL)
        return NULL;
    struct Ver *par = root->ver;
    while (par != NULL){
        if (par->x == key1 && par->y == key2)
            return par;
        par = par->next;
    }
    return NULL;
}

int D_Delete_Ver(struct Graph* root_graph){
    int key1, key2, rc, n;

    printf("Enter the X: ");
    n = getInt(&key1);
    if (n == 0)
        return 0;

    scanf("%*c");

    printf("Enter the Y: ");
    n = getInt(&key2);
    if (n == 0)
        return 0;

    struct Ver *del_ver = find_ver(root_graph, key1, key2);
    if (del_ver == NULL)
        rc = 0;
    else {

        rc = del_rebro_of_ver(root_graph, del_ver);

    }
    printf("%d", rc);

}

int del_rebro_of_ver(struct Graph *root_graph, struct Ver *del_ver){
    struct Reb_to_ver *par = del_ver->reb_to_ver;
    while (par != NULL){

        del_rebro(par->smezg, del_ver->x, del_ver->y);
        par = par->next;
    }
    del_ver->reb_to_ver = NULL;
    if (root_graph->ver->x == del_ver->x && root_graph->ver->y == del_ver->y)
        root_graph->ver = root_graph->ver->next;
    else{
        struct Ver *parent = find_ver_do(root_graph, del_ver);
        parent->next = parent->next->next;
    }
    return 1;
}

struct Ver *find_ver_do(struct Graph* root, struct Ver *del_ver){
    if(root->ver == NULL)
        return NULL;
    struct Ver *par = root->ver;
    while (par != NULL){
        if (par->next->x == del_ver->x && par->next->y == del_ver->y)
            return par;
        par = par->next;
    }
    return NULL;
}

void del_rebro(struct Ver *ver, int x, int y ){
    struct Reb_to_ver *par = ver->reb_to_ver;

    if (par->smezg->x == x && par->smezg->y == y)
        ver->reb_to_ver = par->next;
    else {
        while (par->next != NULL) {
            if (par->next->smezg->x == x && par->next->smezg->y == y){
                struct Reb_to_ver *pop = par->next->next;
                par->next->smezg = NULL;
                par->next = NULL;
                par = pop;}
            else
                par = par->next;
        }
    }
}

int D_Delete_Reb(struct Graph* root_graph){
    int key1, key2, key11, key22, rc, n;

    printf("Enter the X1: ");
    n = getInt(&key1);
    if (n == 0)
        return 0;

    scanf("%*c");

    printf("Enter the Y1: ");
    n = getInt(&key2);
    if (n == 0)
        return 0;

    printf("Enter the X2: ");
    n = getInt(&key11);
    if (n == 0)
        return 0;

    scanf("%*c");

    printf("Enter the Y2: ");
    n = getInt(&key22);
    if (n == 0)
        return 0;

    struct Ver *ver1 = find_ver(root_graph, key1, key2);
    struct Ver *ver2 = find_ver(root_graph, key11, key22);

    if (ver1 == NULL)
        rc = 0;
    else if (ver2 == NULL)
        rc = 0;
    else {
        del_rebro(ver2, key1, key2);
        del_rebro(ver1, key11, key22);
        rc = 3;
        printf("%d", rc);
        ver1 = NULL;
        ver2 = NULL;
    }
    return 1;
}

int D_Show(struct Graph* root){

}

int D_Find_From_Ver(struct Graph* root_graph){
    int key1, key2, key11, key22, rc, n;

    printf("Enter the X1: ");
    n = getInt(&key1);
    if (n == 0)
        return 0;

    scanf("%*c");

    printf("Enter the Y1: ");
    n = getInt(&key2);
    if (n == 0)
        return 0;

    printf("Enter the X2: ");
    n = getInt(&key11);
    if (n == 0)
        return 0;

    scanf("%*c");

    printf("Enter the Y2: ");
    n = getInt(&key22);
    if (n == 0)
        return 0;

    find_bfs(root_graph, 0, key1, key2);
    struct Ver *s = find_ver(root_graph, key1, key2);
    struct Ver *v = find_ver(root_graph, key11, key22);

    print_path(root_graph, s, v);
    return 1;
}

void print_path(struct Graph *root_graph, struct Ver *s,struct Ver *v){

    if (v->x == s->x && v->y == s->y)
        printf("S- x: %d, y: %d, name: %s\n", s->x, s->y, s->name);
    else{
        if(v->queue->pred ==NULL)
            printf("There is no way");
        else{
            print_path(root_graph, s,v->queue->pred);
            printf("V- x: %d, y: %d, name: %s\n", v->x, v->y, v->name);
        }
    }
}

void find_bfs(struct Graph *root_graph, int start, int key1, int key2){
    struct Ver *s = find_ver(root_graph, key1, key2);
    struct Q *q = (struct Q*)calloc(1, sizeof(struct Q));
    struct Ver *perem;
    struct Ver *adj;
    initialization(root_graph);

    s->queue->color = 1;
    s->queue->d = 0;
    push_stack(s, q);

    while (q->ver != NULL){
        perem = take_stack(q);
        if (perem->reb_to_ver != NULL){
        adj = perem->reb_to_ver->smezg;
        do {
            if (adj->queue->color == 0) {
                adj->queue->color = 1;
                adj->queue->d = perem->queue->d + 1;
                adj->queue->pred = perem;
                push_stack(adj, q);
                adj->reb_to_ver = adj->reb_to_ver->next;
            }
        }while (adj->reb_to_ver != NULL);}

        perem->queue->color = 2;
    }
}

int D_Find_Short_Way(struct Graph* root_graph){
    int key1, key2, key11, key22, rc, n;

    printf("Enter the X1: ");
    n = getInt(&key1);
    if (n == 0)
        return 0;

    scanf("%*c");

    printf("Enter the Y1: ");
    n = getInt(&key2);
    if (n == 0)
        return 0;

    printf("Enter the X2: ");
    n = getInt(&key11);
    if (n == 0)
        return 0;

    scanf("%*c");

    printf("Enter the Y2: ");
    n = getInt(&key22);
    if (n == 0)
        return 0;


    find_ford(root_graph, key1, key2);
    struct Ver *v = find_ver(root_graph, key11, key22);
    printf("Min way: %d", v->ford->d);

    v = NULL;
    return 1;
}

void find_ford(struct Graph *root_graph, int key1, int key2){
    struct Ver *s = find_ver(root_graph, key1, key2);

    struct Ver *perem = root_graph->ver;
    initialization_ford(root_graph);
    s->ford->d = 0;

    while (perem != NULL){
        struct Reb_to_ver *rebro = perem->reb_to_ver;
        while (rebro != NULL){
            if (perem->ford->d > rebro->smezg->ford->d + rebro->weight){
                perem->ford->d = rebro->smezg->ford->d + rebro->weight;
                perem->ford->pred = rebro->smezg;
            }
            rebro = rebro->next;
        }
        perem = perem->next;
    }
}

void push_stack(struct Ver *s, struct Q *q){
    struct Ver *par = q->ver;
    if (q->ver == NULL)
        q->ver = s;
    else if (par->next == NULL)
        par->next = s;
    else {
        while (par->next != NULL)
            par = par->next;
        par->next = s;
    }
}

struct Ver *take_stack(struct Q *q){
    struct Ver *ret = q->ver;
    if (q->next == NULL)
        q->ver = NULL;
    else{
        q->ver = q->next->ver;
        q->next = q->next->next;}
    return ret;
}

void initialization(struct Graph *root){
    struct Ver *par = root->ver;
    while (par!=NULL){
        par->queue = (struct Queue*)calloc(1, sizeof(struct Queue));
        par->queue->pred = NULL;
        par->queue->color = 0;
        par->queue->d = 0;
        par = par->next;
    }
}

void initialization_ford(struct Graph *root_graph){
    struct Ver *par = root_graph->ver;
    while (par!=NULL){
        par->ford = (struct Ford*)calloc(1, sizeof(struct Ford));
        par->ford->pred = NULL;
        par->ford->d = 1000;
        par = par->next;
    }
}

int D_Find_Short_Ostov(struct Graph *root_graph){

    initialization_kruskal(root_graph);
    mst_prim(root_graph);
    insert_to_ostov(root_graph, root_graph->list_reb);
    return 1;
}

void initialization_kruskal(struct Graph *root_graph){
    struct Ver *par = root_graph->ver;
    struct Reb_to_ver *list_reb_graph = root_graph->list_reb;
    while(par != NULL) {
        par->ostov = (struct Ostov*)calloc(1, sizeof(struct Ostov));
        par->ostov->pred = par;
        par->ostov->rank = 10000;
        struct Reb_to_ver *reb_list = par->reb_to_ver;

        reb_list = sort_spisok_reb(reb_list);

        while (reb_list != NULL){
            if (root_graph->list_reb == NULL){
                root_graph->list_reb = (struct Reb_to_ver*)calloc(1, sizeof(struct Reb_to_ver));
                root_graph->list_reb= reb_list;
                list_reb_graph = root_graph->list_reb;
            }
            else {
                list_reb_graph->next = reb_list;
                list_reb_graph = list_reb_graph->next;
            }
            reb_list = NULL;
        }
        par = par->next;
    }

    //sort
    root_graph->list_reb = sort_spisok_reb(root_graph->list_reb);
    root_graph->list_reb->parent->ostov->rank = 0;

}

struct Reb_to_ver *sort_spisok_reb(struct Reb_to_ver *list_reb){
    struct Reb_to_ver *root_rebr = list_reb;
    struct Reb_to_ver *new_root = NULL;

    while (root_rebr != NULL){
        struct Reb_to_ver *reb_par = root_rebr;
        root_rebr = root_rebr->next;
        if (new_root == NULL || reb_par->weight < new_root->weight){
            reb_par->next = new_root;
            new_root = reb_par;
        }else{
            struct Reb_to_ver *reb_par2 = new_root;
            while (reb_par2->next != NULL && !(reb_par->weight < reb_par2->next->weight))
                reb_par2 = reb_par2->next;
            reb_par->next = reb_par2->next;
            reb_par2->next = reb_par;
        }
    }
    return new_root;
}

void mst_prim(struct Graph *root_graph){
    struct Reb_to_ver *root_rebr = root_graph->list_reb;
    while (root_rebr != NULL){
            struct Ver *u = root_rebr->parent;
            struct Reb_to_ver *reb = u->reb_to_ver;
            struct Ver *v = reb->smezg;
            while (reb != NULL){
                if(v == find_q(root_graph, v) && reb->weight < v->ostov->rank){
                    v->ostov->pred = u;
                    v->ostov->rank = reb->weight;
                }
                reb = reb->next;
            }
        root_rebr = root_rebr->next;
    }
}
struct Ver *find_q(struct Graph *root_graph, struct Ver *v){
    struct Reb_to_ver *par = root_graph->list_reb;
    while (par != NULL){
        if (par->parent == v)
            return v;
        else
            par = par->next;
    }
    return NULL;
}

struct Ver *find_set(struct Ver *ver){
    if (ver->ostov->pred != ver)
        ver->ostov->pred = find_set(ver->ostov->pred);
}
void tree_union(struct Ver *u,struct Ver *v){
    link(find_set(u), find_set(v));
}
void link(struct Ver *x, struct Ver *y){
    if (x->ostov->rank > y->ostov->rank)
        y->ostov->pred = x;
    else{
        x->ostov->pred = y;
        if (x->ostov->rank == y->ostov->rank)
            y->ostov->rank = y->ostov->rank +1;
    }
}
void insert_to_ostov(struct Graph *root_graph, struct Reb_to_ver *root_rebr){

    struct Ver *par = root_graph->ver;
    while(par != NULL){
        struct Ver *par_new = par;
        while (par_new != NULL){

            par_new = par_new->next;
        }

        par = par->next;
    }
    struct Ver *ver_root1 = find_ver_ostov(root_graph, root_rebr->parent->x, root_rebr->parent->y);
    if (ver_root1 == NULL)
        inseart_ver_ostov(root_rebr->parent, root_graph );
    struct Ver *ver_root2 = find_ver_ostov(root_graph, root_rebr->smezg->x, root_rebr->smezg->y);
    if (ver_root2 == NULL)
        inseart_ver_ostov(root_rebr->smezg, root_graph);
    struct Ver *ver2 = find_ver_ostov(root_graph, root_rebr->smezg->x, root_rebr->smezg->y);
    struct Ver *ver1 = find_ver_ostov(root_graph, root_rebr->parent->x, root_rebr->parent->y);
    if(ver_root2 != NULL || ver_root1 != NULL) {
        inseart_reb_ostov(root_graph, ver1, ver2);
        inseart_reb_ostov(root_graph, ver2, ver1);
    }
}
void inseart_ver_ostov(struct Ver *ver, struct Graph *root){
    struct Ver *new_element = (struct Ver*)calloc(1, sizeof(struct Ver));

    new_element->name = ver->name;
    new_element->x = ver->x;
    new_element->y = ver->y;
    new_element->reb_to_ver = NULL;
    new_element->next = NULL;
    new_element->ostov = NULL;
    new_element->ford = NULL;
    new_element->queue = NULL;

    if(root->ostov_ver == NULL) {
        root->ostov_ver = new_element;
    }else{
        struct Ver *par = root->ostov_ver;
        while(par->next != NULL){
            if (new_element->x == par->x && new_element->y == par->y)
                break;
            par = par->next;
        }
        par->next = new_element;
        }
}
void inseart_reb_ostov(struct Graph *root, struct Ver *ver1, struct Ver *ver2){
    struct Reb_to_ver *par = ver1->reb_to_ver;
    struct Reb_to_ver *new_reb = (struct Reb_to_ver*)calloc(1, sizeof(struct Reb_to_ver));
    new_reb->smezg = ver2;
    new_reb->weight = calculations(ver1, ver2);
    new_reb->parent = ver1;
    if (par == NULL)
        ver1->reb_to_ver = new_reb;
    else{
        if(par == NULL)
            ver1->reb_to_ver = new_reb;
        else{
            while (par->next != NULL)
                par = par->next;
            par->next = new_reb;}
    }
}
struct Ver *find_ver_ostov(struct Graph* root, int key1, int key2){
    if(root->ostov_ver == NULL)
        return NULL;
    struct Ver *par = root->ostov_ver;
    while (par != NULL){
        if (par->x == key1 && par->y == key2)
            return par;
        par = par->next;
    }
    return NULL;
}

int D_Graphviz_ostov(struct Graph *root_graph){
    FILE *fn = NULL;
    if((fn = fopen("graph.dot", "wb")) == NULL){
        printf("Can't create file\n");
        return 0;
    }

    fprintf(fn, "digraph Graph {\n");
    fprintf(fn, "    node [fontname=\"Arial\"];\n");
    struct Ver *par = root_graph->ostov_ver;
    while (par != NULL){
        fprintf(fn, "    %s [pos = \"%d,%d!\"]\n", par->name, par->x, par->y);
        par = par->next;
    }
    struct Ver *par1 = root_graph->ostov_ver;
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

int getInt(int *a)
{
    int n;
    do{
        n = scanf("%d", a, sizeof(int));
        if (n < 0)
            return 0;
        if (n == 0){
            printf("%s\n", "Error! Repeat input");
            scanf("%*c", 0);
        }
    } while (n == 0);
    return 1;
}
char* get_str()
{
    char buf[81] = { 0 };
    char* res = NULL;
    int len = 0;
    int n = 0;
    do {
        n = scanf("%80[^\n]", buf, 80);
        if (n < 0) {
            if (!res)
                return NULL;
        }
        else if (n > 0) {
            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            res = (char*)realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        }
        else
            scanf("%*c");
    } while (n > 0);

    if (len > 0)
        res[len] = '\0';
    else
        res = (char*)calloc(1, sizeof(char));

    return res;
}
int dialog(const char *msgs[], int N)
{
    char *errmsg = "";
    int rc;
    int i, n;
    do{
        puts(errmsg);
        errmsg = "You are wrong. Repeat, please!";
        for(i = 0; i < N; ++i)
            puts(msgs[i]);
        puts("Make your choice: --> ");
        n = getInt(&rc);
        if(n == 0)
            rc = 0;
    } while(rc < 0 || rc >= N);
    return rc;
}
struct Graph *graph_new(){
    struct Graph* graph_tree = (struct Graph*)calloc(1, sizeof(struct Graph));
    return graph_tree;
}