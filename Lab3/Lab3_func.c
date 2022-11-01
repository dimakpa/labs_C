#include <stdio.h>
#include "Lab3_func.h"
#include <stdlib.h>
#include <string.h>

#define KS1_MAXSIZE 5
#define KS2_MAXSIZE 5
#define Length2 4



///создавать новую таблицу


const char *errmsgs[] = {"Ok", "Duplicate key", "Table overflow", "Element deleted"};

const char *msgs_find[] = {"0. Quite", "1. Find element with key1", "2. Find element with key2", "3. Find with 2 keys"};
const int NMsgs_Find = sizeof(msgs_find) / sizeof(msgs_find[0]);
int (*fptr_find[])(struct Table *) = {NULL, Find_With_Key1, Find_With_Key2, Find_With_Two_Keys};

const char *msgs_del[] = {"0. Quite", "1. Delete with key1", "2. Delete with key2", "3. Delete with 2 keys"};
const int NMsgs_Del = sizeof(msgs_find) / sizeof(msgs_find[0]);
int (*fptr_del[])(struct Table *) = {NULL, Del_With_Key1, Del_With_Key2, Delete_With_Both_Keys};



int D_Add(struct Table *ptab)
{
    int k1, rc, n;


    printf("Enter the 1 key: ");
    n = getInt(&k1);
    if (n == 0)
        return 0;

    char k2[Lengthkey + 1] = { 0 };
    get_str();
    printf("Enter the 2 key: ");
    n = scanf("%9[^\n]", k2, Lengthkey + 1);
    if (n < 0)
        return 0;
    if (n == 0)
        printf("Incorrect input, try again\n");

    scanf("%*c");

    struct Item item;
    item.info = calloc (1, sizeof(char));
    item.info = NULL;
    item.key1 = k1;
    item.key2 = k2;

    printf("Enter the string of info: ");
    item.info = get_str();
    if (item.info == NULL) {
        return 0; //EOF
    }

    rc = insert (ptab, k1, k2, &item); //insert the element in table

    free(item.info);
    item.info = NULL;
    printf("%s:\n%d\n%s\n", errmsgs[rc], k1, k2);


    return 1;
}

int D_Find(struct Table *ptab)
{
    int rc_find;
    while (rc_find = dialog(msgs_find, NMsgs_Find))
        if(!fptr_find[rc_find](ptab))
            break;
    return 1;
}
int Find_With_Key1(struct Table* ptab) {//добавить релизы
    struct KeySpace1* status = NULL;

    int key1, rel, n;
    printf("Enter the 1 key: ");
    n = getInt(&key1);
    if (n == 0)
        return 0;

    printf("Enter the release! and if you want all elements put 0: ");
    n = getInt(&rel);
    if (n == 0)
        return 0;

    int i = find1(ptab, key1);
    if (rel == 0){
        if (ptab->ks1[i].node->item == NULL) {
            printf("NULL\n");
        }
        else {

            printf("key1 = %d, rel = %d, info = \"%s\"\t--->\t", ptab->ks1[i].keys1, ptab->ks1[i].node->release,ptab->ks1[i].node->item->info );

            struct Node1 *new_ks1 = ptab->ks1[i].node->next;
            while (new_ks1 != NULL) {

                printf("rel = %d, info = \"%s\"\t--->\t", new_ks1->release, new_ks1->item->info);

                new_ks1 = new_ks1->next;
            }
            return 0;
        }
    }

    status = find_and_copy_with_key1(ptab, key1, rel);
    if (status == NULL || status->node->item == NULL) {
        printf("Error! The table doesn't have such element of release\n");
        free(status);
        status=NULL;
        return 1;
    }

    struct KeySpace1* tail = status;
    printf("The elements with this key1:\n");

    while (tail->node != NULL) {
        printf("key1 = %d, key2 = \"%s\", release = %d, info = \"%s\"\t-->\t",
               tail->keys1,
               tail->node->item->key2,
               tail->node->release,
               tail->node->item->info);

        tail->node = tail->node->next;
    }
    return 1;
}
struct KeySpace1* find_and_copy_with_key1 (struct Table* ptab, int key1, int release) {

    if (find_key1(ptab, key1) == 0)
        return NULL;
    struct KeySpace1* ks1_el_ptr =  (struct KeySpace1*) calloc (1, sizeof(struct KeySpace1));
    struct Node1* ks1_el_ptr_node = (struct Node1*)calloc(1, sizeof(struct Node1));
    ks1_el_ptr->node = ks1_el_ptr_node;

