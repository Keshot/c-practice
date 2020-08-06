#ifndef SORT_ALGORITHM_H_GUARD
#define SORT_ALGORITHM_H_GUARD

/* function for print array :-)  */
void array_print(const int *, int);
/* creates an array and fill it with some numbers  */
int *array_init(int);
/* it just practice with function pointer :-) */
void arr_swap(int *, int *);
/* i did some test, with array by 100 000 elements and wrote down time of sort completion */
/* compiler is gcc with -g with -O0  */
/* 38.378  */
void bubble_sort(int *, int, void (*)(int *, int *));
/* 24.272 */
void shaker_sort(int *, int, void (*)(int *, int *));
/* 12.680  */
void insertion_sort(int *, int, void (*)(int *, int *));
/* 0.218 lol */
void merge_sort(int *, int*, int, void (*)(int *, int *));
/* 0.148 :-) */
void quick_sort(int *, int*, void (*)(int *, int *));


#endif
