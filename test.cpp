#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct line_ {
    char* str;
    int len;
} line;

typedef struct Line_array_ {
    line* arr;
    size_t len;
} Line_array;


int buf_size = 1000;
const char* bad_symbols_string   = " ,.\t!?:;";
Line_array* parse_file (FILE* file);


int main()
{
    FILE* file = fopen("test.txt", "r");

    Line_array* arr = parse_file (file);
    printf ("%s\n", arr->arr[0].str);
    fclose(file);

/*    for (int i = 0; i < 1; i++)
        free(arr[i]);
    free(arr);
*/
    return 0;
}

Line_array* parse_file (FILE* file)
{
    if (file == nullptr)
    {
        printf ("ERROR: *file == nullptr");
        return NULL;
    }

//  finding size of file and number of strings

    fseek (file, 0L, SEEK_END);  // find END 
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

    Line_array* str_arr = (Line_array*) calloc (str_counter + 1, sizeof (Line_array));

    if (str_counter == 0)
    {
        size_t len = strlen (text_of_file);
        line* term   = (line*) calloc (1,       sizeof (line));
        char* string = (char*) calloc (len + 1, sizeof (char));
        strcpy (string, (char*) text_of_file);
        
        term->str = string;
        term->len = len;
        str_arr->arr[0] = *term;
        str_arr->len = 1;

        free (text_of_file);
        return str_arr;    
    }

    long int ptr = 0;
    size_t j = 0;
    
    for ( ; j < str_counter; j++)
    {
        size_t len = strlen ((char*) text_of_file + ptr);
        line* term   = (line*) calloc (1,       sizeof (line));
        char* string = (char*) calloc (len + 1, sizeof (char));
        strcpy (string, (char*) text_of_file + ptr);
        term->str = string;
        term->len = len;
        str_arr->arr[j] = *term;
        ptr = ptr + len + 1;
    }
    str_arr->len = str_counter + 1;
    free (text_of_file);
    return str_arr;
}
