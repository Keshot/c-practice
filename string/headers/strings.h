#ifndef STRINGS_H_GUARD
#define STRINGS_H_GUARD

typedef struct strings
{
    char *data;
    /* total allocated memory  */
    int max_length;
    /* how much it take right now  */
    int used;
    /* amount of free memory  */
    int mem_free;
}string_t;
/* the function can be called with size 0 then it will be calculate the size itself  */
string_t *str_init(const char *str, int str_size);
/* if str_size equal 0 or > str->used then str_size = sre->used  */
string_t *with_str_init(const string_t *str, int str_size);
string_t *strcopy_new(const string_t *src);
void strcopy(string_t *dst, const string_t *src);
/* record new C string  */
void new_string(const char *new_str, string_t *str_ptr);
int str_compare(const string_t* str1, const string_t* str2);
int strn_compare(const string_t* str1, const string_t*, int n);
void str_reverse(char* str, int str_size);

#endif
