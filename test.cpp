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



line_array* parse_file          (FILE* file);
void        destruct_line_arr   (line_array* array);
int         skip_bad_start      (const char* str);
int         start_comparator    (line l1, line l2);
int         skip_bad_end        (char* begin, char* str);
int         end_comparator      (line l1, line l2);
void        bubblesort          (line_array* array, int (*cmp_function) (line l1, line l2));
void        swap                (line_array* array, int i, int j);
int         my_tolower          (char c);
int cmp (const void* a, const void* b);


int main()
{
    FILE* file = fopen("hamlet.txt", "r");

    line_array* array = parse_file (file);
//    bubblesort (array, start_comparator);
    qsort (array->arr, array->size, sizeof (line), cmp);
    for (int i = 0; i < array->size; i++)
        printf ("%s\n", array->arr[i].string);

    destruct_line_arr (array);
    
    fclose(file);


/*
    const char* s[] = {"", ".qwertyu", "", "rf???"};
    
    line l1, l2;
    l1.string = (char*) s[3];
    l1.len = strlen(s[3]);

    l2.string = (char*) s[1];
    l2.len = strlen(s[1]);

    int res = end_comparator(l1, l2);

    printf ("res = %d\n", res);
*/
    

    
    return 0;
}

line_array* parse_file (FILE* file)
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


int skip_bad_start (const char* str)
{
    int skip = 0;
    while (strchr (" ,.\t!?:;", *(str + skip)) != NULL && *(str + skip) != '\0')
        skip++; 

    return skip;
}

int start_comparator (line* l1, line* l2)
{
    size_t p1 = 0, p2 = 0;

    p1 += skip_bad_start (l1->string + p1);
    p2 += skip_bad_start (l2->string + p2);
    
    while (my_tolower(l1->string[p1]) == my_tolower(l2->string[p2]))
    {
        if (l1->string[p1] == '\0' || l2->string[p2] == '\0')
            return (my_tolower(l1->string[p1]) - my_tolower(l2->string[p2] > 0)) ? 1 : -1;
        
        p1++;
        p2++;
        p1 += skip_bad_start (l1->string + p1);
        p2 += skip_bad_start (l2->string + p2);

    }

    return (my_tolower(l1->string[p1]) - my_tolower(l2->string[p2]) > 0) ? 1 : -1;
}

int end_comparator (line l1, line l2)
{
    if (l1.len == 0)
        return -1;
    
    if (l2.len == 0 && l1.len != 0)
        return 1;
    
    size_t p1 = l1.len - 1, p2 = l2.len - 1;

    p1 -= skip_bad_end (l1.string, l1.string + p1);
    p2 -= skip_bad_end (l2.string, l2.string + p2);
    
    while (my_tolower(l1.string[p1]) == my_tolower(l2.string[p2]))
    {
        if (p1 == 0 && p2 == 0)
            return (l1.len - l2.len > 0) ? 1 : -1;
        if ((p1 == 0 && p2 != 0) || (p1 != 0 && p2 == 0))
            return (my_tolower(l1.string[p1]) - my_tolower(l2.string[p2] > 0)) ? 1 : -1;
        
        p1--;
        p2--;
        p1 -= skip_bad_end (l1.string, l1.string + p1);
        p2 -= skip_bad_end (l2.string, l2.string + p2);

    }

    return (my_tolower(l1.string[p1]) - my_tolower(l2.string[p2]) > 0) ? 1 : -1;
}

int skip_bad_end (char* begin, char* str)
{
    int skip = 0;
    while (strchr (" ,.\t!?:;", *(str - skip)) != NULL && str - skip != begin)
        skip++; 

    return skip;
}

void bubblesort (line_array* array, int (*cmp_function) (line l1, line l2))
{
    int swaps = 1;
    
    while (swaps != 0)
    {
        swaps = 0;
        for(int i = 0; i < array->size; i++)
        {
            if (cmp_function (array->arr[i], array->arr[i+1]) > 0)
            {
                swap (array, i, i+1);
                swaps++;
            }
        }
    }
}

void swap (line_array* array, int i, int j)
{
    line temp = array->arr[i];
    array->arr[i] = array->arr[j];
    array->arr[j] = temp;
}

int my_tolower (char c)
{
    return (65 <= c && c <= 90) ? c + 32 : c;
}


int cmp (const void* a, const void* b)
{
    return start_comparator ((line*) a, (line*) b);
}