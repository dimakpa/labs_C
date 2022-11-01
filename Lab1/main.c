#include <stdio.h>
#include "Lab1_func.h"



int main() {
    Matrix matrix = {0, NULL};
    input(&matrix);
    output("Source matrix", matrix);
    matrix_change(&matrix);
    output("Change matrix", matrix);
    erase(&matrix);
    return 0;
}
