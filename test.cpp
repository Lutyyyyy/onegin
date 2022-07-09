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


//const char* bad_symbols_string   = " ,.\t!?:;";

line_array* parse_file (FILE* file);
void destruct_line_arr (line_array* array);

int main()
{
    FILE* file = fopen("hamlet.txt", "r");

    line_array* array = parse_file (file);
    for (int i = 0; i < array->size - 1; i++)
        printf ("%s\n", array->arr[i].string);

    destruct_line_arr (array);
    
    fclose(file);
    return 0;
}

line_array* parse_file (FILE* file)
{
    if (file == nullptr)
    {
        printf ("ERROR: *file == nullptr");
        return NULL;
    }

//  finding size of file and number of strings

    fseek (file, 0L, SEEK_END); // find END 
    long int sz = ftell (file); // bytes from START to END
    fseek (file, 0L, SEEK_SET); // return indicator to START position

    char* text_of_file = (char*) calloc (sz + 1, sizeof(char));
    long int i = 0;
    size_t str_counter = 0;
    while (i < sz)
    {
        char c = getc (file);
        if (c == '\n') 
        {
            c = '\0';
            str_counter++;
        }
        text_of_file[i] = c;
        i++;
    }
    if (getc (file) == EOF)
        text_of_file[i] = '\0';

//  creating array of strings

    line_array* str_array = (line_array*) calloc (1,               sizeof (line_array));
    line*       strings   = (line*)       calloc (str_counter + 1, sizeof (line));
/*
    if (str_counter == 0)
    {
        size_t len = strlen (text_of_file);
        char* term = (char*) calloc (len + 1, sizeof (char));
        strcpy (term, (char*) text_of_file);
        str_arr[0] = term;
    }
*/
    long int ptr = 0;
    size_t j = 0;
    
    for ( ; j == 0 || j < str_counter; j++)
    {
        size_t len = strlen ((char*) text_of_file + ptr);
        char* term = (char*) calloc (len + 1, sizeof (char));
        strings[j].string = strcpy (term, (char*) text_of_file + ptr);
        strings[j].len = len;
        
        ptr = ptr + len + 1;
    }
    str_array->arr  = strings;
    printf ("\n\n%d\n\n", str_counter);
    str_array->size = str_counter + 1;

    free (text_of_file);
    return str_array;
}

void destruct_line_arr (line_array* array)
{
    for (int i = 0; i < array->size; i++)
        free (array->arr[i].string);
    
    free (array->arr);
    free (array);
}