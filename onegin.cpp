#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>


const int String_size       = 1000;
const int Number_of_strings = 1000;
const int Speaker_name_len  = 3;


//-----------------------------------------------------------------------------

char* Get_string (char* str, size_t String_size, FILE* file);
void Space_cleaning (char* str);
void End_of_line_cleaning (char* str);
void Speaker_cleaning (char* str);
void bubblesort(char* array[], int len);
void swap (char* array[], int i, int j);

//-----------------------------------------------------------------------------


int main(int argc, char* argv[])
    {
    printf("argc = %d   argv[0] = %s    argv[1] = %s\n", argc, argv[0], argv[1]);

    FILE* Onegin = fopen ((argc == 1) ? "hamlet.txt" : argv[1], "r");

    char strings[Number_of_strings][String_size] = {};
    char* string_pointers[Number_of_strings] = {};

    int nStrings = 0;
    for ( ; nStrings < Number_of_strings; nStrings++)
        {
        char* line = Get_string (strings[nStrings], String_size - 1, Onegin);
        if (line == NULL)
            break;

        Space_cleaning (line);
        End_of_line_cleaning (line);
        Speaker_cleaning (line);
        }

    for (int i = 0; i < nStrings; i++)
        string_pointers[i] = (char*) &strings[i];

    for (int i = 0; i < nStrings; i++)
        {
        printf("String #[%d] = (%s)\n", i, string_pointers[i]);
        }

    printf("\n\n\n");

    bubblesort (string_pointers, nStrings);

    for (int i = 0; i < nStrings; i++)
        {
        printf("String #[%d] = (%s)\n", i, string_pointers[i]);
        }




    fclose (Onegin);


    getchar();

    return 0;
    }


//-----------------------------------------------------------------------------

char* Get_string (char* str, size_t size, FILE* file)
    {
    char* NULL_check = fgets (str, size - 1, file);
    if (NULL_check == NULL)
        return NULL;

    char* eol = strchr (str, '\n');
    if(eol != NULL)
        *eol = '\0';

    return str;
    }

//-----------------------------------------------------------------------------

void Space_cleaning (char* str)
    {
    int space_counter = 0;
    while (str[space_counter] == ' ' || str[space_counter] == '\t')
        space_counter++;

    int i = 0;
    while (str[space_counter + i] != '\0')
        {
        str[i] = str[space_counter + i];
        i++;
        }

    str[i] = '\0';
    }

//-----------------------------------------------------------------------------

void End_of_line_cleaning (char* str)
    {
    int symbols_counter = strlen(str) - 1;
    while(str[symbols_counter] == ' ' || str[symbols_counter] == ',' || str[symbols_counter] == '.' || str[symbols_counter] == '\t'
       || str[symbols_counter] == '!' || str[symbols_counter] == '?' || str[symbols_counter] == ':' || str[symbols_counter] == ';')
        symbols_counter--;

    str[symbols_counter + 1] = '\0';
    }

//-----------------------------------------------------------------------------

void Speaker_cleaning (char* str)
    {
    if (!(str[Speaker_name_len] == '.' && str[Speaker_name_len + 1] == ' '))
        return;

    int read = Speaker_name_len + 2;
    int write = 0;
    while (str[read] != '\0')
        str[write++] = str[read++];

    str[write] = '\0';
    }

//-----------------------------------------------------------------------------

void bubblesort(char* array[], int len)
    {
    int swaps = 1;
    while (swaps != 0)
        {
        swaps = 0;

        for(int i = 0; i < len - 1; i++)
            {
            assert (0 <= i && i < len - 1);
            assert (0 <= i + 1 && i + 1 < len);

            if (stricmp ((array[i]), (array[i + 1])) > 0)
                {
                swap (array, i, i + 1);
                swaps++;
                }
            }
        }
    }

//-----------------------------------------------------------------------------

void swap (char* array[], int i, int j)
    {
    char* temp = array[i];
    array[i] = array[j];
    array[j] = temp;
    }

//-----------------------------------------------------------------------------






