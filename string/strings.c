#include "headers/strings.h"
#include <stdlib.h>

enum{ null_symbol = 1 };

static void ch_copy(const char *src, char *dst, int size);

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
    int i;
    for(i = 0; i < (src_str->used - 1); i++)
        if(src_str->data != dst_str->data)
        {

        }
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

static void ch_copy(const char *src, char *dst, int size)
{
    for(int i = 0; i < size; i++, *dst = *src, src++, dst++);
    *(dst + 1) = '\0';
}
