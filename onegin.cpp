#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>


const int String_size          = 1000;
const int Number_of_strings    = 100;
const int Speaker_name_len     = 3;
const char* bad_symbols_string = " ,.\t!?:;";


//-----------------------------------------------------------------------------

char* Get_string (char* str, size_t String_size, FILE* file);


void start_bubblesort(char* array[], int len);

int  skip_bad_start (const char* str);
int  start_ignoring_cmp (const char* str1, const char* str2);


void end_bubblesort(char* array[], int len);

int  skip_bad_end (const char* str, int len);
int  reverse_stricmp (const char* str1, int len_1,
                      const char* str2, int len_2);
int  end_ignoring_cmp (char* str1, int len1,
                       char* str2, int len2);


void Space_cleaning (char* str);
void End_of_line_cleaning (char* str);
void Speaker_cleaning (char* str);


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

        //Space_cleaning (line);
        //End_of_line_cleaning (line);
        //Speaker_cleaning (line);
        }

    for (int i = 0; i < nStrings; i++)
        string_pointers[i] = (char*) &strings[i];

    for (int i = 0; i < nStrings; i++)
        {
        printf("String #[%d] = (%s)\n", i, string_pointers[i]);
        }

    printf("\n\n\n");

    end_bubblesort (string_pointers, nStrings);

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

void start_bubblesort (char* array[], int len)
    {
    int swaps = 1;
    while (swaps != 0)
        {
        swaps = 0;

        for(int i = 0; i < len - 1; i++)
            {
            assert (0 <= i && i < len - 1);
            assert (0 <= i + 1 && i + 1 < len);

            if (start_ignoring_cmp (array[i], array[i + 1]) > 0)
                {
                swap (array, i, i + 1);
                swaps++;
                }
            }
        }
    }

//-----------------------------------------------------------------------------

int start_ignoring_cmp (const char* str1, const char* str2)
    {
    return (stricmp (str1 + skip_bad_start (str1), str2 + skip_bad_start (str2)));
    }

//-----------------------------------------------------------------------------

int skip_bad_start (const char* str)
    {
    int space_counter = 0, str_start = 0;
    int read = Speaker_name_len + 2;

    while (str[space_counter] == ' ')
        space_counter++;
    str_start = space_counter;

    if (str[str_start + Speaker_name_len] == '.' && str[str_start + Speaker_name_len + 1] == ' ')
        str_start += read;

    return (str_start);
    }

//-----------------------------------------------------------------------------

void end_bubblesort (char* array[], int len)
    {
    int swaps = 1;
    while (swaps != 0)
        {
        swaps = 0;

        for(int i = 0; i < len - 1; i++)
            {
            assert (0 <= i && i < len - 1);
            assert (0 <= i + 1 && i + 1 < len);

            if (end_ignoring_cmp (array[i],     strlen (array[i]),
                                  array[i + 1], strlen (array[i + 1])) > 0)
                {
                swap (array, i, i + 1);
                swaps++;
                }
            }
        }
    }

//-----------------------------------------------------------------------------

int end_ignoring_cmp (char* str1, int len1,
                      char* str2, int len2)
    {
    return (reverse_stricmp (str1, len1 - skip_bad_end (str1, len1),
                             str2, len2 - skip_bad_end (str2, len2)));
    }

//-----------------------------------------------------------------------------

int skip_bad_end (const char* str, int len)
    {
    int symbols_counter = len - 1;
    while (strchr(bad_symbols_string, str[symbols_counter]))
        symbols_counter--;
    return symbols_counter;
    }

//-----------------------------------------------------------------------------

int reverse_stricmp (const char* str1, int len_1,
                     const char* str2, int len_2)
    {
    assert (str1 != NULL);
    assert (str2 != NULL);

    int i_1 = len_1 - 1, i_2 = len_2 - 1;

    while (i_1 >= 0 && i_2 >= 0 && tolower(str1[i_1]) == tolower(str2[i_2]));
        {
        if (i_1 == 0 || i_2 == 0)
            return (tolower(str1[i_1]) - tolower(str2[i_2]));

        i_1--;
        i_2--;
        }

    return (tolower(str1[i_1]) - tolower(str2[i_2]));
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

void swap (char* array[], int i, int j)
    {
    char* temp = array[i];
    array[i] = array[j];
    array[j] = temp;
    }

//-----------------------------------------------------------------------------



