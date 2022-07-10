#include "onegin.h"

int         skip_bad_start      (const char* str);
int         start_comparator    (const void* el1, const void* el2);

int         skip_bad_end        (char* begin, char* str);
int         end_comparator      (const void* el1, const void* el2);


void        my_qsort            (void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
int         partition_alg       (void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
void        swap                (void *pa, void *pb, size_t size);


void        bubblesort          (void* base, size_t nmemb, size_t size, int (*compar) (const void* , const void* ));
int         my_tolower          (char c);