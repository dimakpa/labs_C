#include "Functions_Lab4b.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define rul  16


const char *errmsgs[] = {"Error", "Ok", "Add to ne", "Add to nw","Add to sw","Add to se", "Add to root", "Duplicate key", "Element not founded", "Element deleted", "Koren"};

const char *msgs_find[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show", "5. Add with file"};
const int NMsgs_Find = sizeof(msgs_find) / sizeof(msgs_find[0]);
int (*fptr_find[])(struct Tree *) = {NULL, D_Add, D_Find, D_Delete, D_Show, D_File};

int D_Add(struct Tree* root_tree)
{
    int key1, key2, rc, n;
    char *inform;
    struct Item *elem_new = (struct Item*) calloc(1, sizeof(struct Item));

    printf("Enter the 1 key: ");
    n = getInt(&key1);
    if (n == 0)
        return 0;

    scanf("%*c");

    printf("Enter the 2 key: ");
    n = getInt(&key2);
    if (n == 0)
        return 0;

    scanf("%*c");

    printf("Enter the string of info: ");
    inform = get_str();
    if (inform == NULL) {
        return 0; //EOF
    }

    elem_new->xy = calloc(1, sizeof(struct Xy));
    elem_new->xy->x = key1;
    elem_new->xy->y = key2;
    elem_new->info = calloc(1, sizeof(char));
    strcpy(elem_new->info, inform);

    if (root_tree->root == NULL)
    {
        root_tree->root = (struct Node*)calloc(1, sizeof(struct Node));
        root_tree->root->nw = NULL;
        root_tree->root->ne = NULL;
        root_tree->root->sw = NULL;
        root_tree->root->se = NULL;
        root_tree->root->par = NULL;
        root_tree->root->xy = calloc(1, sizeof(struct Xy));
        root_tree->root->xy->x = key1;
        root_tree->root->xy->y = key2;
        root_tree->root->xy->width = rul;
        rc = 4;
    }else if (elem_new->xy->x > (root_tree->root->xy->x + rul))
        rc = 0;
    else if (elem_new->xy->y > (root_tree->root->xy->y + rul))
        rc = 0;
    else {
        rc = vstavka_quadro(elem_new, root_tree);
    }
    printf("%s:\n%d\t %d\n", errmsgs[rc], key1, key2);
    return 1;
}

int vstavka_quadro(struct Item *elem_new, struct Tree *root_tree){
    int rc, k;
    struct Node *ptr = root_tree->root;
    struct Node *par = NULL;
    while(ptr != NULL){
        par = ptr;
        if((elem_new->xy->x > ptr->xy->x && elem_new->xy->y > ptr->xy->y) || (elem_new->xy->x == ptr->xy->x && elem_new->xy->y == ptr->xy->y))
            ptr = ptr->ne;
        else if((elem_new->xy->x < ptr->xy->x && elem_new->xy->y > ptr->xy->y) || (elem_new->xy->x < ptr->xy->x && elem_new->xy->y == ptr->xy->y))
            ptr = ptr->nw;
        else if(elem_new->xy->x < ptr->xy->x && elem_new->xy->y < ptr->xy->y)
            ptr = ptr->sw;
        else if((elem_new->xy->x > ptr->xy->x && elem_new->xy->y < ptr->xy->y) || (elem_new->xy->x == ptr->xy->x && elem_new->xy->y < ptr->xy->y))
            ptr = ptr->se;
    }

    if((elem_new->xy->x > par->xy->x && elem_new->xy->y > par->xy->y) || (elem_new->xy->x == par->xy->x && elem_new->xy->y == par->xy->y)){
        if (par->ine == NULL){
            par->ine = elem_new;
            rc = 2;}
        else{
            struct Item *item_ptr = par->ine;
            par->ine = NULL;
            struct Node *new_node = (struct Node*)calloc(1, sizeof(struct Node));
            new_node->xy = calloc(1, sizeof(struct Xy));
            new_node->xy->x = par->xy->x + par->xy->width/2;
            new_node->xy->y = par->xy->y + par->xy->width/2;
            new_node->xy->width = par->xy->width/2;
            new_node->par = par;
            par->ne = new_node;
            k = vstavka_quadro(item_ptr, root_tree);
            rc = vstavka_quadro(elem_new, root_tree);
        }
    }
    else if((elem_new->xy->x < par->xy->x && elem_new->xy->y > par->xy->y) || ((elem_new->xy->x < par->xy->x && elem_new->xy->y == par->xy->y))){
        if (par->inw == NULL){
            par->inw = elem_new;
            rc = 3;}
        else{
            struct Item *item_ptr = par->ine;
            par->inw = NULL;
            struct Node *new_node = (struct Node*)calloc(1, sizeof(struct Node));
            new_node->xy = calloc(1, sizeof(struct Xy));
            new_node->xy->x = par->xy->x - par->xy->width/2;
            new_node->xy->y = par->xy->y + par->xy->width/2;
            new_node->xy->width = par->xy->width/2;
            new_node->par = par;
            par->nw = new_node;
            k = vstavka_quadro(item_ptr, root_tree);
            rc = vstavka_quadro(elem_new, root_tree);
        }
    } else if(elem_new->xy->x < par->xy->x && elem_new->xy->y < par->xy->y){
        if (par->isw == NULL){
            par->isw = elem_new;
            rc = 4;}
        else{
            struct Item *item_ptr = par->isw;
            par->isw = NULL;
            struct Node *new_node = (struct Node*)calloc(1, sizeof(struct Node));
            new_node->xy = calloc(1, sizeof(struct Xy));
            new_node->xy->x = par->xy->x - par->xy->width/2;
            new_node->xy->y = par->xy->y - par->xy->width/2;
            new_node->xy->width = par->xy->width/2;
            new_node->par = par;
            par->sw = new_node;
            k = vstavka_quadro(item_ptr, root_tree);
            rc = vstavka_quadro(elem_new, root_tree);
        }}
    else if((elem_new->xy->x > par->xy->x && elem_new->xy->y < par->xy->y) || (elem_new->xy->x == par->xy->x && elem_new->xy->y < par->xy->y)){
        if (par->ise == NULL){
            par->ise = elem_new;
            rc = 5;}
        else{
            struct Item *item_ptr = par->ine;
            par->ise = NULL;
            struct Node *new_node = (struct Node*)calloc(1, sizeof(struct Node));
            new_node->xy = calloc(1, sizeof(struct Xy));
            new_node->xy->x = par->xy->x + par->xy->width/2;
            new_node->xy->y = par->xy->y - par->xy->width/2;
            new_node->xy->width = par->xy->width/2;
            new_node->par = par;
            par->se = new_node;
            k = vstavka_quadro(item_ptr, root_tree);
            rc = vstavka_quadro(elem_new, root_tree);
        }}
    else
        rc = 0;
    return rc;
}

int D_Find(struct Tree* root)
{
    int key1, key2, rc, n;

    printf("Enter the 1 key: ");
    n = getInt(&key1);
    if (n == 0)
        return 0;

    scanf("%*c");

    printf("Enter the 2 key: ");
    n = getInt(&key2);
    if (n == 0)
        return 0;

    scanf("%*c");

    struct Node *ptr = root->root;
    struct Item *tree_new;
    struct Node *tree_new_node = find_recurs(ptr, key1, key2);
    if (tree_new_node->ine->xy->x == key1 && tree_new_node->ine->xy->y == key2)
        tree_new = tree_new_node->ine;
    else if (tree_new_node->inw->xy->x == key1 && tree_new_node->inw->xy->y == key2)
        tree_new = tree_new_node->inw;
    else if (tree_new_node->isw->xy->x == key1 && tree_new_node->isw->xy->y == key2)
        tree_new = tree_new_node->isw;
    else if (tree_new_node->ise->xy->x == key1 && tree_new_node->ise->xy->y == key2)
        tree_new = tree_new_node->ise;
    if (tree_new == NULL)
        rc = 6;
    else{
        printf("information:\"%s\"", tree_new->info);
        rc = 1;}
    printf("%s:\n%d\t %d\n", errmsgs[rc], key1, key2);
    return 1;
}

struct Node *find_recurs(struct Node *ptr,int key1, int key2){

    struct Node *res;
    if (ptr == NULL)
        return NULL;
    else{
        if(ptr->xy->x == key1 && ptr->xy->y == key2)
            res = ptr;
        else if(key1 < ptr->xy->x && key2 < ptr->xy->y){
            if (ptr->sw == NULL)
                return ptr;
            res = find_recurs(ptr->sw, key1, key2);
        }
        else if(key1 > ptr->xy->x && key2 < ptr->xy->y){
            if (ptr->se == NULL)
                return ptr;
            res = find_recurs(ptr->se, key1, key2);
        }
        else if(key1 > ptr->xy->x && key2 > ptr->xy->y){
            if (ptr->ne == NULL)
                return ptr;
            res = find_recurs(ptr->ne, key1, key2);
        }
        else if((key1 < ptr->xy->x) && (key2 > ptr->xy->y)){
            if (ptr->nw == NULL)
                return ptr;
            res = find_recurs(ptr->nw, key1, key2);
        }
    }
    return res;
}


int D_Delete(struct Tree* root){

    int key1, key2, rc, n;

    printf("Enter the 1 key: ");
    n = getInt(&key1);
    if (n == 0)
        return 0;

    scanf("%*c");

    printf("Enter the 2 key: ");
    n = getInt(&key2);
    if (n == 0)
        return 0;

    scanf("%*c");

    struct Node *ptr = root->root;

    struct Item *tree_delet = delete_recurs(root, ptr, key1, key2);


    if (tree_delet == NULL)
        rc = 6;
    else{
        printf("information:\"%s\" ", tree_delet->info);
        rc = 7;}
    printf("%s:\n%d\t %d\n", errmsgs[rc], key1, key2);
    return 1;
}
struct Item *delete_recurs(struct Tree *root, struct Node *ptr,int key1, int key2){


    struct Node *res = find_recurs(ptr, key1, key2);
    if (ptr == NULL)
        return NULL;

    struct Item del;
    struct Node *p;
    struct Item not_del;
    struct Item *not_del_1;

    if(res->ine != NULL && res->inw == NULL && res->isw == NULL && res->ise == NULL){
        del.xy = res->ine->xy;
        del.info = res->ine->info;
        res->ine->info = NULL;
        res->ine->xy = NULL;
        res->ine = NULL;
        root->root->ine = NULL;
        root->root = NULL;
        root = NULL;
    }
    else if(res->ine == NULL && res->inw != NULL && res->isw == NULL && res->ise == NULL){
        del.xy = res->inw->xy;
        del.info = res->inw->info;
        res->inw->info = NULL;
        res->inw->xy = NULL;
        res->inw = NULL;
        root->root->inw = NULL;
        root->root = NULL;
        root = NULL;
    }
    else if(res->ine == NULL && res->inw == NULL && res->isw != NULL && res->ise == NULL){
        del.xy = res->isw->xy;
        del.info = res->isw->info;
        res->isw->info = NULL;
        res->isw->xy = NULL;
        res->isw = NULL;
        root->root->isw = NULL;
        root->root = NULL;
        root = NULL;
    }
    else if(res->ine == NULL && res->inw == NULL && res->isw == NULL && res->ise != NULL){
        del.xy = res->ise->xy;
        del.info = res->ise->info;
        res->ise->info = NULL;
        res->ise->xy = NULL;
        res->ise = NULL;
        root->root->ise = NULL;
        root->root = NULL;
        root = NULL;
    }


    else if(res->ine == NULL && res->inw == NULL && res->isw != NULL && res->ise != NULL){
        if(res->isw->xy->x == key1 && res->isw->xy->y == key2){
            del.xy = res->isw->xy;
            del.info = res->isw->info;
            res->isw->info = NULL;
            res->isw->xy = NULL;
            not_del.info = res->ise->info;
            res->isw = NULL;
            not_del.xy = res->ise->xy;
            not_del_1 = &not_del;
            res->ise->info = NULL;
            res->ise->xy = NULL;
            res->ise = NULL;
            del_node(res);
            res = NULL;
            int rc = vstavka_quadro(not_del_1, root);
            printf("%d\n", rc);
        }
        else if (res->ise->xy->x == key1 && res->ise->xy->y == key2){
            del.xy = res->ise->xy;
            del.info = res->ise->info;
            res->ise->info = NULL;
            res->ise->xy = NULL;
            res->ise = NULL;
            not_del.info = res->isw->info;
            not_del.xy = res->isw->xy;
            not_del_1 = &not_del;
            res->isw->info = NULL;
            res->isw->xy = NULL;
            res->isw = NULL;
            del_node(res);
            res = NULL;
            int rc = vstavka_quadro(not_del_1, root);
            printf("%d\n", rc);
        }else return NULL;
        }
    else if(res->ine == NULL && res->inw != NULL && res->isw == NULL && res->ise != NULL){
        if(res->inw->xy->x == key1 && res->inw->xy->y == key2){
            del.xy = res->inw->xy;
            del.info = res->inw->info;
            res->inw->info = NULL;
            res->inw->xy = NULL;
            res->inw = NULL;
            not_del.info = res->ise->info;
            not_del.xy = res->ise->xy;
            not_del_1 = &not_del;
            res->ise->info = NULL;
            res->ise->xy = NULL;
            res->ise = NULL;
            del_node(res);
            res = NULL;
            int rc = vstavka_quadro(not_del_1, root);
            printf("%d\n", rc);
        }
        else if (res->ise->xy->x == key1 && res->ise->xy->y == key2){
            del.xy = res->ise->xy;
            del.info = res->ise->info;
            res->ise->info = NULL;
            res->ise->xy = NULL;
            res->ise = NULL;
            not_del.info = res->inw->info;
            not_del.xy = res->inw->xy;
            not_del_1 = &not_del;
            res->inw->info = NULL;
            res->inw->xy = NULL;
            res->inw = NULL;
            del_node(res);
            res = NULL;
            int rc = vstavka_quadro(not_del_1, root);
            printf("%d\n", rc);
        }else return NULL;
        }
    else if(res->ine != NULL && res->inw == NULL && res->isw == NULL && res->ise != NULL){
        if(res->ine->xy->x == key1 && res->ine->xy->y == key2){
            del.xy = res->ine->xy;
            del.info = res->ine->info;
            res->ine->info = NULL;
            res->ine->xy = NULL;
            res->ine = NULL;
            not_del.info = res->ise->info;
            not_del.xy = res->ise->xy;
            not_del_1 = &not_del;
            res->ise->info = NULL;
            res->ise->xy = NULL;
            res->ise = NULL;
            del_node(res);
            res = NULL;
            int rc = vstavka_quadro(not_del_1, root);
            printf("%d\n", rc);
        }
        else if (res->ise->xy->x == key1 && res->ise->xy->y == key2){
            del.xy = res->ise->xy;
            del.info = res->ise->info;
            res->ise->info = NULL;
            res->ise->xy = NULL;
            res->ise = NULL;
            not_del.info = res->ine->info;
            not_del.xy = res->ine->xy;
            not_del_1 = &not_del;
            res->ine->info = NULL;
            res->ine->xy = NULL;
            res->ine = NULL;
            del_node(res);
            res = NULL;
            int rc = vstavka_quadro(not_del_1, root);
            printf("%d\n", rc);
        }else return NULL;
        }
    else if(res->ine == NULL && res->inw != NULL && res->isw != NULL && res->ise == NULL){
        if(res->isw->xy->x == key1 && res->isw->xy->y == key2){
            del.xy = res->isw->xy;
            del.info = res->isw->info;
            res->isw->info = NULL;
            res->isw->xy = NULL;
            res->isw = NULL;
            not_del.info = res->inw->info;
            not_del.xy = res->inw->xy;
            not_del_1 = &not_del;
            res->inw->info = NULL;
            res->inw->xy = NULL;
            res->inw = NULL;
            del_node(res);
            res = NULL;
            int rc = vstavka_quadro(not_del_1, root);
            printf("%d\n", rc);
        }
        else if (res->inw->xy->x == key1 && res->inw->xy->y == key2){
            del.xy = res->inw->xy;
            del.info = res->inw->info;
            res->inw->info = NULL;
            res->inw->xy = NULL;
            res->inw = NULL;
            not_del.info = res->isw->info;
            not_del.xy = res->isw->xy;
            not_del_1 = &not_del;
            res->isw->info = NULL;
            res->isw->xy = NULL;
            res->isw = NULL;
            del_node(res);
            res = NULL;
            int rc = vstavka_quadro(not_del_1, root);
            printf("%d\n", rc);
        }else return NULL;
        }
    else if(res->ine != NULL && res->inw == NULL && res->isw != NULL && res->ise == NULL){
        if(res->isw->xy->x == key1 && res->isw->xy->y == key2){
            del.xy = res->isw->xy;
            del.info = res->isw->info;
            res->isw->info = NULL;
            res->isw->xy = NULL;
            res->isw = NULL;
            not_del.info = res->ine->info;
            not_del.xy = res->ine->xy;
            not_del_1 = &not_del;
            res->ine->info = NULL;
            res->ine->xy = NULL;
            res->ine = NULL;
            del_node(res);
            res = NULL;
            int rc = vstavka_quadro(not_del_1, root);
            printf("%d\n", rc);
        }
        else if (res->ine->xy->x == key1 && res->ine->xy->y == key2){
            del.xy = res->ine->xy;
            del.info = res->ine->info;
            res->ine->info = NULL;
            res->ine->xy = NULL;
            res->ine = NULL;
            not_del.info = res->isw->info;
            not_del.xy = res->isw->xy;
            not_del_1 = &not_del;
            res->isw->info = NULL;
            res->isw->xy = NULL;
            res->isw = NULL;
            del_node(res);
            res = NULL;
            int rc = vstavka_quadro(not_del_1, root);
            printf("%d\n", rc);
        }else return NULL;
        }
    else if(res->ine != NULL && res->inw != NULL && res->isw == NULL && res->ise != NULL){
        if(res->inw->xy->x == key1 && res->inw->xy->y == key2){
            del.xy = res->inw->xy;
            del.info = res->inw->info;
            res->inw->info = NULL;
            res->inw->xy = NULL;
            res->inw = NULL;
            not_del.info = res->ine->info;
            not_del.xy = res->ine->xy;
            not_del_1 = &not_del;
            res->ine->info = NULL;
            res->ine->xy = NULL;
            res->ine = NULL;
            del_node(res);
            res = NULL;
            int rc = vstavka_quadro(not_del_1, root);
            printf("%d\n", rc);
        }
        else if (res->ine->xy->x == key1 && res->ine->xy->y == key2){
            del.xy = res->ine->xy;
            del.info = res->ine->info;
            res->ine->info = NULL;
            res->ine->xy = NULL;
            res->ine = NULL;
            not_del.info = res->inw->info;
            not_del.xy = res->inw->xy;
            not_del_1 = &not_del;
            res->inw->info = NULL;
            res->inw->xy = NULL;
            res->inw = NULL;
            del_node(res);
            res = NULL;
            int rc = vstavka_quadro(not_del_1, root);
            printf("%d\n", rc);
        }else return NULL;
        }


    else if(res->ine == NULL && res->inw != NULL && res->isw != NULL && res->ise != NULL){
        if(res->isw->xy->x == key1 && res->isw->xy->y == key2){
            del.xy = res->isw->xy;
            del.info = res->isw->info;
            res->isw->info = NULL;
            res->isw->xy = NULL;
            res->isw = NULL;
        }
        else if (res->ise->xy->x == key1 && res->ise->xy->y == key2){
            del.xy = res->ise->xy;
            del.info = res->ise->info;
            res->ise->info = NULL;
            res->ise->xy = NULL;
            res->ise = NULL;
        }
        else if (res->inw->xy->x == key1 && res->inw->xy->y == key2){
            del.xy = res->inw->xy;
            del.info = res->inw->info;
            res->inw->info = NULL;
            res->inw->xy = NULL;
            res->inw = NULL;
        }else return NULL;
    }
    else if(res->ine != NULL && res->inw == NULL && res->isw != NULL && res->ise != NULL){
        if(res->isw->xy->x == key1 && res->isw->xy->y == key2){
            del.xy = res->isw->xy;
            del.info = res->isw->info;
            res->isw->info = NULL;
            res->isw->xy = NULL;
            res->isw = NULL;
        }
        else if (res->ise->xy->x == key1 && res->ise->xy->y == key2){
            del.xy = res->ise->xy;
            del.info = res->ise->info;
            res->ise->info = NULL;
            res->ise->xy = NULL;
            res->ise = NULL;
        }
        else if (res->ine->xy->x == key1 && res->ine->xy->y == key2){
            del.xy = res->ine->xy;
            del.info = res->ine->info;
            res->ine->info = NULL;
            res->ine->xy = NULL;
            res->ine = NULL;
        }else return NULL;
    }
    else if(res->ine != NULL && res->inw != NULL && res->isw == NULL && res->ise != NULL){
        if(res->ine->xy->x == key1 && res->ine->xy->y == key2){
            del.xy = res->ine->xy;
            del.info = res->ine->info;
            res->ine->info = NULL;
            res->ine->xy = NULL;
            res->ine = NULL;
        }
        else if (res->ise->xy->x == key1 && res->ise->xy->y == key2){
            del.xy = res->ise->xy;
            del.info = res->ise->info;
            res->ise->info = NULL;
            res->ise->xy = NULL;
            res->ise = NULL;
        }
        else if (res->inw->xy->x == key1 && res->inw->xy->y == key2){
            del.xy = res->inw->xy;
            del.info = res->inw->info;
            res->inw->info = NULL;
            res->inw->xy = NULL;
            res->inw = NULL;
        }else return NULL;
    }
    else if(res->ine != NULL && res->inw != NULL && res->isw != NULL && res->ise == NULL){
        if(res->isw->xy->x == key1 && res->isw->xy->y == key2){
            del.xy = res->isw->xy;
            del.info = res->isw->info;
            res->isw->info = NULL;
            res->isw->xy = NULL;
            res->isw = NULL;
        }
        else if (res->ine->xy->x == key1 && res->ine->xy->y == key2){
            del.xy = res->ine->xy;
            del.info = res->ine->info;
            res->ine->info = NULL;
            res->ine->xy = NULL;
            res->ine = NULL;
        }
        else if (res->inw->xy->x == key1 && res->inw->xy->y == key2){
            del.xy = res->inw->xy;
            del.info = res->inw->info;
            res->inw->info = NULL;
            res->inw->xy = NULL;
            res->inw = NULL;
        }else return NULL;
    }
    struct Item *del_1 = &del;
    return del_1;
}

void del_node(struct Node *res){
    if (res->xy->x > res->par->xy->x && res->xy->y > res->par->xy->y)
        res->par->ne = NULL;
    else if (res->xy->x < res->par->xy->x && res->xy->y > res->par->xy->y)
        res->par->nw = NULL;
    else if (res->xy->x < res->par->xy->x && res->xy->y < res->par->xy->y)
        res->par->sw = NULL;
    else if (res->xy->x > res->par->xy->x && res->xy->y < res->par->xy->y)
        res->par->se = NULL;
}

int D_Show(struct Tree* root){
    int level = 1;
    print_tree(root->root, level);
    return 1;
}
void print_tree(struct Node* tree, int level){
    if(tree){
        print_tree(tree->ne, level+1);
        if (tree->ne == NULL && tree->ine != NULL){
            for(int i = 0; i<=level; i++)
                printf("      ");
            printf("NE x: %d, y: %d, info: %s\n" ,tree->ine->xy->x, tree->ine->xy->y, tree->ine->info);}

        print_tree(tree->nw, level+1);
        if(tree->nw == NULL && tree->inw != NULL){
            for(int i = 0; i<=level; i++)
                printf("      ");
            printf("NW x: %d, y: %d, info: %s\n" ,tree->inw->xy->x, tree->inw->xy->y, tree->inw->info);}
        for(int i = 0; i<level; i++)
            printf("      ");
        printf("node: %d, %d\n", tree->xy->x, tree->xy->y);
        print_tree(tree->sw, level+1);
        if(tree->sw == NULL && tree->isw != NULL){
            for(int i = 0; i<=level; i++)
                printf("      ");
            printf("SW x: %d, y: %d, info: %s\n" ,tree->isw->xy->x, tree->isw->xy->y, tree->isw->info);}
        print_tree(tree->se, level+1);
        if(tree->se == NULL && tree->ise != NULL){
            for(int i = 0; i<=level; i++)
                printf("      ");
            printf("SE x: %d, y: %d, info: %s\n" ,tree->ise->xy->x, tree->ise->xy->y, tree->ise->info);}
    }
}

int D_File(struct Tree* root_tree){
    FILE *fp;
    char key_char[10];
    if ((fp = fopen("C:\\Users\\dimak\\CLionProjects\\Labs_2sem\\Lab4\\Add.txt", "r")) == NULL)
    {
        printf("???? ?????????????? ?????????????? ????????");
        getchar();
        return 0;
    }

    while (key_char) {
        int key, rc;
        int n=0, i=0;
        char inform_1[10];
        char *inform;
        struct Node *tree_new = (struct Node *) calloc(1, sizeof(struct Node));

        if ( NULL != fgets ( key_char, 10, fp ) ) {
            key = atoi(key_char);
            if (key == 0)
                return 0;
        }else
            return 1;

        if ( NULL != fgets ( inform_1, 100, fp ) ) {
            inform = inform_1;
            char *pos = strrchr(inform, '\n');
            if (pos)
                inform[pos-inform] = 0;

            if (inform == NULL) {
                return 0; //EOF
            }
        }else
            return 1;




}}

int D_FindTime(struct Tree* root_tree){
//    int rc_find;
//    while (rc_find = dialog(msgs_find, NMsgs_Find)){

    int key1, key2, rc, n;

    printf("Enter the 1 key: ");
    n = getInt(&key1);
    if (n == 0)
        return 0;

    scanf("%*c");

    printf("Enter the 2 key: ");
    n = getInt(&key2);
    if (n == 0)
        return 0;

    scanf("%*c");
    clock_t begin = clock();
    struct Node *ptr = root_tree->root;

    struct Node *tree_new = find_recurs(ptr, key1, key2);
    if (tree_new == NULL)
        rc = 6;
    else{
        //printf("information:\"%s\" %d\t %d ", tree_new->info, key1, key2);
        rc = 1;}
    printf("%s:\n%d\t %d\n", errmsgs[rc], key1, key2);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time of work: %lf", time_spent);
    // }

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
struct Tree *tree_new(){
    struct Tree* tree_ptr = (struct Tree*) calloc (1, sizeof(struct Tree));

    return tree_ptr;
}
