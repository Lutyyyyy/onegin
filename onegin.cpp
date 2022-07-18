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

    long int nSymbols = fread (file_start, sizeof (char), sz, file);
    file_start[nSymbols] = '\0';

    return file_start;
}

line_array* buf_to_line_arr (char* buf, size_t buf_size)
{
    size_t nLines = count_lines (buf, buf_size);
    
    line_array* lines_array = (line_array*) calloc (1,      sizeof (line_array));
    line*       lines       = (line*)       calloc (nLines, sizeof (line));

    char* ptr = buf;
    char* term = ptr;
    size_t str_counter = 0;

    for ( ; (ptr = strchr (ptr, '\n')) != NULL; str_counter++)
    {
        size_t len = size_t (ptr - term);

        lines[str_counter].string = term;
        lines[str_counter].len = len;
        
        if (ptr + 1 != NULL)
            ptr++;
        term = ptr;
    }

    size_t len = buf_size - size_t (term - buf);
    lines[str_counter].string = term;
    lines[str_counter].len = len;

    lines_array->arr  = lines;
    lines_array->size = nLines;

    return lines_array;
}

void destruct_line_arr (line_array* array)
{  
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

line_array* copy_line_arr (line_array* array)
{
    line_array* lines_array = (line_array*) calloc (1,           sizeof (line_array));
    line*       lines       = (line*)       calloc (array->size, sizeof (line));

    size_t line_counter = 0;
    while (line_counter < array->size) 
    {
        lines[line_counter].string = array->arr[line_counter].string;
        lines[line_counter].len    = array->arr[line_counter].len;

        line_counter++;
    }

    lines_array->arr = lines;
    lines_array->size = array->size;

    return lines_array;
}

int my_fputs (const char *s, FILE* stream)
{
    if (s == NULL)
        return EOF;

    size_t i = 0;
    while (s[i] != '\n' && s[i] != '\0')
        fputc (s[i++], stream);
    
    fputc ('\n', stream);
    return i;
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
        my_fputs(array->arr[i].string, file);
    return;
}
