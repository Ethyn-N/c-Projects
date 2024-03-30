#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE 128

void cat_string(char str1[], char str2[]);

int main()
{
    char str1[ARRAY_SIZE], str2[ARRAY_SIZE];

    printf("Enter first string: ");
    fgets(str1, ARRAY_SIZE, stdin);

    printf("Enter second string: ");
    fgets(str2, ARRAY_SIZE, stdin);

    cat_string(str1, str2);

    return 0;
}

void cat_string(char str1[], char str2[])
{
    int i, j;
    int consonants_1 = 0;
    int consonants_2 = 0;
    int size = (strlen(str1)-1) + (strlen(str2)-1);
    char str3[size];

    for (i = 0; i < strlen(str1)-1; i++)
    {
        switch (str1[i])
        {
            case 'A': case 'E': case 'I': case 'O': case 'U': break;
            case 'a': case 'e': case 'i': case 'o': case 'u': break;
            case 'Y': case 'y':
                if (i == 0)
                {
                    consonants_1++;
                    break;
                }
            default: consonants_1++;     
        }
    }

    for (i = 0; i < strlen(str2)-1; i++)
    {
        switch (str2[i])
        {
            case 'A': case 'E': case 'I': case 'O': case 'U': break;
            case 'a': case 'e': case 'i': case 'o': case 'u': break;
            case 'Y': case 'y':
                if (i == 0)
                {
                    consonants_2++;
                    break;
                }
            default: consonants_2++;     
        }
    }

    if (consonants_1 >= consonants_2)
    {
        for (i = 0; i < strlen(str1)-1; i++)
        {
            str3[i] = str1[i];
        }
        for (j = i; j < (strlen(str2)-1) + i; j++)
        {
            str3[j] = str2[j - i];
        }
    }
    else
    {
        for (i = 0; i < strlen(str2)-1; i++)
        {
            str3[i] = str2[i];
        }
        for (j = i; j < (strlen(str1)-1) + i; j++)
        {
            str3[j] = str1[j - i];
        }
    }

    for (i = 0; i < size; i++)
    {
        printf("%c", str3[i]);
    }
    printf("\n");
}