    int i = 0, m = ptab->csize1 - 1;
    int j;
    while (i <= m) {
        j = (i + m) / 2;

        if (key1 == ptab->ks1[j].keys1)  {
            if(release != 0){
                if (ptab->ks1[j].node->item == NULL) {
                    return NULL;
                }
                if ( (ptab->ks1[j].node->item->key1 == key1) && (ptab->ks1[j].node->release == release) ) {
                    ks1_el_ptr->keys1 = ptab->ks1[j].node->item->key1;
                    ks1_el_ptr->node->release = ptab->ks1[j].node->release;
                    ks1_el_ptr->node->next = NULL;
                    ks1_el_ptr->node->item = (struct Item*) calloc (1, sizeof(struct Item));
                    ks1_el_ptr->node->item->key1 = ptab->ks1[j].node->item->key1;
                    ks1_el_ptr->node->release = ptab->ks1[j].node->release;

                    ks1_el_ptr->node->item->key2 = ptab->ks1[j].node->item->key2;

                    ks1_el_ptr->node->item->info =  calloc (1, sizeof(char));

                    ks1_el_ptr->node->item->info = (char*)calloc( 1, sizeof(char));
                    strcpy(ks1_el_ptr->node->item->info, ptab->ks1[j].node->item->info);


                    return ks1_el_ptr;
                }

                struct KeySpace1 el_ks_11 = ptab->ks1[j];
                struct Node1* el_ks_1 = el_ks_11.node->next;

                while (el_ks_1 != NULL) {
                    if ((el_ks_11.keys1 == key1) && (el_ks_1->release == release) ) {
                        ks1_el_ptr->keys1 = el_ks_11.keys1;
                        ks1_el_ptr->node->release = el_ks_1->release;
                        ks1_el_ptr->node->next = NULL;
                        ks1_el_ptr->node->item = (struct Item*) calloc (1, sizeof(struct Item));
                        ks1_el_ptr->node->item->key1 = el_ks_11.keys1;
                        ks1_el_ptr->node->release = el_ks_1->release;
                        ks1_el_ptr->node->item->key2 = (char*)calloc (1, sizeof(char));
                        strcpy(ks1_el_ptr->node->item->key2 , el_ks_1->item->key2);

                        ks1_el_ptr->node->item->info = ( calloc (1, sizeof(char)));

                        ks1_el_ptr->node->item->info = (char*)calloc( 1, sizeof(char));
                        strcpy(ks1_el_ptr->node->item->info, el_ks_1->item->info);


                        return ks1_el_ptr;
                    }
                    el_ks_1 = el_ks_1->next;
                }

                return ks1_el_ptr;
            }

            if (ptab->ks2[j].item == NULL) {
                return NULL;
            }
            if (ptab->ks1[j].node->item->key1 == key1) {

                ks1_el_ptr->keys1 = ptab->ks1[j].keys1;
                ks1_el_ptr->node->release = ptab->ks1[j].node->release;
                ks1_el_ptr->node->next = NULL;
                ks1_el_ptr->node->item = (struct Item*) calloc (1, sizeof(struct Item));
                ks1_el_ptr->node->item->key1 = ptab->ks1[j].node->item->key1;
                ks1_el_ptr->node->release = ptab->ks1[j].node->release;

                ks1_el_ptr->node->item->key2 = ptab->ks1[j].node->item->key2;

                ks1_el_ptr->node->item->info =  calloc (1, sizeof(char));

                ks1_el_ptr->node->item->info = (char*)calloc(strlen(ptab->ks2[j].item->info) + 1, sizeof(char));
                strcpy(ks1_el_ptr->node->item->info, ptab->ks2[j].item->info);

            }

            struct KeySpace1 el_ks_22 = ptab->ks1[j];
            struct Node1* el_ks_2 = el_ks_22.node->next;
            struct KeySpace1* el_ks_2_new = NULL;
            struct KeySpace1* ks2_el_ptr_mov = ks1_el_ptr;

            while (el_ks_2 != NULL) {

                if (el_ks_22.keys1 == key1) {
                    el_ks_2_new = (struct KeySpace1*)calloc(1,sizeof(struct KeySpace1));

                    el_ks_2_new->keys1 = el_ks_22.keys1;
                    el_ks_2_new->node->release = el_ks_2->release;
                    el_ks_2_new->node->next = NULL;
                    el_ks_2_new->node->item = (struct Item*) calloc (1, sizeof(struct Item));
                    el_ks_2_new->node->item->key1 = el_ks_22.keys1;
                    el_ks_2_new->node->release = el_ks_2->release;

                    el_ks_2_new->node->item->key2 = el_ks_2->item->key2;

                    el_ks_2_new->node->item->info =  calloc (1, sizeof(char));

                    el_ks_2_new->node->item->info = (char*)calloc(1, sizeof(char));
                    strcpy(el_ks_2_new->node->item->info, el_ks_2->item->info);


                    if (ks1_el_ptr->node->item == NULL) {
                        ks2_el_ptr_mov = el_ks_2_new;
                        ks1_el_ptr = el_ks_2_new;
                    }
                    else {
                        ks2_el_ptr_mov->node->next = el_ks_2_new->node;
                        ks2_el_ptr_mov->node = ks2_el_ptr_mov->node->next;
                    }

                }

                el_ks_2 = el_ks_2->next;
            }

            return ks1_el_ptr;



        }

        if (key1 < ptab->ks1[j].keys1)
            m = j - 1;
        else {
            i = j + 1;
        }
    }
    return ks1_el_ptr;
}
int Find_With_Key2(struct Table* ptab) {
    int n,  release;

    char key2[Lengthkey + 1] = { 0 };
    get_str();
    printf("Enter the 2 key: ");
    n = scanf("%9[^\n]", key2, Lengthkey + 1);
    if (n < 0)
        return 0;
    if (n == 0)
        printf("Incorrect input, try again\n");

    printf("\nEnter a release of an element with this key2 you want to find (enter 0 if you want to find all elements with this key2: ");
    n = getInt(&release);
    if (n == 0)
        return 0;


    struct KeySpace2* status  = find_and_copy_with_key2(ptab, key2, release);
    if (status == NULL || status->item == NULL) {
        printf("Error! The table doesn't have such element of release\n");
        free(status);
        status=NULL;
        return 1;
    }
    struct KeySpace2* tail = status;
    printf("The elements with this key2:\n");

    while (tail != NULL) {
        printf("key1 = %d, key2 = \"%s\", release = %d, info = \"%s\"\t-->\t",
               tail->item->key1,
               tail->item->key2,
               tail->release,
               tail->item->info);

        tail = tail->next;
    }

    struct KeySpace2* ptr = status;
    struct KeySpace2* ptr_prev = NULL;
    while(ptr != NULL) {
        ptr_prev = ptr;
        ptr = ptr->next;

        ptr_prev->item->info = NULL;

        ptr_prev->item->key2 = NULL;
        free(ptr_prev->item);                     ptr_prev->item = NULL;
        ptr_prev->keys2 = NULL;
        free(ptr_prev);                           ptr_prev = NULL;
    }

    return 1;
}
struct KeySpace2* find_and_copy_with_key2(struct Table* ptab, char* key2, int release) {

