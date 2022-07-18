#ifndef ONEGIN_H_
#define ONEGIN_H_

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct line_
{
    char* string;
    int len;
} line;

typedef struct line_array_
{
    line* arr;
    size_t size;
} line_array;



char*       text_to_buf         (FILE* file);
line_array* buf_to_line_arr     (char* buf, size_t buf_size);

line_array* copy_line_arr       (line_array* array);
void        destruct_line_arr   (line_array* array);

long int    file_size           (FILE* file);
size_t      count_lines         (char* buf, size_t buf_size);
int         my_fputs            (const char *s, FILE* stream);

void        print_title         (FILE* file, const char* title);
void        print_lines_to_file (FILE* file, line_array* arr);

#endif