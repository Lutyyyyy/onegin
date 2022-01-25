#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>


const int   String_size          = 1000;
const int   Number_of_strings    = 4000;
const int   Speaker_name_len     = 3;
const char* bad_symbols_string   = " ,.\t!?:;";


struct line
{
    char* string;
    int len;
};


//-----------------------------------------------------------------------------

char* Get_string (char* str, size_t String_size, FILE* file);

void bubblesort (struct line array[], int len, int (*cmp_function) (const struct line structure1, const struct line structure2));


int  skip_bad_start (const struct line structure);
int  start_ignoring_cmp (const struct line structure1, const struct line structure2);


int  skip_bad_end (const struct line structure);
int reverse_stricmp (const char* str1, int len_1,
                     const char* str2, int len_2);
int  end_ignoring_cmp (const struct line structure1, const struct line structure2);


void Space_cleaning (struct line structure);
void End_of_line_cleaning (struct line structure);
void Speaker_cleaning (struct line structure);


void generate_poem (const struct line array[], int number_of_strings, int number_of_quatrains);


void swap (struct line array[], int i, int j);

//-----------------------------------------------------------------------------


int main(int argc, char* argv[])
    {
    printf("argc = %d   argv[0] = %s    argv[1] = %s\n", argc, argv[0], argv[1]);

    FILE* Onegin = fopen ((argc == 1) ? "hamlet.txt" : argv[1], "r");


    static char strings[Number_of_strings][String_size] = {};
    struct line lines  [Number_of_strings] = {};


    int nStrings = 0;
    for ( ; nStrings < Number_of_strings; nStrings++)
        {
        char* line = Get_string (strings[nStrings], String_size - 1, Onegin);
        if (line == NULL)
            break;
        }

    for (int i = 0; i < nStrings; i++)
        {
        lines[i].string = strings[i];
        lines[i].len    = strlen (strings[i]);
        }


    for (int i = 0; i < nStrings; i++)
        printf("String #[%4d]: len = %3d,\t(%s)\n", i, lines[i].len, lines[i].string);

    printf("\n\n\n");


    bubblesort (lines, nStrings, 0 ?  start_ignoring_cmp :  end_ignoring_cmp);
//  bubblesort (lines, nStrings, 0 ? &start_ignoring_cmp : &end_ignoring_cmp);

    for (int i = 0; i < nStrings; i++)
        printf("Sorted #[%4d]: len = %3d,\t(%s)\n", i, lines[i].len, lines[i].string);


    generate_poem (lines, Number_of_strings, 10);


    fclose (Onegin);


//    getchar();

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

void bubblesort (struct line array[], int array_len, int (*cmp_function) (const struct line structure1, const struct line structure2))
    {

//    printf ("SORT START:\n");
//    for(int i = 0; i < array_len; i++)
//        printf("String #[%d] = (%s)\n", i, array[i]);
//    printf ("\n");

    int swaps = 1;
    while (swaps != 0)
        {
        swaps = 0;

        for(int i = 0; i < array_len - 1; i++)
            {
            assert (0 <= i && i < array_len - 1);
            assert (0 <= i + 1 && i + 1 < array_len);

//            printf ("i = %d: end_ignoring_cmp ('%s', '%s')...\n", i, array[i].string, array[i + 1].string);

            int res =   cmp_function  (array[i], array[i + 1]);
//          int res = (*cmp_function) (array[i], array[i + 1]);

//            printf ("i = %d: end_ignoring_cmp ('%s', '%s')... GOT %d\n", i, array[i].string, array[i + 1].string, res);

            if (res > 0)
                {
                swap (array, i, i + 1);
                swaps++;

//                printf ("... SWAPPED\n");
                }
//            printf ("\n\n");
            }
//        for(int i = 0; i < array_len; i++) printf("String #[%d] = (%s)\n", i, array[i].string);
//        printf ("\n");
        }

//    printf ("...SORT END\n\n");
    }

//-----------------------------------------------------------------------------

int start_ignoring_cmp (const struct line structure1, const struct line structure2)
    {
    return (stricmp ((char*) structure1.string + skip_bad_start (structure1),
                     (char*) structure2.string + skip_bad_start (structure2)));
    }

//-----------------------------------------------------------------------------

int skip_bad_start (const struct line structure)
    {
    int space_counter = 0, str_start = 0;
    int read = Speaker_name_len + 2;

    while (structure.string[space_counter] == ' ')
        space_counter++;
    str_start = space_counter;

    if (structure.string[str_start + Speaker_name_len] == '.' && structure.string[str_start + Speaker_name_len + 1] == ' ')
        str_start += read;

    return (str_start);
    }

//-----------------------------------------------------------------------------

int end_ignoring_cmp (const struct line structure1, const struct line structure2)
    {
    return (reverse_stricmp (structure1.string, skip_bad_end (structure1),
                             structure2.string, skip_bad_end (structure2)));
    }

//-----------------------------------------------------------------------------

int skip_bad_end (const struct line structure)
    {
    if (structure.len == 0)
        return 0;

    int symbols_counter = structure.len;
    while (strchr(bad_symbols_string, structure.string[symbols_counter]))
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

void Space_cleaning (struct line structure)
    {
    int space_counter = 0;
    while (structure.string[space_counter] == ' ' || structure.string[space_counter] == '\t')
        space_counter++;

    int i = 0;
    while (structure.string[space_counter + i] != '\0')
        {
        structure.string[i] = structure.string[space_counter + i];
        i++;
        }

    structure.string[i] = '\0';
    }

//-----------------------------------------------------------------------------

void End_of_line_cleaning (struct line structure)
    {
    int symbols_counter = structure.len - 1;
    while(structure.string[symbols_counter] == ' ' || structure.string[symbols_counter] == ',' || structure.string[symbols_counter] == '.' || structure.string[symbols_counter] == '\t'
       || structure.string[symbols_counter] == '!' || structure.string[symbols_counter] == '?' || structure.string[symbols_counter] == ':' || structure.string[symbols_counter] == ';')
        symbols_counter--;

    structure.string[symbols_counter + 1] = '\0';
    }

//-----------------------------------------------------------------------------

void Speaker_cleaning (struct line structure)
    {
    if (!(structure.string[Speaker_name_len] == '.' && structure.string[Speaker_name_len + 1] == ' '))
        return;

    int read = Speaker_name_len + 2;
    int write = 0;
    while (structure.string[read] != '\0')
        structure.string[write++] = structure.string[read++];

    structure.string[write] = '\0';
    }

//-----------------------------------------------------------------------------

void swap (struct line array[], int i, int j)
    {
    struct line temp = array[i];
    array[i] = array[j];
    array[j] = temp;
    }


//-----------------------------------------------------------------------------

void generate_poem (const struct line array[], int number_of_strings, int number_of_quatrains)
    {
    for (int j = 0; j < number_of_quatrains; j++)
        {
        int number_of_line = rand() % (number_of_strings - 4);

        for (int i = 0; i < 4; i++)
            {
            while (array[number_of_line].len < 2)
                number_of_line = rand() % (number_of_strings - 4);

            Space_cleaning (array[number_of_line + i]);
            printf("%s\n", array[number_of_line + i].string);
            }
        printf ("\n");
        }

    printf("\n@Ilya Mirkis feat. Shakespeare\n");
    }


