    if (find_key2(ptab,key2) == 0)
        return NULL;

    if (release < 0) {
        return NULL;
    }

    struct KeySpace2* ks2_el_ptr =  (struct KeySpace2*) calloc (1, sizeof(struct KeySpace2));

    if (release != 0) {
        int h = hesh(key2);

        if (ptab->ks2[h].item == NULL) {
            return NULL;
        }
        if ( (strcmp(ptab->ks2[h].item->key2, key2) == 0) && (ptab->ks2[h].release == release) ) {
            ks2_el_ptr->keys2 = ptab->ks2[h].item->key2;
            ks2_el_ptr->release = ptab->ks2[h].release;
            ks2_el_ptr->next = NULL;
            ks2_el_ptr->item = (struct Item*) calloc (1, sizeof(struct Item));
            ks2_el_ptr->item->key2 = ptab->ks2[h].item->key2;
            ks2_el_ptr->release = ptab->ks2[h].release;

            ks2_el_ptr->item->key1 = ptab->ks2[h].item->key1;

            ks2_el_ptr->item->info =  calloc (1, sizeof(char));

            ks2_el_ptr->item->info = (char*)calloc( 1, sizeof(char));
            strcpy(ks2_el_ptr->item->info, ptab->ks2[h].item->info);


            return ks2_el_ptr;
        }

        struct KeySpace2* el_ks_2 = ptab->ks2[h].next;

        while (el_ks_2 != NULL) {
            if (( strcmp(el_ks_2->keys2 ,key2)==0) && (el_ks_2->release == release) ) {
                ks2_el_ptr->keys2 = (char *)calloc(1, sizeof(char ));
                strcpy(ks2_el_ptr->keys2 , el_ks_2->keys2);
                ks2_el_ptr->release = el_ks_2->release;
                ks2_el_ptr->next = NULL;
                ks2_el_ptr->item = (struct Item*) calloc (1, sizeof(struct Item));
                ks2_el_ptr->item->key2 = (char *)calloc(1, sizeof(char ));
                strcpy(ks2_el_ptr->item->key2 , el_ks_2->keys2);
                ks2_el_ptr->release = el_ks_2->release;

                strcpy(ks2_el_ptr->item->key2 , el_ks_2->item->key2);

                ks2_el_ptr->item->info = ( calloc (1, sizeof(char)));

                ks2_el_ptr->item->info = (char*)calloc( 1, sizeof(char));
                strcpy(ks2_el_ptr->item->info, el_ks_2->item->info);


                return ks2_el_ptr;
            }
            el_ks_2 = el_ks_2->next;
        }

        return ks2_el_ptr;
    }

