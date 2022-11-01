#include <stdio.h>
#include <malloc.h>
#include "Lab1_func.h"


int matrix_change(Matrix *a) {
    int perem1, perem2;

    printf("Changing...\n");

    for (int i = 0; i < a->lines; ++i)//Cicle for lines
    {
        perem1 = search_first_element(a, i);
        perem2 = search_second_element(a, i);

        swap(a, perem1, perem2, i);
    }
}

void swap(Matrix *a, int perem1,int perem2, int i){
    double k;
    k = a->matr[i].a[perem1+1];
    a->matr[i].a[perem1+1] = a->matr[i].a[a->matr[i].n - perem2-1];
    a->matr[i].a[a->matr[i].n - perem2-1] = k;
}

double search_first_element(Matrix *a, int i) {
    int k = a->matr[i].n;
    for (int j = 0; j < k; ++j)//Cicle for find first element
    {
        if (a->matr[i].a[j] < a->matr[i].a[j+1]) {//first element (i), so than we find:
            printf("First search...\n%lf\n", a->matr[i].a[j+1]);
            return j;
        }

    }
}

double search_second_element(Matrix *a, int i) {
    int k = a->matr[i].n;
    for (int j = 0; j < k; ++j)//Cicle for find first element
    {
        if (a->matr[i].a[k - j -2] > a->matr[i].a[k -j-1]) {//first element (i), so than we find:
            printf("Second search...\n%lf\n", a->matr[i].a[k - j-1]);
            return j;
        }
    }
}

int input(Matrix *rm){
    const char *pr = "";
    int m;
    int i, j;
    double *p;
    do{
        printf("%s\n", pr);
        printf("Enter number of lined: -->");
        pr = "You are wrong; repeat, please!";
        if(getInt(&m) == 0)
            return 0;
    }while (m<1);
    rm->lines = m;
    rm->matr = (Line*)calloc(m, sizeof(Line));

    for (i=0; i <rm->lines; ++i){
        pr = "";
        do{
            printf("%s\n", pr);
            printf("Enter number of items in line %d: -->", i+1);
            pr = "You are wrong; repeat, please!";
            if (getInt(&m)==0){
                rm->lines = i;
                erase(rm);
                return 0;
            }
        }while (m < 1);
        rm->matr[i].n = m;

        p= (double *)malloc(sizeof(double )* m);
        rm->matr[i].a = p;

        printf("Enter items for matrix line #%d:\n", i+1);
        for (j=0; j<m; ++j, ++p)
        if (getDouble(p) == 0){
            rm->lines = i+1;
            erase(rm);
            return 0;
        }
    }
    return 1;
}

int getInt(int *a){
    int n;
    do{
        n=scanf("%d", a, sizeof(int));
        if (n<0)
            return 1;
        if (n==0){
            printf("%s\n", "Error! Repeat input");
            scanf("%*c", 0);
        }
    } while (n==0);
    return 1;
}

int getDouble(double *a){
    int n;
    do{
        n=scanf("%lf", a, sizeof(double ));
        if (n<0)
            return 0;
        if (n==0){
            printf("%s\n", "Error! Repeat input");
            scanf("%*c", 0);
        }
    } while (n==0);
    return 1;
}

void erase(Matrix *a){
    int i;
    for(i=0; i<a->lines; ++i)
        free(a->matr[i].a);
    free(a->matr);
    a->lines = 0;
    a->matr = NULL;
}

void output(const char *msg, Matrix a){
    int i, j;
    double *p;
    printf("%s:\n", msg);
    for (i=0; i<a.lines; ++i){
        p = a.matr[i].a;
        for (j=0; j<a.matr[i].n; ++j, ++p)
            printf("%lf ", *p);
        printf("\n");
    }
}