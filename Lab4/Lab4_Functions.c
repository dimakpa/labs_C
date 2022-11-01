#include "Lab4_Functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


const char *errmsgs[] = {"Error", "Ok", "Add to left", "Add to right", "Add to root", "Duplicate key", "Element not founded", "Element deleted", "Koren"};

const char *msgs_find[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show", "5. Add with file"};
const int NMsgs_Find = sizeof(msgs_find) / sizeof(msgs_find[0]);
int (*fptr_find[])(struct Tree *) = {NULL, D_Add, D_Find, D_Delete, D_Show, D_File};

int D_Add(struct Tree* root_tree)
{
    int key, rc, n;
    char *inform;
    struct Node *tree_new = (struct Node*) calloc(1, sizeof(struct Node));

    printf("Enter the 1 key: ");
    n = getInt(&key);
    if (n == 0)
        return 0;

    scanf("%*c");

    printf("Enter the string of info: ");
    inform = get_str();
    if (inform == NULL) {
        return 0; //EOF
    }

    tree_new->key = key;
    tree_new->info = calloc (1, sizeof(char));
    strcpy(tree_new->info, inform);


    if (root_tree->root == NULL)
    {
        tree_new->right = NULL;
        tree_new->left = NULL;
        tree_new->par = NULL;
        root_tree->root = tree_new;
        rc = 4;
    }else {

        struct Node *ptr = root_tree->root;
        struct Node *par = NULL;
        while(ptr != NULL){
            par = ptr;
            if(tree_new->key < ptr->key)
                ptr = ptr->left;
            else
                ptr = ptr->right;
        }
        if(tree_new->key < par->key){
            par->left = tree_new;
            strcpy(tree_new->info, inform);
            tree_new->par = par;
            tree_new->left = NULL;
            tree_new->right = NULL;
            rc = 2;
        }
        else if(tree_new->key > par->key){
            par->right = tree_new;
            strcpy(tree_new->info, inform);
            tree_new->par = par;
            tree_new->left = NULL;
            tree_new->right = NULL;
            rc = 3;
        } else
            rc = 0;

        }

    printf("%s:\n%d\n", errmsgs[rc], key);


    return 1;
}

int D_Find(struct Tree* root)
{
    int key, rc, n;

    printf("Enter the 1 key: ");
    n = getInt(&key);
    if (n == 0)
        return 0;

    scanf("%*c");

    struct Node *ptr = root->root;

    struct Node *tree_new = find_recurs(ptr, key);
    if (tree_new == NULL)
        rc = 6;
    else{
        printf("information:\"%s\" %d ", tree_new->info, key);
        rc = 1;}
    printf("%s:\n%d\n", errmsgs[rc], key);
    return 1;
}

struct Node *find_recurs(struct Node *ptr,int key){

    struct Node *res;
    if (ptr == NULL)
        return NULL;
    else{
        if(ptr->key == key)
            res = ptr;
        else if(key < ptr->key){
            if (ptr->left == NULL)
                return res = NULL;
            res = find_recurs(ptr->left, key);
            }
        else{
            if (ptr->right == NULL)
                return NULL;
            res = find_recurs(ptr->right, key);
        }
    }
    return res;
}


int D_Delete(struct Tree* root){

    int key, rc, n;

    printf("Enter the 1 key: ");
    n = getInt(&key);
    if (n == 0)
        return 0;

    scanf("%*c");

    struct Node *ptr = root->root;

    struct Node *tree_delet = delete_recurs(root, ptr, key);


    if (tree_delet == NULL)
        rc = 6;
    else{
        printf("information:\"%s\" %d ", tree_delet->info, tree_delet->key);
        rc = 7;}
    printf("%s:\n%d\n", errmsgs[rc], key);
    return 1;
}
struct Node *delete_recurs(struct Tree *root, struct Node *ptr,int key){


    struct Node *res = find_recurs(ptr, key);
    if (ptr == NULL)
        return NULL;

    struct Node *del;
    struct Node *p;
    struct Node *param = res->par;

    if (res->right == NULL && res->left == NULL)
        del = res;
    else if(res->right != NULL && res->left == NULL)
        del = res->right;
    else if(res->right == NULL && res->left != NULL)
        del = res->left;
    else{
        int min_key = find_min_right_key(root, res->right);
        del = delete_recurs(root, ptr, min_key);

        strcpy(res->info, del->info);
        res->key = del->key;
        return del;
    }


    if (del->left != NULL)
        p = del->left;
    else
        p = del->right;
    struct Node *par = del->par;

    if (p != NULL)
        p->par = par;
    if (par == NULL)
        root->root = p;
    else if (par->left == del)
        par->left = p;
    else
        par->right = p;

    if (res != del){
        res->key = del->key;
        strcpy(res->info, del->info);
        res->right = del->right;
        res->left = del->left;
        res->par = del->par;
    }
    return del;
}

int find_min_right_key(struct Tree* root, struct Node* res){
    struct Node *ptr = res;
    while (ptr->left !=NULL){
        ptr = ptr->left;
    }
    return ptr->key;
}

int D_Show(struct Tree* root){
    int level = 0;
    print_tree(root->root, level);
    return 1;
}
void print_tree(struct Node* tree, int level){
    if(tree){
        print_tree(tree->right, level+1);
        for(int i = 0; i<level; i++)
            printf("      ");
        printf("key: %d, info: %s\n", tree->key, tree->info);
        print_tree(tree->left, level+1);
    }
}

int D_File(struct Tree* root_tree){
    FILE *fp;
    char key_char[10];
    if ((fp = fopen("C:\\Users\\dimak\\CLionProjects\\Labs_2sem\\Lab4\\Add.txt", "r")) == NULL)
    {
        printf("Не удалось открыть файл");
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



        tree_new->key = key;
        tree_new->info = calloc(1, sizeof(char));
        strcpy(tree_new->info, inform);


        if (root_tree->root == NULL) {
            tree_new->right = NULL;
            tree_new->left = NULL;
            tree_new->par = NULL;
            root_tree->root = tree_new;
            rc = 4;
        } else {

            struct Node *ptr = root_tree->root;
            struct Node *par = NULL;
            while (ptr != NULL) {
                par = ptr;
                if (tree_new->key < ptr->key)
                    ptr = ptr->left;
                else
                    ptr = ptr->right;
            }
            if (tree_new->key < par->key) {
                par->left = tree_new;
                strcpy(tree_new->info, inform);
                tree_new->par = par;
                tree_new->left = NULL;
                tree_new->right = NULL;
                rc = 2;
            } else if (tree_new->key > par->key) {
                par->right = tree_new;
                strcpy(tree_new->info, inform);
                tree_new->par = par;
                tree_new->left = NULL;
                tree_new->right = NULL;
                rc = 3;
            } else
                rc = 0;

        }

        printf("%s:\n%d\n", errmsgs[rc], key);
    }
    fclose(fp);
    getchar();


    return 1;
}

int D_FindTime(struct Tree* root_tree){
//    int rc_find;
//    while (rc_find = dialog(msgs_find, NMsgs_Find)){

    int key, rc, n;

    printf("Enter the 1 key: ");
    n = getInt(&key);
    if (n == 0)
        return 0;

    scanf("%*c");
    clock_t begin = clock();
    struct Node *ptr = root_tree->root;

    struct Node *tree_new = find_recurs(ptr, key);
    if (tree_new == NULL)
        rc = 6;
    else{
        printf("information:\"%s\" %d ", tree_new->info, key);
        rc = 1;}
    printf("%s:\n%d\n", errmsgs[rc], key);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time of work: %lf", time_spent);
   // }

    return 1;
}

int D_Show_preOrder(struct Tree* root_tree){
    print_preoder_tree(root_tree->root);
    return 1;
}

void print_preoder_tree(struct Node* root){
    if (root) {
        printf("key: %d\t info: %s\n", root->key, root->info);
        print_preoder_tree(root->left);
        print_preoder_tree(root->right);
    }
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
