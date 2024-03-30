#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 64

void Swap(char str[]);

int main()
{
    int i;
    int index_1, index_2;
    char str[LENGTH];
    char temp[1];
    
    printf("Enter a string (up to %d characters): ", LENGTH);
    fgets(str, sizeof(str) + 1, stdin);
    
    printf("Enter index 1: ");
    scanf("%d", &index_1);
    
    printf("Enter index 2: ");
    scanf("%d", &index_2);
    
    if((index_1 >= strlen(str) || index_1 < 0) && (index_2 >= strlen(str) || index_2 < 0))
    {
        printf("Indices 1 and 2 are out of bounds. Please type valid indices next time.\n");
        return 3;
    }
       
    if(index_1 >= strlen(str) || index_1 < 0)
    {
        printf("Index 1 out of bounds. Please type a valid index next time.\n");
        return 1;
    }
    else if(index_2 >= strlen(str) || index_2 < 0)
    {
        printf("Index 2 out of bounds. Please type a valid index next time.\n");
        return 2;
    }
    
    temp[0] = str[index_1];
    str[index_1] = str[index_2];
    str[index_2] = temp[0];
    
    for(i = 0; i < strlen(str); i++)
    {
        printf("%c", str[i]);
    }
    
    printf("\n");

    return 0;

}
