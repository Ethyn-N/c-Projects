#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE 64

void reverse_half(char str[]);

int main()
{
    char str[ARRAY_SIZE];
    printf("Enter a string: ");
    fgets(str, ARRAY_SIZE, stdin);
   
    reverse_half(str);
}

void reverse_half(char str[])
{
    int i, j, half = 0;
    char temp;
    int length = strlen(str)-1;
    
    if (((strlen(str)-1) % 2) == 0)
    {
        half = length/2;
    }
    else
    {
        half = (length/2) + 1;
    }

    j = half-1;

    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;

        i++;
        j--;
    }
    
    for (i = 0; i < strlen(str)-1; i++)
    {
        printf("%c", str[i]);
    }

    printf("\n");
}