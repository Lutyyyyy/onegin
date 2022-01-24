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


void start_bubblesort(const char* array[], int len);

int  skip_bad_start (const char* str);
int  start_ignoring_cmp (const char* str1, const char* str2);


void end_bubblesort(const char* array[], int len);

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

    FILE* Onegin = fopen ((argc == 1) ? "iluxa.txt" : argv[1], "r");

    char strings[Number_of_strings][String_size] = {};
    const char* string_pointers[Number_of_strings] = {};

    int nStrings = 0;
    for ( ; nStrings < 2; nStrings++)
        {
        char* line = Get_string (strings[nStrings], String_size - 1, Onegin);
        if (line == NULL)
            break;
        }

    printf ("\nTEXT READ: nStrings = %d\n\n", nStrings);

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
//                        0000000000111111111122222222223333333333
//                        0123456789012345678901234567890123456789
    /*const char* str1 = "THE TRAGEDY OF HAMLET, PRINCE OF DENMARK";
    const char* str2 = "THE TRAGEDY OF HAMLET, PRINCE OF DENMARL";
    const char* str3 = "THE TRAGEDY OF HAMLET, PRINCE OF DENMARA";
    const char* str4 = "  Claudius, King of Denmark.";
    const char* arr[] = {str1, str2, str3, str4};*/

    /*const char* arr2[] = {"",
                        "",
                        "",
                        "",
                        "                    Enter Horatio and Marcellus.  ",
                        "    If you do meet Horatio and Marcellus,",
                        "",
                        "    And let us hear Bernardo speak of this.",
                        "    And let us once again assail your ears,",
                        "    Touching this dreaded sight, twice seen of us.",
                        "  Ber. Welcome, Horatio. Welcome, good Marcellus."};

    end_bubblesort (arr2, 11);
    for (int i = 0; i < 11; i++)
        {
        printf("String #[%d] = (%s)\n", i, arr2[i]);
        }*/


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

void start_bubblesort (const char* array[], int len)
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

void end_bubblesort (const char* array[], int len)
    {
    printf ("SORT START:\n");
    for(int i = 0; i < len; i++) printf("String #[%d] = (%s)\n", i, array[i]);
    printf ("\n");

    int swaps = 1;
    while (swaps != 0)
        {
        swaps = 0;

        for(int i = 0; i < len - 1; i++)
            {
            assert (0 <= i && i < len - 1);
            assert (0 <= i + 1 && i + 1 < len);

            printf ("i = %d: end_ignoring_cmp ('%s', '%s')...\n", i, array[i], array[i + 1]);

            int res = end_ignoring_cmp (array[i], array[i + 1]);

            printf ("i = %d: end_ignoring_cmp ('%s', '%s')... GOT %d", i, array[i], array[i + 1], res);

            if (res > 0)
                {
                swap (array, i, i + 1);
                swaps++;

                printf ("... SWAPPED");
                }

            printf ("\n\n");
            }

        for(int i = 0; i < len; i++) printf("String #[%d] = (%s)\n", i, array[i]);
        printf ("\n");
        }

    printf ("...SORT END\n\n");
    }

//-----------------------------------------------------------------------------

int end_ignoring_cmp (const char* str1, const char* str2)
    {
    //printf("Kekw");

    int bebra = reverse_stricmp (str1, skip_bad_end (str1, strlen(str1)),
                                 str2, skip_bad_end (str2, strlen(str2)));
    //printf("DED NEPRAW");
    return bebra;
    }

//-----------------------------------------------------------------------------

int skip_bad_end (const char* str, int len)
    {
    if (len == 0)
        return 0;

    int symbols_counter = len;
    printf("symbols_counter before = %d\n", symbols_counter);
    while (strchr(bad_symbols_string, str[symbols_counter]))
        symbols_counter--;

    printf("symbols_counter after = %d", symbols_counter);
    return symbols_counter;
    }

//-----------------------------------------------------------------------------

int reverse_stricmp (const char* str1, int len_1,
                     const char* str2, int len_2)
    {
    fprintf(stderr, "ALLO");

    assert (str1 != NULL);
    assert (str2 != NULL);

    int i_1 = len_1, i_2 = len_2;

    fprintf(stderr, ">>> i_1 = %d, i_2 = %d, str1[] = '%c', str2[] = '%c'\n", i_1, i_2, str1[i_1], str2[i_2]);

    while (i_1 >= 0 && i_2 >= 0 && tolower(str1[i_1]) == tolower(str2[i_2]))
        {
        fprintf (stderr, "!!! i_1 = %d, i_2 = %d\n", i_1, i_2);

        if (i_1 == 0 || i_2 == 0)
            return (tolower(str1[i_1]) - tolower(str2[i_2]));

        i_1--;
        i_2--;
        }

    fprintf(stderr, "MENYA SLIWNO?");

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

void swap (const char* array[], int i, int j)
    {
    const char* temp = array[i];
    array[i] = array[j];
    array[j] = temp;
    }

//-----------------------------------------------------------------------------




