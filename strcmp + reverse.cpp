#include <stdio.h>
#include <string.h>
#include <assert.h>

int Strcmp (const char* str1, const char* str2);
int reverse_strcmp (const char* str1, const char* str2);



int main()
    {
    const char* string[] = {"", "", "reAnvperf", "re"};
    int res = reverse_strcmp (string[2], string[3]);

    printf ("reverse_strcmp = %d", res);

    return 0;
    }


int Strcmp (const char* str1, const char* str2)
    {
    assert (str1 != NULL);
    assert (str2 != NULL);

    int i = 0;
    while (str1[i] == str2[i] && str1[i] != '\0')
        i++;

    return (str1[i] - str2[i]);
    }


//-----------------------------------------------------------------------------

int reverse_strcmp (const char* str1, const char* str2)
    {
    assert (str1 != NULL);
    assert (str2 != NULL);

    int i_1 = strlen (str1) - 1, i_2 = strlen (str2) - 1;

    while (i_1 >= 0 && i_2 >= 0 && str1[i_1] == str2[i_2])
        {
        if (i_1 == 0 || i_2 == 0)
            return (str1[i_1] - str2[i_2]);

        i_1--;
        i_2--;
        }

    return (str1[i_1] - str2[i_2]);
    }


int skip_bad_end (char* str, int len)
    {
    int symbols_counter = len - 1;

    if(strchr(str, bad_s))
            break;
       symbols_counter--;
    }


char* bad_symbols_string = " ,.\t!?:;"


