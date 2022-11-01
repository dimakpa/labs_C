
struct Ver{
    char *name;
    int x;
    int y;
    struct Reb_to_ver *reb_to_ver;
    struct Ver *next;
    struct Queue *queue;
    struct Ford *ford;
    struct Ostov *ostov;
};

struct Reb_to_ver{
    struct Reb_to_ver *next;
    struct Ver *smezg;
    double weight;
    struct Ver *parent;
};

struct Graph{
    struct Ver *ver;
    struct Ver *ostov_ver;
    struct Reb_to_ver *list_reb;
};

struct Ford{
    int d;
    struct Ver *pred;
};

struct Queue{
    int color;
    int d;
    struct Ver *pred;
};

struct Q{
    struct Ver *ver;
    struct Q *next;
};

struct Ostov{
    struct Ver *pred;
    int rank;
};

int D_Add_Ver(struct Graph *root);
struct Ver *ver_new();
int inseart_ver(struct Ver *new_element, struct Graph *root);

int D_Add_Reb(struct Graph *root);
void inseart_reb(struct Graph *root, struct Ver *ver1, struct Ver *ver2);
double calculations(struct Ver *ver1, struct Ver *ver2);

int D_Find_From_Ver(struct Graph *root);
struct Ver *find_ver(struct Graph* root, int key1, int key2);
struct Ver *find_ver_do(struct Graph* root, struct Ver *del_ver);
void find_bfs(struct Graph *root, int start, int key1, int key2);
void initialization(struct Graph *root);
void push_stack(struct Ver *s, struct Q *q);
struct Ver *take_stack(struct Q *q);
void print_path(struct Graph *root_graph, struct Ver *s,struct Ver *v);

int D_Delete_Ver(struct Graph *root);
int del_rebro_of_ver(struct Graph *root_graph, struct Ver *del_ver);
void del_rebro(struct Ver *ver, int x, int y);
int D_Delete_Reb(struct Graph* root_graph);

int D_Show(struct Graph* root);

int D_VisualizeGraph(struct Graph *root_graph);

int D_Find_Short_Way(struct Graph* root_graph);
void find_ford(struct Graph *root_graph, int key1, int key2);
void initialization_ford(struct Graph *root_graph);

int D_Find_Short_Ostov(struct Graph *root_graph);
void initialization_kruskal(struct Graph *root_graph);
void mst_prim(struct Graph *root_graph);
struct Reb_to_ver *sort_spisok_reb(struct Reb_to_ver *list_reb);
struct Ver *find_q(struct Graph *root_graph, struct Ver *v);
struct Ver *find_set(struct Ver *ver);
void tree_union(struct Ver *u,struct Ver *v);
void link(struct Ver *u, struct Ver *v);
void insert_to_ostov(struct Graph *root_graph, struct Reb_to_ver *root_rebr);
void inseart_ver_ostov(struct Ver *new_element, struct Graph *root);
void inseart_reb_ostov(struct Graph *root, struct Ver *ver1, struct Ver *ver2);
struct Ver *find_ver_ostov(struct Graph* root, int key1, int key2);

int D_Graphviz_ostov(struct Graph *root_graph);

int getInt(int *a);
char *get_str();
int dialog(const char *msgs[], int N);
struct Graph *graph_new();