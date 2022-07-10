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



line_array* construct_line_arr  (FILE* file);
void        destruct_line_arr   (line_array* array);
void        print_title         (FILE* file, const char* title);
void        print_lines_to_file (FILE* file, line_array* arr);

#endif