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
string_t *str_init(const char *, int);
/* if str_size equal 0 or > str->used then str_size = str->used  */
string_t *with_str_init(const string_t *, int);
void strcopy(string_t **out, const string_t *);
/* record new C string  */
/* copy first n characters  */
void strn_copy(string_t **out, const string_t *, int);
char *new_string(const string_t *);
/* returns the addres of the character in a string  */
char *str_char(const string_t *, char);
/* returns the addres of the last character in a string */
char *strr_char(const string_t *, char);
/* reduce the amount of memory on the string */
void str_shrink(string_t *, int);
/* increase the amount of memory on the string */
void str_grow(string_t *, int);
/* finds the first occurrence of a string */
int str_str(const string_t *, const string_t *, char **out);
/* appends src string to dst string to the end point */
void str_cat(const string_t *, string_t *);
/* appends src string to dst string in the n positiont */
void strn_cat(const string_t *, string_t *, int);
int str_compare(const string_t*, const string_t*);
int strn_compare(const char*, const char*, int);
void str_reverse(char *, int);

#endif
