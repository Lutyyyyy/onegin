#include <stdio.h>
#include <string.h>


const int String_size       = 1000;
const int Number_of_strings = 1000;
const int Speaker_name_len  = 3;


//-----------------------------------------------------------------------------

char* Get_string (char* str, size_t String_size, FILE* file);
void Space_cleaning (char* str);
void End_of_line_cleaning (char* str);
void Speaker_cleaning (char* str);

//-----------------------------------------------------------------------------


int main()
    {
    FILE* Onegin = fopen ("hamlet.txt", "r");

    char strings[Number_of_strings][String_size] = {};

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
        {
        printf("String #[%d] = (%s)\n", i, strings[i]);
        }




    fclose (Onegin);
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

    int i = Speaker_name_len + 2;
    while (str[i] != '\0')
        {
        str[i - Speaker_name_len - 2] = str[i];
        i++;
        }

    str[i - Speaker_name_len - 2] = '\0';
    }







