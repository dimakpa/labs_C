#define NMAX 20
#define  VEC //LIST or VEC
#ifdef VEC

struct st{
    char c[NMAX];
    int top;
};


#else
struct st {
    char c;
    struct st *next;
};
struct st *stack2 = NULL;

#endif

void stack_init(struct st *a);
//void stack_init(struct st1 *a);

int prior(char a);
char delet(struct st **head);
struct st *push(struct  st *head, char a);

void init(struct st *stk);
void push_vector(struct st *st1, char a);
char delet_vector(struct st *st1);