    int h = hesh(key2);

    if (ptab->ks2[h].item == NULL) {
        return NULL;
    }
    if (strcmp(ptab->ks2[h].item->key2, key2) == 0) {
        ks2_el_ptr->keys2 = (char*)calloc(1, sizeof(char ));
        strcpy(ks2_el_ptr->keys2 , ptab->ks2[h].keys2);
        ks2_el_ptr->release = ptab->ks2[h].release;
        ks2_el_ptr->next = NULL;
        ks2_el_ptr->item = (struct Item*) calloc (1, sizeof(struct Item));
        ks2_el_ptr->item->key2 = ptab->ks2[h].item->key2;
        ks2_el_ptr->release = ptab->ks2[h].release;

        ks2_el_ptr->item->key1 = ptab->ks2[h].item->key1;

        ks2_el_ptr->item->info =  calloc (1, sizeof(char));

        ks2_el_ptr->item->info = (char*)calloc(strlen(ptab->ks2[h].item->info) + 1, sizeof(char));
        strcpy(ks2_el_ptr->item->info, ptab->ks2[h].item->info);

    }

    struct KeySpace2* el_ks_2 = ptab->ks2[h].next;
    struct KeySpace2* el_ks_2_new = NULL;
    struct KeySpace2* ks2_el_ptr_mov = ks2_el_ptr;

    while (el_ks_2 != NULL) {

        if (strcmp(el_ks_2->keys2 ,key2)==0) {
            el_ks_2_new = (struct KeySpace2*)calloc(1,sizeof(struct KeySpace2));
            el_ks_2_new->keys2 = (char*)calloc(1, sizeof(char));
            strcpy(el_ks_2_new->keys2, el_ks_2->keys2);
            el_ks_2_new->release = el_ks_2->release;
            el_ks_2_new->next = NULL;
            el_ks_2_new->item = (struct Item*) calloc (1, sizeof(struct Item));
            el_ks_2_new->item->key2 = (char*)calloc(1, sizeof(char));
            strcpy(el_ks_2_new->item->key2, el_ks_2->keys2);
            el_ks_2_new->release = el_ks_2->release;

            el_ks_2_new->item->key1 = el_ks_2->item->key1;

            el_ks_2_new->item->info =  calloc (1, sizeof(char));

            el_ks_2_new->item->info = (char*)calloc(1, sizeof(char));
            strcpy(el_ks_2_new->item->info, el_ks_2->item->info);


            if (ks2_el_ptr->item == NULL) {
                ks2_el_ptr_mov = el_ks_2_new;
                ks2_el_ptr = el_ks_2_new;
            }
            else {
                ks2_el_ptr_mov->next = el_ks_2_new;
                ks2_el_ptr_mov = ks2_el_ptr_mov->next;
            }

        }

        el_ks_2 = el_ks_2->next;
    }

    return ks2_el_ptr;

}
int Find_With_Two_Keys(struct Table *ptab){

    int key1, n;
    printf("Enter the 1 key: ");
    n = getInt(&key1);
    if (n == 0)
        return 0;

    char key2[Lengthkey + 1] = { 0 };
    get_str();
    printf("Enter the 2 key: ");
    n = scanf("%9[^\n]", key2, Lengthkey + 1);
    if (n < 0)
        return 0;
    if (n == 0)
        printf("Incorrect input, try again\n");

    int i = find1(ptab, key1);//строка в которой ключ 1
    if (ptab->ks1[i].node->item == NULL) {
        printf("NULL\n");
    }else if(strcmp(ptab->ks1[i].node->item->key2, key2)==0)
        printf("key1 = %d, key2 = \"%s\", info = \"%s\"", key1, ptab->ks1[i].node->item->key2, ptab->ks1[i].node->item->info);
    else{
        struct Node1 *new_ks1 = ptab->ks1[i].node->next;
        while (strcmp(new_ks1->item->key2, key2) != 0)
            new_ks1 = new_ks1->next;
        printf("key1 = %d, key2 = \"%s\", info = \"%s\"", key1, new_ks1->item->key2, new_ks1->item->info);
    }

    return 1;
}

int D_Delete(struct Table *ptab){
    int rc_del;
    while (rc_del = dialog(msgs_del, NMsgs_Del))
        if(!fptr_del[rc_del](ptab))
            break;
    return 1;
}

