#include "onegin.h"


line_array* construct_line_arr (FILE* file)
{
//  check if could open file
    if (file == nullptr)
    {
        printf ("ERROR: *file == nullptr");
        return NULL;
    }


//  finding size of file 
    fseek (file, 0L, SEEK_END); // find END 
    long int sz = ftell (file); // bytes from START to END
    fseek (file, 0L, SEEK_SET); // return indicator to START position


// finding number of strings to calloc 
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
    {
        text_of_file[i] = '\0';
        str_counter++;
    }


//  creating array of strings
    line_array* str_array = (line_array*) calloc (1,               sizeof (line_array));
    line*       strings   = (line*)       calloc (str_counter, sizeof (line));

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
    str_array->size = str_counter;


//  free buffer and return
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

void print_title (FILE* file, const char* title)
{
    fprintf (file,  "\n"
                    "\n"
                    "\n"
                    "################################################"
                    "\n"
                    "\t%s"
                    "\n"
                    "################################################"
                    "\n"
                    "\n"
                    "\n", title);
    return;
}

void print_lines_to_file (FILE* file, line_array* array)
{
    for (int i = 0; i < array->size; i++)
        fprintf (file, "%s\n", array->arr[i].string);
    return;
}