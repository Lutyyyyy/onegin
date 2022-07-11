#include "onegin.h"


char* text_to_buf (FILE* file)
{
    if (file == nullptr)
    {
        printf ("ERROR: *file == nullptr");
        return NULL;
    }

    int sz = file_size (file);
    char* file_start = (char*) calloc (sz + 1, sizeof(char));
    fread (file_start, sizeof (char), sz, file);

    return file_start;
}

line_array* buf_to_line_arr (char* buf, size_t buf_size)
{
    size_t nLines = count_lines (buf, buf_size);
    
    line_array* lines_array = (line_array*) calloc (1,      sizeof (line_array));
    line*       lines       = (line*)       calloc (nLines, sizeof (line));

    char* ptr = buf;
    char* term = ptr;
    size_t j = 0;

    for ( ; j < nLines && (ptr = strchr (ptr, '\n')) != NULL; j++)
    {
        size_t len = size_t (ptr - term);

        char* string = (char*) calloc (len + 1, sizeof (char));
        lines[j].string = strncpy (string, term, len);
        lines[j].string[len] = '\0';
        lines[j].len = len;
        
        if (ptr + 1 != NULL)
            ptr++;
        term = ptr;
    }

    if (term != NULL)
    {
        size_t len = strlen (term);
        char* string = (char*) calloc (len + 1, sizeof (char));
        lines[j].string = strcpy (string, term);
        lines[j].len = len;
    }
    
    else 
    {
        char* string = (char*) calloc (1, sizeof (char));
        lines[j].string = strcpy (string, "\0");
        lines[j].len = 0;
    }
    
    lines_array->arr  = lines;
    lines_array->size = nLines;

    return lines_array;
}

void destruct_line_arr (line_array* array)
{
    for (int i = 0; i < array->size; i++)
        free (array->arr[i].string);
    
    free (array->arr);
    free (array);
}



long int file_size (FILE* file)
{
    fseek (file, 0L, SEEK_END);  
    long int sz = ftell (file); 
    fseek (file, 0L, SEEK_SET);
    return sz; 
}

size_t count_lines (char* buf, size_t buf_size)
{
    size_t str_counter = 0;
    char* ptr = buf;
    while ( (ptr = strchr (ptr, '\n')) != NULL )
    {
        ptr++;
        str_counter++;
    }

    return str_counter + 1;
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