int Del_With_Key2(struct Table* ptab){
    int n,  release;

    char key2[Lengthkey + 1] = { 0 };
    get_str();
    printf("Enter the 2 key: ");
    n = scanf("%9[^\n]", key2, Lengthkey + 1);
    if (n < 0)
        return 0;
    if (n == 0)
        printf("Incorrect input, try again\n");

    printf("\nEnter a release of an element with this key2 you want to delete (enter 0 if you want to delete all elements with this key2: ");
    n = getInt(&release);
    if (n == 0)
        return 0;
    if (release == 0)
        delete_with_key2(ptab, key2);
    else
        find_and_delete_rel_ks2(ptab, key2, release);
    return 1;
}
int delete_with_key2 (struct Table* table_ptr, char* key2) {
    int i = hesh(key2);
    struct KeySpace2* ks2 = table_ptr->ks2[i].next;
    if (strcmp(table_ptr->ks2[i].keys2, key2)==0)
        delete_with_two_keys(table_ptr, table_ptr->ks2[i].item->key1, table_ptr->ks2[i].item->key2);

    while (ks2 != NULL) {
        if(strcmp(ks2->keys2, key2) == 0)
            delete_with_two_keys(table_ptr, ks2->item->key1, ks2->item->key2);
        else
            ks2 = ks2->next;
    };
    return 1;
}
int find_and_delete_rel_ks2(struct Table* ptab,char* key2,int release){
    if (find_key2(ptab, key2) == 0)
        return -1;
    int g = hesh(key2);
    struct KeySpace2* ptr = ptab->ks2[g].next;

    while (ptr->release != release && strcmp(ptr->keys2, key2) != 0){
        ptr = ptr->next;
    }
    delete_with_two_keys(ptab, ptr->item->key1, ptr->item->key2);
    return 1;
}

int Del_With_Key1(struct Table* ptab){
    struct KeySpace1* status = NULL;
    int n, k1, rel;

    printf("Enter the 1 key: ");
    n = getInt(&k1);
    if (n == 0)
        return 0;

    printf("Enter the release! and if you want all elements put 0: ");
    n = getInt(&rel);
    if (n == 0)
        return 0;



    int h = find1(ptab, k1);
    if (h == -1) {
        printf("Error! No element with this key1\n");
        return 1;
    }

    if (rel == 0)
        delete_with_key1(ptab, k1);
    else{
        find_and_delete_rel_ks1(ptab, k1, rel);
    }



    return 1;
}
int delete_with_key1 (struct Table* table_ptr, int key1) {
    int i = find1(table_ptr, key1);
    do{
        delete_with_two_keys(table_ptr, table_ptr->ks1[i].keys1, table_ptr->ks1[i].node->item->key2);
    }while (table_ptr->ks1[i].node->item != NULL);
    return 1;
}
int find_and_delete_rel_ks1(struct Table* ptab, int key1, int release){
    if (find1(ptab, key1) == -1)
        return -1;
    int g = find1(ptab, key1);
    struct Node1* ptr = ptab->ks1[g].node;

    while (ptr->release != release){
        ptr = ptr->next;
    }
    delete_with_two_keys(ptab, ptr->item->key1, ptr->item->key2);
    return 1;
}

