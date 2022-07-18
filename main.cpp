#include <time.h>
#include "onegin.h"
#include "sorting_algs.h"


int main(/*const int argc, const char *argv[]*/)
{
    // if (argc < 2)
    time_t start, end;
    double cpu_time_used;
    start = clock();

    FILE* inputfile = fopen("hamlet.txt", "r");
    long int sz = file_size (inputfile);
    
    char* buffer = text_to_buf (inputfile);
    line_array* text_array = buf_to_line_arr (buffer, sz);
    fclose(inputfile); 
    
    FILE* sort = fopen ("sorted.txt", "w");

    print_title (sort, "SORTING FROM BEGINNING");
    line_array* begin_arr = copy_line_arr (text_array);
//    qsort         (begin_arr->arr, begin_arr->size, sizeof (line), start_comparator);
//    my_qsort      (begin_arr->arr, begin_arr->size, sizeof (line), start_comparator);  
    bubblesort    (begin_arr->arr, begin_arr->size, sizeof (line), start_comparator);
    print_lines_to_file (sort, begin_arr);
    print_title (sort, "FINISHED SORTING FROM BEGINNING");

    print_title (sort, "SORTING FROM ENDING");
    line_array* end_arr = copy_line_arr (text_array);
//    qsort         (end_arr->arr, end_arr->size, sizeof (line), end_comparator);
//    my_qsort      (end_arr->arr, end_arr->size, sizeof (line), end_comparator);  
    bubblesort    (end_arr->arr, end_arr->size, sizeof (line), end_comparator);
    print_lines_to_file (sort, end_arr);
    print_title (sort, "FINISHED SORTING FROM ENDING");

    print_title (sort, "ORIGINAL TEXT FROM BUFFER");
    fprintf (sort, "%s", buffer);
    print_title (sort, "END OF ORIGINAL TEXT FROM BUFFER");

    print_title (sort, "ORIGINAL TEXT FROM LINE ARRAY");
    print_lines_to_file (sort, text_array);
    print_title (sort, "END OF ORIGINAL TEXT FROM LINE ARRAY");

    fclose (sort);
    destruct_line_arr (begin_arr);
    destruct_line_arr (text_array); 
    destruct_line_arr (end_arr);
    free (buffer);
    
    
    end = clock();
    cpu_time_used = (float) (end - start) / CLOCKS_PER_SEC;
    printf ("\n%f\n", cpu_time_used);  
    
    return 0;
}