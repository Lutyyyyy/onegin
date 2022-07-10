#include "onegin.h"
#include "sorting_algs.h"


int main()
{
    FILE* file = fopen("hamlet.txt", "r");
    line_array* array = construct_line_arr (file);
    fclose(file); 
    
    FILE* sort = fopen ("sorted.txt", "w");
    
    print_title (sort, "ORIGINAL TEXT");
    print_lines_to_file (sort, array);
    print_title (sort, "END OF ORIGINAL TEXT");

    print_title (sort, "SORTING FROM BEGINNING");
    qsort         (array->arr, array->size, sizeof (line), start_comparator);
//    my_qsort      (array->arr, array->size, sizeof (line), start_comparator);  
//    bubblesort    (array->arr, array->size, sizeof (line), start_comparator);
    print_lines_to_file (sort, array);
    print_title (sort, "FINISHED SORTING FROM BEGINNING");

    print_title (sort, "SORTING FROM ENDING");
    qsort         (array->arr, array->size, sizeof (line), end_comparator);
//    my_qsort      (array->arr, array->size, sizeof (line), end_comparator);  
//    bubblesort    (array->arr, array->size, sizeof (line), end_comparator);
    print_lines_to_file (sort, array);

    fclose (sort);

    destruct_line_arr (array);   
    return 0;
}