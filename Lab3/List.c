#include "Lab3_func.h"
#ifdef PEREMEH
const char *errmsgs[] = {"Ok", "Duplicate key", "Table overflow"};



int D_Add(struct Table *ptab)
{
    int k, rc, n;
    char *info = NULL;
    printf("Enter key: -->");
    n = getInt(&k);

    if(n == 0)
        return 0;
    printf("Enter info:\n");
    info = getStr();
    if (info == NULL)
        return 0;
    rc = insert(ptab, k, info);
    free(info);
    printf("%s: %d\n", errmsgs[rc], k);
    return 1;
}
// vstavka v tablicy
int insert(struct Table *ptab, int k, char *str){
    if(find(*ptab, k) >= 0)
        return 1;
    if(ptab->msize1 >= ptab->csize1)
        return 2;
    ptab->ks1[ptab->msize1].key = k;
    ptab->ks1[ptab->msize1].node->info = str;
    ++(ptab->msize1);
    return 0;
}



int D_Find(struct Table *ptab)
{
    char *info = NULL;
    int k, n, keys, vers;
    puts("Enter key: -->");
    n = getInt(&k);
    if(n == 0)
        return 0;
    puts("Enter vers: -->");
    n = getInt(&vers);
    if(n == 0)
        return 0;

    keys = findInfoKey(*ptab, k);
    info = findInfoVers(*ptab, vers, keys);


    if(info){
        printf("key = %d, version = %d, info = \"%s\"\n", k, vers, info);
        free(info);
    }
    else
        printf("Item %d was not found\n", k);
    return 1;
}
//поиск по ключу
int findInfoKey(struct Table ptab, int k)
{
    int i, m;
    i=0;
    m=ptab.csize1-1;
    while (i<=m){
        int j= 5;/* середина таблицы*/
        if (k == ptab.ks1->key)
            return ptab.ks1->key;
        if (k < ptab.ks1->key)
            m = j-1;
        else
            i = j+1;
    }
    if (i>m)
        return -1;
}
//поиск по версии
char * findInfoVers(struct Table ptab, int vers, int keys){

    while (ptab.ks1[keys].node->next != NULL){
        if (vers ==ptab.ks1[keys].node->release)
            return ptab.ks1[keys].node->info;
        else
            ptab.ks1[keys].node = ptab.ks1[keys].node->next;
    }
    if(ptab.ks1[keys].node == NULL)
        printf("WARNIING");
}


int D_Delete(struct Table *ptab){
    char *info = NULL;
    int k, n, keys, vers;
    puts("Enter key: -->");
    n = getInt(&k);
    if(n == 0)
        return 0;
    puts("Enter vers: -->");
    n = getInt(&vers);
    if(n == 0)
        return 0;

    keys = findInfoKey(*ptab, k);
    info = findInfoVers(*ptab, vers, keys);

    if (keys < 0)
        printf(errmsgs[2]);
    if (ptab->ks1->node->next ==NULL)//если один элемент без версий
        for(; keys < ptab->csize1; keys++){
            ptab->ks1[keys] = ptab->ks1[keys+1];
        }
    else{//иначе удаляем одну из версий
        if (ptab->ks1->node->next->release != vers)
            ptab->ks1->node = ptab->ks1->node->next;
        else
            ptab->ks1->node = ptab->ks1->node->next->next;
    }
}


int D_Show(struct Table *ptab){

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

char *getStr() {
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n = 0;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        } else if (n > 0) {
            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
    }

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
#endif