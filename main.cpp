#include <time.h>
#include "onegin.h"
#include "sorting_algs.h"


int main()
{
    time_t start, end;
    double cpu_time_used;
    start = clock();

    FILE* inputfile = fopen("hamlet.txt", "r");
    long int sz = file_size (inputfile);
    
    char* buffer = text_to_buf (inputfile);
    char* original = (char*) calloc (sz + 1, sizeof (char));
    strcpy (original, buffer);

    line_array* array = buf_to_line_arr (buffer, sz);
    fclose(inputfile); 
    
    FILE* sort = fopen ("sorted.txt", "w");

    print_title (sort, "SORTING FROM BEGINNING");
//    qsort         (array->arr, array->size, sizeof (line), start_comparator);
//    my_qsort      (array->arr, array->size, sizeof (line), start_comparator);  
    bubblesort     (array->arr, array->size, sizeof (line), start_comparator);
    print_lines_to_file (sort, array);
    print_title (sort, "FINISHED SORTING FROM BEGINNING");

    print_title (sort, "SORTING FROM ENDING");
//    qsort         (array->arr, array->size, sizeof (line), end_comparator);
    my_qsort      (array->arr, array->size, sizeof (line), end_comparator);  
//    bubblesort    (array->arr, array->size, sizeof (line), end_comparator);
    print_lines_to_file (sort, array);
    print_title (sort, "FINISHED SORTING FROM ENDING");

    print_title (sort, "ORIGINAL TEXT");
    fprintf (sort, "%s", original);
    print_title (sort, "END OF ORIGINAL TEXT");


    fclose (sort);
    destruct_line_arr (array); 
    free (buffer);
    free (original);
    
    
    end = clock();
    cpu_time_used = (float) (end - start) / CLOCKS_PER_SEC;
    printf ("\n%f\n", cpu_time_used);  
    
    return 0;
}