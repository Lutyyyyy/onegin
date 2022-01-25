#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>


const int String_size          = 1000;
const int Number_of_strings    = 50;
const int Speaker_name_len     = 3;
const char* bad_symbols_string = " ,.\t!?:;";


struct line
{
    char string[String_size];
    int len;
};


//-----------------------------------------------------------------------------

char* Get_string (char* str, size_t String_size, FILE* file);

void bubblesort (const char* array[], int len, int (*cmp) (const char*, const char*));


int  skip_bad_start (const char* str);
int  start_ignoring_cmp (const char* str1, const char* str2);


int  skip_bad_end (const char* str, int len);
int  reverse_stricmp (const char* str1, int len_1,
                      const char* str2, int len_2);
int  end_ignoring_cmp (const char* str1, const char* str2);


void Space_cleaning (char* str);
void End_of_line_cleaning (char* str);
void Speaker_cleaning (char* str);


void swap (const char* array[], int i, int j);

//-----------------------------------------------------------------------------


int main(int argc, char* argv[])
    {
    printf("argc = %d   argv[0] = %s    argv[1] = %s\n", argc, argv[0], argv[1]);

    FILE* Onegin = fopen ((argc == 1) ? "hamlet.txt" : argv[1], "r");

    static struct line lines[Number_of_strings] = {};
    const char* line_pointers[Number_of_strings] = {};

    //static char strings[Number_of_strings][String_size] = {};
    //const char* string_pointers[Number_of_strings] = {};

    int nStrings = 0;
    for ( ; nStrings < Number_of_strings; nStrings++)
        {
        char* line = Get_string ((lines[nStrings]).string, String_size - 1, Onegin);
        if (line == NULL)
            break;
        (lines[nStrings]).len = strlen(line);
        }

    for (int i = 0; i < nStrings; i++)
        line_pointers[i] = (lines[i]).string;

    for (int i = 0; i < nStrings; i++)
        printf("String #[%d] = (%s)\n", i, (lines[i]).string);

    printf("\n\n\n");


    bubblesort (line_pointers, nStrings, *(0 ? start_ignoring_cmp : end_ignoring_cmp));


    for (int i = 0; i < nStrings; i++)
        printf("String #[%d] = (%s)\n", i, line_pointers[i]);

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

void bubblesort (const char* array[], int len, int (*cmp) (const char*, const char*))
    {
    int swaps = 1;
    while (swaps != 0)
        {
        swaps = 0;

        for(int i = 0; i < len - 1; i++)
            {
            assert (0 <= i && i < len - 1);
            assert (0 <= i + 1 && i + 1 < len);

            int res = (*cmp) (array[i], array[i + 1]);
            if (res > 0)
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

int end_ignoring_cmp (const char* str1, const char* str2)
    {
    return (reverse_stricmp (str1, skip_bad_end (str1, strlen(str1)),
                                 str2, skip_bad_end (str2, strlen(str2))));
    }

//-----------------------------------------------------------------------------

int skip_bad_end (const char* str, int len)
    {
    if (len == 0)
        return 0;

    int symbols_counter = len;
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

    int i_1 = len_1, i_2 = len_2;
    while (i_1 >= 0 && i_2 >= 0 && tolower(str1[i_1]) == tolower(str2[i_2]))
        {
        if (i_1 == 0 || i_2 == 0)
            return (tolower(str1[i_1]) - tolower(str2[i_2]));

        i_1--;
        i_2--;
        }

    return (tolower(str1[i_1]) - tolower(str2[i_2]));
    }
//-----------------------------------------------------------------------------

void swap (const char* array[], int i, int j)
    {
    const char* temp = array[i];
    array[i] = array[j];
    array[j] = temp;
    }




