int Delete_With_Both_Keys (struct Table* ptab) {
    printf("\nEnter the key1 and key2 to delete element:\n");
    int n, key1, status;

    printf("\nEnter key1: ");
    n = getInt(&key1);
    if (n == 0) {
        return 0; //EOF
    }
    get_str();
    char* key2 = NULL;
    printf("\nEnter key2: ");
    key2 = get_str();


    status = delete_with_two_keys(ptab, key1, key2);
    if (status == 0) {
        printf("Error! Element not found\n");
    }
    else {
        printf("The element with key1 = %d key2 = \"%s\" was successfully deleted", key1, key2);
    }
    free(key2);     key2 = NULL;
    return 1;
}
int delete_with_two_keys (struct Table* table_ptr, int key1, char* key2) {

    int i = find1(table_ptr, key1);

    if  ( (strcmp(table_ptr->ks1[i].node->item->key2, key2)==0) && (table_ptr->ks1[i].keys1 == key1)  ) {
        table_ptr->ks1[i].node->item = NULL;

        if ((table_ptr->ks1[i].node->next != NULL) ) {
            table_ptr->ks1[i].node = table_ptr->ks1[i].node->next;
        }
        else if(table_ptr->ks1[i].node->next == NULL && table_ptr->ks1[i].node->item == NULL){
            table_ptr->ks1[i].node->item = NULL;


            for (int k = i + 1; k < table_ptr->msize1; ++k) {
                table_ptr->ks1[k-1] = table_ptr->ks1[k];
            }
            --table_ptr->csize1;
            table_ptr->ks1[table_ptr->msize1 - 1].node->item = NULL;
        }

    }else{
        struct Node1* ptr1 = table_ptr->ks1[i].node->next;
        struct Node1* ptr_prev1 = NULL;


        while (ptr1 != NULL) {
            ptr_prev1= ptr1;
            ptr1 = ptr1->next;
        }
        struct Node1* tail1 = ptr_prev1;

        ptr1 = table_ptr->ks1[i].node->next;
        ptr_prev1 = NULL;
        while ( (ptr1!=NULL) && (strcmp(ptr1->item->key2 , key2)< 0) && (ptr1->item->key1 != key1) ) {
            ptr_prev1 = ptr1;
            ptr1 = ptr1->next;
        }
        if (ptr1 == NULL) {
            return 0;
        }
        if (ptr1 == table_ptr->ks1[i].node->next) {
            table_ptr->ks1[i].node->next = ptr1->next;
        }
        if (ptr1 == tail1)
            tail1 = ptr_prev1;

        if (ptr_prev1 != NULL) {
            ptr_prev1->next = ptr1->next;
        }
//        free(ptr1->item->key2);                  ptr1->item->key2 = NULL;
//        free(ptr1->item->info);                  ptr1->item->info = NULL;
        //free(ptr1->item);
        ptr1->item = NULL;
        //free(ptr1);                              ptr1 = NULL;
    }






    int h = hesh(key2);

    if (table_ptr->ks2[h].item == NULL) {
        return 0;
    }

    if  ( (strcmp(table_ptr->ks2[h].item->key2, key2)==0) && (table_ptr->ks2[h].item->key1 == key1)  ) {
        free(table_ptr->ks2[h].item->key2);                table_ptr->ks2[h].item->key2 = NULL;
        //free(table_ptr->ks2[h].item->info);
        table_ptr->ks2[h].item->info = NULL;
        free(table_ptr->ks2[h].item);                      table_ptr->ks2[h].item = NULL;

        if (table_ptr->ks2[h].next != NULL && table_ptr->ks2[h].next->item != NULL) {
            table_ptr->ks2[h].keys2 = table_ptr->ks2[h].next->keys2;
            table_ptr->ks2[h].release = table_ptr->ks2[h].next->release;
            table_ptr->ks2[h].item = table_ptr->ks2[h].next->item;
            table_ptr->ks2[h].next = table_ptr->ks2[h].next->next;
        }
        return 1;
    }

    struct KeySpace2* ptr = table_ptr->ks2[h].next;
    struct KeySpace2* ptr_prev = NULL;


    while (ptr != NULL) {
        ptr_prev = ptr;
        ptr = ptr->next;
    }
    struct KeySpace2* tail = ptr_prev;

    ptr = table_ptr->ks2[h].next;
    ptr_prev = NULL;
    while ( (ptr!=NULL) && (strcmp(ptr->item->key2 , key2)< 0) && (ptr->item->key1 != key1) ) {
        ptr_prev = ptr;
        ptr = ptr->next;
    }
    if (ptr == NULL) {
        return 0;
    }
    if (ptr == table_ptr->ks2[h].next) {
        table_ptr->ks2[h].next = ptr->next;
    }
    if (ptr == tail)
        tail = ptr_prev;

    if (ptr_prev != NULL) {
        ptr_prev->next = ptr->next;
    }
    free(ptr->item->key2);                  ptr->item->key2 = NULL;
    //free(ptr->item->info);
    ptr->item->info = NULL;
    free(ptr->item);                        ptr->item = NULL;
    free(ptr);                              ptr = NULL;

    return 1;
}

int D_Show(struct Table *ptab){
    printf("\n-------KeySpace1-------\n");
    for (int i = 0; i < ptab->msize1; ++i) {
        printf("%d\t", i);
        if (ptab->ks1[i].node->item == NULL) {
            printf("NULL\n");
        }
        else {
            printf("key1 = %d, rel = %d, info = \"%s\"\t--->\t", ptab->ks1[i].keys1, ptab->ks1[i].node->release,ptab->ks1[i].node->item->info );
            struct Node1 *new_ks1 = ptab->ks1[i].node->next;
            while (new_ks1 != NULL) {

                printf("rel = %d, info = \"%s\"\t--->\t", new_ks1->release, new_ks1->item->info);

                new_ks1 = new_ks1->next;
            }

            printf("NULL\n");
        }
    }

    printf("\n-------KeySpace2-------\n");
    for (int i = 0; i < ptab->msize2; ++i) {
        printf("%d\t", i);
        if (ptab->ks2[i].item == NULL) {
            printf("NULL\n");
        }
        else {
            printf("key2 = \"%s\", rel = %d, info = \"%s\"\t--->\t", ptab->ks2[i].item->key2, ptab->ks2[i].release ,ptab->ks2[i].item->info);

            struct KeySpace2* new_ks2 = ptab->ks2[i].next;
            while (new_ks2 != NULL) {

                printf("key2 = \"%s\", rel = %d, info = \"%s\"\t--->\t", new_ks2->keys2, new_ks2->release, new_ks2->item->info);

                new_ks2 = new_ks2->next;
            }
            printf("NULL\n");
        }
    }
    return 1;
}

