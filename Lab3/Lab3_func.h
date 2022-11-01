#define KS1_MAXSIZE 5
#define KS2_MAXSIZE 5
#define Lengthkey 8
//каждый элемент таблицы имеет следующую структуру:
struct KeySpace1{
    int keys1;			/* ключ элемента				*/
    struct Node1 *node;			/* указатель на информацию			*/
};

//Элемент списка имеет следующую структуру:
struct Node1{
    int release;	/* номер версии						*/
    struct Item *item;		/* указатель на информацию				*/
    struct Node1 *next;		/* указатель на следующий элемент			*/
};


struct KeySpace2{
    char *keys2;		/* ключ элемента			*/
    int release;	/* номер версии элемента		*/
    struct Item *item;		/* указатель на информацию		*/
    struct KeySpace2 *next;	/* указатель на следующий элемент	*/

};

//Каждый элемент таблицы имеет следующую структуру:
struct Item{
    char *info;
    int key1;
    char *key2;
};

struct Table{
    struct KeySpace1 *ks1;
    /* указатель на первое пространство ключей			*/
    struct KeySpace2 *ks2;
    /* указатель на второе пространство ключей			*/

    int	msize1;
    /* размер области 1-го пространства ключей 			*/
    int msize2;
    /* размер области 2-го пространства ключей 			*/

    int csize1;
    /* количество элементов в области 1-го пространства ключей	*/
    int csize2;

    int number;



}Table;

int getInt(int *a);
char *get_str();
int D_Add( struct Table *Table);
int D_Find(struct Table *Table);

struct Table* table_new();
int Find_With_Key1(struct Table* ptab);
int Find_With_Key2(struct Table* ptab);
struct KeySpace1* find_and_copy_with_key1 (struct Table* ptab, int key1, int rel);
struct KeySpace2* find_and_copy_with_key2(struct Table* ptab, char* key2, int release);

int Find_With_Two_Keys(struct Table *ptab);

int find_key1(struct Table *ptab, int key1);
int find_and_delete_rel_ks1(struct Table* ptab,int k1, int rel);
int find_key2(struct Table* ptab, char* key2);
int find_and_delete_rel_ks2(struct Table* ptab,char* key2,int release);
int find_rel(struct Table* table_ptr, char* key2, int h);

int D_Delete(struct Table *Table);
int Del_With_Key1(struct Table* ptab);
int delete_with_key1 (struct Table* table_ptr, int key1);
int Del_With_Key2(struct Table* ptab);
int delete_with_key2 (struct Table* table_ptr, char* key2);
int Delete_With_Both_Keys (struct Table* ptab);
int delete_with_two_keys (struct Table* table_ptr, int key1, char* key2);


int D_Show(struct Table *Table);

int insert( struct Table *Table, int key1,char *key2, struct Item* item);
int findInfoKey(struct Table Table, int k);
char * findInfoVers(struct Table Table,int vers, int k);
int dialog(const char *msgs[], int n);

unsigned short int hesh(char c[Lengthkey]);
int find1(struct Table* ptab, int key);


