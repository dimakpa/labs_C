struct Tree{
    struct Node* root;
};

struct Xy{
    int x;
    int y;
    int width;
};

struct Item{
    char *info;
    struct Xy *xy;
};
struct Node{
    struct Item *inw;
    struct Item *ine;
    struct Item *isw;
    struct Item *ise;

    struct Node *nw;
    struct Node *ne;
    struct Node *sw;
    struct Node *se;
    struct Xy *xy;
    struct  Node *par;
}Node;


int D_Add(struct Tree *root);
int vstavka_quadro(struct Item *new_element, struct Tree *root);

int D_Find(struct Tree *root);
struct Node *find_recurs(struct Node *ptr,int key1, int key2);

int D_Delete(struct Tree *root);
struct Item *delete_recurs(struct Tree *root, struct Node *ptr,int key1, int key2);
void del_node(struct Node *res);

int D_Show(struct Tree* root);
void print_tree(struct Node* root, int level);

int D_File(struct Tree* root);
int D_FindTime(struct Tree* root_tree);



int getInt(int *a);
char *get_str();
int dialog(const char *msgs[], int N);
struct Tree *tree_new();