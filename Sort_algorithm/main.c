#include "headers/sort_algorithm.h"
#include <stdio.h>
#include <stdlib.h>
#define ARR_SIZE 100000

int main(int argc, char *argv[])
{
    int size = ARR_SIZE;
    int *arr1 = array_init(size);
    array_print(arr1, size);
    merge_sort(arr1, arr1 + (size - 1), size, &arr_swap);
    array_print(arr1, size);
    return 0;
}
