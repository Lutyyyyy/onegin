#include <stdio.h>
#include <string.h>
#include <assert.h>



char* Strchr (char* str, char sym);

int main()
    {
    char stroka[] = "qwerty890";
    int position = 6;
    char * symbol = Strchr (stroka, '9');

    if (symbol == NULL)
        printf ("Error: symbol has NULL address\n");

    if ((symbol - stroka) != position)
        printf ("Error: symbol's position = %d does not match with reference = %d\n", symbol - stroka, position);

    printf("bebra");
    return 0;
    }


char* Strchr (char* str, char sym)
    {
    assert (str != NULL);

    for (int i = 0; str[i] != '\0'; i++)
        if (sym == str[i])
            return &(str[i]);

    return NULL;
    }
