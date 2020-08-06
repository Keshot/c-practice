#include "headers/sort_algorithm.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

static int rand_number(int max, int min);

void array_print(const int *arr_ptr, int size)
{
    for(int iter = 0; iter < size; iter++)
        fprintf(stdout, "[%d]", arr_ptr[iter]);
    printf("\n");
}

int *array_init(int arr_size)
{
    int iter;
    int *new_arr = malloc(sizeof(*new_arr) * arr_size);
    srand(time(NULL));
    for(iter = 0; iter < arr_size; iter++)
        new_arr[iter] = rand_number(50, 1);
    return new_arr;
}

void bubble_sort(int *arr_ptr, int size, void (*fpswap)(int *, int *))
{
    int iter;
    int flag = 1;
    while(flag)
    {
        flag = 0;
        for(iter = 0; iter < size - 1; iter++)
        {
            if(arr_ptr[iter] > arr_ptr[iter + 1])
            {
                (*fpswap)(arr_ptr + iter, arr_ptr + iter + 1);
                flag = 1;
            }
        }
    }
}

void shaker_sort(int *arr_ptr, int size, void (*fpswap)(int *, int *))
{
    int left_iter, right_iter;
    int arr_begin = 0;
    int arr_end = size - 1;
    while(arr_begin <= arr_end)
    {
        for(left_iter = arr_begin; left_iter < arr_end; left_iter++)
        {
            if(arr_ptr[left_iter] > arr_ptr[left_iter + 1])
                (*fpswap)(arr_ptr + left_iter, arr_ptr + left_iter + 1);
        }
        arr_end--;
        for(right_iter = arr_end; right_iter > arr_begin; right_iter--)
        {
            if(arr_ptr[right_iter] < arr_ptr[right_iter - 1])
                (*fpswap)(arr_ptr + right_iter, arr_ptr + right_iter - 1);
        }
        arr_begin++;
    }
}

void insertion_sort(int *arr_ptr, int size, void (*fpswap)(int *, int *))
{
    int iter, insert_iter;
    for(iter = 1; iter < size; iter++)
    {
        for(insert_iter = iter; insert_iter > 0
                                && arr_ptr[insert_iter] < arr_ptr[insert_iter - 1];
                                 insert_iter--)
        {
            (*fpswap)(arr_ptr + insert_iter, arr_ptr + insert_iter - 1);
        }
    }
}

void quick_sort(int *arr_start, int *arr_end, void (*fpswap)(int*, int*))
{
    int size = arr_end - arr_start;
    int pivot = arr_start[size >> 1];
    int *iter_start = arr_start;
    int *iter_end = arr_end;
    while(iter_start < iter_end)
    {
        for(; *iter_start < pivot; iter_start++);
        for(; *iter_end > pivot; iter_end--);
        if(iter_start <= iter_end)
        {
            (*fpswap)(iter_start, iter_end);
            iter_start++;
            iter_end--;
        }
    }
    if(arr_start < iter_end)
    {
        quick_sort(arr_start, iter_end, fpswap);
    }
    if(iter_start < arr_end)
    {
        quick_sort(iter_start, arr_end, fpswap);
    }
}

void merge_sort(int *arr_start, int *arr_end, int ln, void(*fpswap)(int *, int *))
{
    if(ln < 2)
        return;
    if(ln == 2)
    {
        if(*arr_start > *arr_end)
            (*fpswap)(arr_start, arr_end);
        return;
    }
    int center = ln / 2;
    merge_sort(arr_start, arr_start + (center - 1), center, fpswap);
    merge_sort(arr_start + center, arr_end, ln - center, fpswap);
    int *res_arr = malloc(sizeof(*res_arr) * ln);
    int first_arr_ln = center;
    /* int second_arr_ln = ln - center; */
    int first_arr_iter = 0;
    int second_arr_iter = center;
    int res_arr_iter = 0;
    while((first_arr_iter < first_arr_ln) && (second_arr_iter < ln))
    {
        res_arr[res_arr_iter++] = arr_start[first_arr_iter] < arr_start[second_arr_iter] ?
                                arr_start[first_arr_iter++] : arr_start[second_arr_iter++];
    }
    for(; first_arr_iter < first_arr_ln; first_arr_iter += 1)
    {
        res_arr[res_arr_iter++] = arr_start[first_arr_iter];
    }
    for(; second_arr_iter < ln; second_arr_iter += 1)
    {
        res_arr[res_arr_iter++] = arr_start[second_arr_iter];
    }
    for(int i = 0; i < ln; i++)
        arr_start[i] = res_arr[i];
}

void arr_swap(int *first, int *second)
{
    int temp = *first;
    *first = *second;
    *second = temp;
}

static int rand_number(int max, int min)
{
    return rand() % max + min;
}