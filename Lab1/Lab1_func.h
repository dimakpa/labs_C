typedef struct Line {
    double *a;
    int n;
}Line ;

typedef struct Matrix {
    int lines;   //count of lines
    Line *matr;
} Matrix;

int matrix_change(Matrix *a);
int input(Matrix *matrix);

int getInt(int *a);
int getDouble(double *a);
void erase(struct Matrix *a);
void output(const char *msg, Matrix a);

double search_first_element(Matrix *a, int i);
double search_second_element(Matrix *a, int i);
void swap(Matrix *a,int perem1,int perem2, int i);