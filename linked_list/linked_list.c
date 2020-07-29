#include "Headers/linked_list.h"
#include <stdlib.h>

void remove_all(Node_t **first, Node_t **last)
{
    Node_t *temp;
    if(!(*first))
        return;
    while(*first)
    {
        temp = *first;
        *first = (*first)->next;
        free(temp);
    }
    if(!(*last))
        return;
    *last = *first;
}

int *list_copy_to_array(Node_t *first)
{
    int i;
    int arr_length;
    int *new_arr;
    if(!first)
        return NULL;
    arr_length = element_counts(first);
    new_arr = malloc(arr_length * sizeof(int));
    for(i = 0; first; first = first->next, i++)
    {
        new_arr[i] = first->data;
    }
    return new_arr;
}

void add_new_item(Node_t **first, Node_t **last, int new_num)
{
    Node_t *temp = malloc(sizeof(Node_t));
    temp->data = new_num;
    temp->next = NULL;
    if(last && *last)
    {
        (*last)->next = temp;
        *last = temp;
    }
    else
        *first = temp;
}

Node_t *add_after(Node_t *current, int new_num)
{
    Node_t* temp = malloc(sizeof(Node_t));
    temp->data = new_num;
    temp->next = current->next;
    current->next = temp;
    return temp;
}

void add_in_begin(Node_t **first, int new_num)
{
    Node_t* temp;
    if(!(*first))
        *first = NULL;
    temp = malloc(sizeof(Node_t));
    temp->data = new_num;
    temp->next = *first;
    *first = temp;
}

void add_in_end(Node_t **last, int new_num)
{
    Node_t* temp = malloc(sizeof(Node_t));
    temp->data = new_num;
    temp->next = NULL;

    if(!(*last))
        *last = temp;
    (*last)->next = temp;
    *last = temp;
}

void remove_element(Node_t* first, Node_t *element)
{
    Node_t** current_ptr = &first;
    for(;*current_ptr != element; current_ptr = &((*current_ptr)->next));
    (*current_ptr) = element->next;
    free(element);
}

int pop_front_(Node_t **first)
{
    int value;
    value = (*first)->data;
    return value;
}

int pop_back_(Node_t *first, Node_t **last)
{
    Node_t *temp = *last;
    int value = (*last)->data;
    for(; first->next != *last; first = first->next){}
    *last = first;
    (*last)->next = NULL;
    free(temp);
    return value;
}

Node_t *find_element(Node_t *first, int value)
{
    if(first)
    {
        for(;first->data != value; first = first->next){}
    }
    return first;
}

int element_counts(Node_t* first)
{
    int count;
    for(count = 0; first; count++, first = first->next){}
    return count;
}

Node_t *find_last(Node_t *first)
{
    while(first->next)
        first = first->next;
    return first;
}

void add_new_node(Node_t* node, Node_t* first)
{
    node->next = first;
    first = node;
}

Node_t *int_array_copy_to_list(int *arr_ptr, int length)
{
    Node_t *first = NULL;
    for(int i = 0; i < length; i++)
    {
        add_in_begin(&first, arr_ptr[i]);
    }
    return first;
}