int insert(struct Table *ptab, int key1, char *key2, struct Item* item){

    if (find_key1(ptab, key1) == 1) {// kollizia + reles
        int h = find1(ptab, key1);

        struct Item* new = (struct Item*) calloc (1, sizeof(struct Item));
        new->info =  (char *)calloc (1, sizeof(char));
        strcpy(new->info, item->info);
        //new->release = 1;
        new->key1 = key1;
        new->key2 = (char*) calloc (strlen(item->key2) + 1, sizeof(char));
        strcpy(new->key2, item->key2);


        struct KeySpace1* ks1_ptr = (struct KeySpace1*) calloc (1, sizeof(struct KeySpace1));
        ks1_ptr->keys1 = ptab->ks1[h].keys1;

        struct Node1* node1 = (struct Node1*) calloc (1, sizeof(struct Node1));
        node1->item = ptab->ks1[h].node->item;
        node1->next = ptab->ks1[h].node->next;
        node1->release = ptab->ks1[h].node->release;

        ks1_ptr->node = node1;

        struct KeySpace1 ks1_buf;
        struct Node1* node1_buf = (struct Node1*) calloc (1, sizeof(struct Node1));;
        ks1_buf.node = node1_buf;
        ks1_buf.node->item = new;
        ks1_buf.keys1 = new->key1;
        ks1_buf.node->next = ks1_ptr->node;
        ks1_buf.node->release = ks1_ptr->node->release+1;

        ptab->ks1[h] = ks1_buf;

        int k = hesh(key2);
        int rel = find_rel(ptab, key2, k);


        if (ptab->ks2[k].item == NULL) {
            ptab->ks2[k].item = new;
            ptab->ks2[k].keys2 = new->key2;
            ptab->ks2[k].release = rel + 1;
            //new->release = rel + 1;
            return 1;
        }

        struct KeySpace2* ks2_ptr = (struct KeySpace2*) calloc (1, sizeof(struct KeySpace2));
        ks2_ptr->item = ptab->ks2[k].item;
        ks2_ptr->keys2 = ptab->ks2[k].keys2;
        ks2_ptr->next = ptab->ks2[k].next;
        ks2_ptr->release = ptab->ks2[k].release;

        struct KeySpace2 ks2_buf;
        ks2_buf.item = new;
        ks2_buf.keys2 = new->key2;
        ks2_buf.next = ks2_ptr;
        //new->release = rel + 1;
        //ks2_buf.release = new->release;
        ks2_buf.release = rel +1;

        ptab->ks2[k] = ks2_buf;

        return 0;
    }

    if (ptab->csize1 == ptab->msize1) {
        return 2;
    }

    struct Item* new = (struct Item*) calloc (1, sizeof(struct Item));
    new->info =  (char *)calloc (1, sizeof(char));
    //new->release = 1;
    strcpy(new->info, item->info);
    new->key1 = key1;

    new->key2 = (char*) calloc (strlen(item->key2) + 1, sizeof(char));
    strcpy(new->key2, item->key2);


    int i = ptab->csize1  - 1;
    while (i >= 0 && ptab->ks1[i].keys1 != key1 ) {

        struct Item* new1 = (struct Item*) calloc (1, sizeof(struct Item));
        new1->info =  (char *)calloc (1, sizeof(char));
        strcpy(new1->info, ptab->ks1[i].node->item->info);
        //new1->release = 1;
        new1->key1 = key1;
        new1->key2 = (char*) calloc (strlen(item->key2) + 1, sizeof(char));
        strcpy(new1->key2, ptab->ks1[i].node->item->key2);


        struct KeySpace1* ks1_ptr1 = (struct KeySpace1*) calloc (1, sizeof(struct KeySpace1));
        ks1_ptr1->keys1 = ptab->ks1[i].keys1;

        struct Node1* node11 = (struct Node1*) calloc (1, sizeof(struct Node1));
        //node11->item = ptab->ks1[i].node->item;
        node11->next = ptab->ks1[i].node->next;
        node11->release = ptab->ks1[i].node->release;

        ks1_ptr1->node = node11;
        node11->item = new1;


        ptab->ks1[i+1].keys1 = ks1_ptr1->keys1;
        ptab->ks1[i+1].node = node11;
        --i;
    }

    ptab->ks1[i+1].node->item = new;
    ptab->ks1[i+1].keys1 = new->key1;
    ptab->ks1[i+1].node->next = NULL;
    ptab->ks1[i+1].node->release = 1;//ptab->ks1[i+1].node->item->release;
    ++ptab->csize1;

    int h = hesh(key2);
    int rel = find_rel(ptab, key2, h);


    if (ptab->ks2[h].item == NULL) {
        ptab->ks2[h].item = new;
        ptab->ks2[h].keys2 = new->key2;
        ptab->ks2[h].release = rel + 1;
        //new->release = rel + 1;
        return 1;
    }

    struct KeySpace2* ks2_ptr = (struct KeySpace2*) calloc (1, sizeof(struct KeySpace2));
    ks2_ptr->item = ptab->ks2[h].item;
    ks2_ptr->keys2 = ptab->ks2[h].keys2;
    ks2_ptr->next = ptab->ks2[h].next;
    ks2_ptr->release = ptab->ks2[h].release;

    struct KeySpace2 ks2_buf;
    ks2_buf.item = new;
    ks2_buf.keys2 = new->key2;
    ks2_buf.next = ks2_ptr;
    //new->release = rel + 1;
    ks2_buf.release = rel+1;//new->release;

    ptab->ks2[h] = ks2_buf;

    return 1;
}

