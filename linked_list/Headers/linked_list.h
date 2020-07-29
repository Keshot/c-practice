#ifndef LINKED_LIST_H_GUARD
#define LINKED_LIST_H_GUARD

typedef struct Node{
    int data;
    struct Node *next;
}Node_t;

void add_new_item(Node_t **first, Node_t **last, int new_num);
void add_new_node(Node_t *node, Node_t *first);
void add_in_begin(Node_t **first, int new_num);
void add_in_end(Node_t **last, int new_num);
Node_t *find_element(Node_t *first, int value);
Node_t *add_after(Node_t *current, int new_num);
int *list_copy_to_array(Node_t *first);
Node_t *int_array_copy_to_list(int *arr_ptr, int length);
void remove_all(Node_t **first, Node_t **last);
void remove_element(Node_t *first, Node_t *element);
int pop_front_(Node_t **first);
int pop_back_(Node_t *first, Node_t **last);
Node_t *find_last(Node_t *first);
int element_counts(Node_t *first);

#endif
