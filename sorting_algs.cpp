#include "sorting_algs.h"


int skip_bad_start (const char* str)
{
    int skip = 0;
    while (strchr (" ,.\t!?:;", *(str + skip)) != NULL && *(str + skip) != '\0')
        skip++; 

    return skip;
}

int start_comparator (const void* el1, const void* el2)
{
    line* l1 = (line*) el1;
    line* l2 = (line*) el2;
    
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


int skip_bad_end (char* begin, char* str)
{
    int skip = 0;
    while (strchr (" ,.\t!?:;", *(str - skip)) != NULL && str - skip != begin)
        skip++; 

    return skip;
}

int end_comparator (const void* el1, const void* el2)
{
    line* l1 = (line*) el1;
    line* l2 = (line*) el2;

    if (l1->len == 0)
        return -1;
    
    else if (l2->len == 0 && l1->len != 0)
        return 1;
    
    size_t p1 = l1->len - 1, p2 = l2->len - 1;

    p1 -= skip_bad_end (l1->string, l1->string + p1);
    p2 -= skip_bad_end (l2->string, l2->string + p2);
    
    while (my_tolower(l1->string[p1]) == my_tolower(l2->string[p2]))
    {
        if (p1 == 0 || p2 == 0)
            return (l1->len - l2->len > 0) ? 1 : -1;
        
        p1--;
        p2--;

        p1 -= skip_bad_end (l1->string, l1->string + p1);
        p2 -= skip_bad_end (l2->string, l2->string + p2);
    } 

    return (my_tolower(l1->string[p1]) - my_tolower(l2->string[p2]) > 0) ? 1 : -1;
}


void my_qsort (void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{

    if (nmemb < 2)
        return;

    char* start = (char*) base;
    int pos = partition_alg (base, nmemb, size, compar);
  
    my_qsort (base, pos, size, compar);
    my_qsort (start + (pos + 1) * size, nmemb - pos - 1, size, compar);
}

int partition_alg (void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    char* start = (char*) base;
    void* pivot = start + (nmemb - 1) * size;
    size_t el_to_swap = 0, current_num = 0;
    for ( ; current_num < nmemb - 1; current_num++)
    {
        if (compar (start + current_num * size, pivot) <= 0)
        {
            swap (start + el_to_swap * size, start + current_num * size, size);
            el_to_swap++;
        }
    }

    swap (start + el_to_swap * size, pivot, size);
    return el_to_swap;
}

void swap (void *pa, void *pb, size_t size) //spizdil s interneta
{
    char *a = (char*) pa;
    char *b = (char*) pb;
    while (size--) 
    {
        char tmp = *a;
        *a++ = *b;
        *b++ = tmp;
    }
}


void bubblesort (void* base, size_t nmemb, size_t size, int (*compar) (const void* , const void* ))
{
    size_t swaps = 1;
    char* start = (char*) base;
    
    while (swaps != 0)
    {
        swaps = 0;
        for(int i = 0; i < nmemb - 1; i++)
        {
            if (compar (start + i * size, start + (i + 1) * size) > 0)
            {
                swap (start + i * size, start + (i + 1) * size, size);
                swaps++;
            }
        }
//        printf ("%ld\n", swaps);
    }
}

int my_tolower (char c)
{
    return (65 <= c && c <= 90) ? c + 32 : c;
}
