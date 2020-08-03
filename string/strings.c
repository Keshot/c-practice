#include "headers/strings.h"
#include <stdlib.h>

enum{ null_symbol = 1, equal = 0, larger = 1, less = -1, find = 1, not_find = 0 };

static void ch_copy(const char *src, char *dst, int size);
static void str_shift(string_t *str_to_shft, int position, int shft_count);

string_t *str_init(const char *str, int size)
{
    string_t *temp;
    if(!size)
    {
        for(; *str != '\0'; str++, size++);
        str -= size;
        size++;/* for zero symbol */
    }
    temp = malloc(sizeof(*temp));
    if(temp)
    {
        temp->data = malloc(sizeof(char) * size);
        if(temp->data)
        {
            temp->max_length = temp->used = size;
            temp->mem_free = 0;
            ch_copy(str, temp->data, size - null_symbol);
        }
    }
    return temp;
}

string_t *with_str_init(const string_t *str, int str_size)
{
    string_t *temp;
    str_size = ((str_size == 0) || (str_size > str->used)) ? str->used : str_size;
    temp = malloc(sizeof(*temp));
    if(temp)
    {
        temp->data = malloc(sizeof(char) * str_size);
        if(temp->data)
        {
            ch_copy(str->data, temp->data, str_size - null_symbol);
            temp->max_length = temp->used = str_size;
            temp->mem_free = 0;
        }
    }
    return temp;
}

int str_compare(const string_t *src_str, const string_t *dst_str)
{
    int compare_res = equal, i;
    for(i = 0; i < (src_str->used - null_symbol); i++)
    {
        if(src_str->data[i] == dst_str->data[i])
            continue;
        else
        {
            if(dst_str->data[i] == '\0')
                return larger;
            else
                return src_str->data[i] > dst_str->data[i] ? larger : less;
        }
    }
    return compare_res;
}

char *new_string(const string_t *str)
{
    char *new_str = malloc(sizeof(char) * str->used);
    if(new_str)
    {
        ch_copy(str->data, new_str, str->used);
        return new_str;
    }
    return NULL;
}

void strcopy(string_t **dst, const string_t *src)
{
    *dst = malloc(sizeof(string_t));
    (*dst)->data = malloc(sizeof(char) * src->used);
    if(*dst)
    {
        ch_copy(src->data, (*dst)->data, src->used);
        (*dst)->max_length = src->max_length;
        (*dst)->used = src->used;
        (*dst)->mem_free = src->mem_free;
    }
}

void strn_copy(string_t **dst, const string_t *src, int size)
{
    *dst = malloc(sizeof(string_t));
    if(*dst)
    {
        (*dst)->data = malloc(sizeof(char) * size + null_symbol);
        if((*dst)->data)
        {
            ch_copy(src->data, (*dst)->data, size);
            (*dst)->used = size;
            (*dst)->max_length = size;
            (*dst)->mem_free = size;
        }
    }
}

char *str_char(const string_t *str_src, char ch)
{
    int iter;
    for(iter = 0; iter < str_src->used; iter++)
    {
        if(str_src->data[iter] == ch)
            return &(str_src->data[iter]);
    }
    return NULL;
}

char *strr_char(const string_t *str, char ch)
{
    int iter;
    char *res = NULL;
    for(iter = 0; iter < str->used - null_symbol; iter++)
        res = str->data[iter] == ch ? &(str->data[iter]) : res;
    return res;
}

void str_shrink(string_t *str, int count)
{
    int iter, new_size = str->used - count;
    char *new_str = malloc(sizeof(char) * new_size);
    for(iter = 0; iter < new_size - null_symbol; iter++)
        new_str[iter] = str->data[iter];
    new_str[iter] = '\0';
    free(str->data);
    str->data = new_str;
    str->max_length = new_size;
    str->used = new_size;
}

void str_grow(string_t *str, int count)
{
    int new_size = str->used + count;
    str->data = realloc(str->data, new_size);
    str->max_length = new_size;
    str->mem_free = new_size - str->used;
}

void str_cat(const string_t *src, string_t *dst)
{
    int size_now = dst->used;
    str_grow(dst, src->used - null_symbol);
    ch_copy(src->data, &(dst->data[size_now - null_symbol]), src->used);
}

void strn_cat(const string_t *src, string_t *dst, int position)
{
    int src_size = src->used - null_symbol;
    str_grow(dst, src_size);
    str_shift(dst, position, src_size);
    char *src_str = &(dst->data[position]);
    for(int iter = 0; iter < src_size; iter++, src_str++)
        *src_str = src->data[iter];
}

int str_str(const string_t *haystack, const string_t *needle, char **out_str_addres)
{
    int i = 0, j = 0;
    for(; haystack->data[i]; j++, i++)
    {
        if(haystack->data[i] != needle->data[j])
        {
            i = j > 0 ? i - 1 : i;      /* <------ this construction returns us on the next */
            j = -1;                     /* iteration to the same character in order to check it at the beginning of the string  */
            continue;
        }else
        if(j + 1 == (needle->used - null_symbol))
        {
            if(out_str_addres)
            {
                *out_str_addres = haystack->data + i - j;
            }
            return find;
        }
    }
    return not_find;
}

int strn_compare(const char *src_str, const char *dst_str, int size)
{
    if(!size)
        return equal;
    return *src_str == *dst_str ?
            strn_compare(src_str + 1, dst_str + 1, size - 1)
            : *src_str > *dst_str ? larger : less;
}

void str_reverse(char* str, int size)
{
    char *str_end = str + (size - (null_symbol + null_symbol));
    for(; str <= str_end; str++, str_end--)
    {
        char temp = *str;
        *str = *str_end;
        *str_end = temp;
    }
}

static void str_shift(string_t *str_to_shft, int position, int shft_count)
{
    int end_pos = str_to_shft->used;
    for(; end_pos >= position; end_pos--)
    {
        for(int iter = 0, indx = end_pos; iter < shft_count; iter++, indx++)
            str_to_shft->data[indx + 1] = str_to_shft->data[indx];
    }
}

static void ch_copy(const char *src, char *dst, int size)
{
    for(int i = 0; i < size; i++, *dst = *src, src++, dst++);
    *dst = '\0';
}
