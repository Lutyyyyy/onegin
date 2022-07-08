#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>

struct line
{
    char* string;
    int len;
};

int buf_size = 1000;
const char* bad_symbols_string   = " ,.\t!?:;";
char** parse_file (FILE* file);

int main()
{
    FILE* file = fopen("test.txt", "r");

    char** arr = parse_file (file);
    printf ("%s\n", arr[0]);
    free(arr[0]);
    free(arr);
    
    fclose(file);
/*
    for (int i = 0; i < 4459; i++)
    {
        printf ("%s\n", arr[i]);
        free(arr[i]);
    }
    free(arr);
*/
    return 0;
}

char** parse_file (FILE* file)
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

    char** str_arr = (char**) calloc (str_counter + 1, sizeof (char*));
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
        strcpy (term, (char*) text_of_file + ptr);
        str_arr[j] = term;
        ptr = ptr + len + 1;
    }

    free (text_of_file);
    return str_arr;
}