int find1(struct Table* ptab, int key)
{
    for (int i = 0; i < ptab->csize1; ++i)
    {
        if (ptab->ks1[i].keys1 == key && ptab->ks1[i].node->item != NULL)
            return i;
    }
    return -1;
}

struct Table* table_new() {
    struct Table* table_ptr = (struct Table*) calloc (1, sizeof(struct Table));
    table_ptr->csize1 = 0;
    table_ptr->csize2 = 0;
    table_ptr->msize1 = KS1_MAXSIZE;
    table_ptr->msize2 = KS2_MAXSIZE;
    table_ptr->ks1 = (struct KeySpace1*) calloc (table_ptr->msize1, sizeof(struct KeySpace1));
    table_ptr->ks2 = (struct KeySpace2*) calloc (table_ptr->msize2, sizeof(struct KeySpace2));

    for (int i = 0; i < table_ptr->msize1; ++i) {
        table_ptr->ks1[i].node = calloc(1, sizeof(struct Node1));

    }

    for (int i = 0; i < table_ptr->msize2; ++i) {
        table_ptr->ks2[i].item = NULL;
        table_ptr->ks2[i].next = NULL;
        table_ptr->ks2[i].keys2 = NULL;
    }
    return table_ptr;
};
int find_key1(struct Table* ptab, int key1) {

    int i = 0, m = ptab->csize1;
    int j;

    while (i <= m) {
        j = (i + m) / 2;
        if (key1 == ptab->ks1[j].keys1)
            return 1;
        if (key1 < ptab->ks1[j].keys1)
            m = j - 1;
        else
            i = j + 1;
    }
    return 0;
}
int find_key2(struct Table* ptab, char* key2) {

    int h = hesh(key2);

    if (ptab->ks2[h].item == NULL) {
        return 0;
    }

    if (strcmp(ptab->ks2[h].item->key2, key2)==0) {
        return 1;
    }

    struct KeySpace2* el_ks_2 = ptab->ks2[h].next;
    while (el_ks_2 != NULL) {
        if (strcmp(el_ks_2->keys2, key2)==0) {
            return 1;
        }
        el_ks_2 = el_ks_2->next;
    }

    return 0;
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
unsigned short int hesh(char c[Lengthkey])
{
    unsigned short int i = 0;
    for (int j = 0; j < Length2 && c[j] != 0; ++j)
        i += (~c[j]);
    return i % Length2;
}
int find_rel(struct Table* ptab, char* key2, int h) {
    if (ptab->ks2[h].item == NULL)
        return 0;
    if (strcmp(ptab->ks2[h].item->key2, key2) == 0)
        return ptab->ks2[h].release;

    struct KeySpace2* new_ks_2 = ptab->ks2[h].next;
    while (new_ks_2 != NULL) {
        if (strcmp(new_ks_2->keys2, key2) == 0)
            return new_ks_2->release;
        new_ks_2 = new_ks_2->next;
    }
    return 0;
}
struct Item* find_rel_ks1(struct Table* ptab,int h){
    if (ptab->ks1[h].node->item == NULL)
        return 0;
    if (ptab->ks1[h].node->item->key1 == ptab->ks1[h].keys1)
        return ptab->ks1[h].node->item;

    struct Node1* new_ks_1 = ptab->ks1[h].node->next;
    while (new_ks_1 != NULL) {
        if (new_ks_1->item->key1 == ptab->ks1[h].keys1)
            return new_ks_1->item;
        new_ks_1 = new_ks_1->next;
    }
    return 0;
}