#include <stdio.h>

#define ARRAY_SIZE 32

void find_numbers(int array[], int start, int end, int size);

int main()
{
    int i, args, size, start, end;
    int array[ARRAY_SIZE];
    char x;

    printf("Enter your numbers (MAX %d): ", ARRAY_SIZE);
    for (i = 0; i < ARRAY_SIZE; i++)
    {
        args = scanf("%d", &array[i]);
        size = ARRAY_SIZE;

        if (args < 1)
        {
            size = i;
            while ((x = getchar()) != EOF && x != '\n');
            break;
        }   
    }

    printf("Enter a range: ");
    do
    {
       args = scanf("%d %d", &start, &end);
       if (args < 2)
       {
           while ((x = getchar()) != EOF && x != '\n');
           printf("Invalid inuput. Please input an integer range: ");
       }   
    } while (args < 2);
    
    while (start > end)
    {
        printf("Invalid range. Starting point is greater than end point. Please input a valid range: ");
    do
    {
       args = scanf("%d %d", &start, &end);
       if (args < 2)
       {
           while ((x = getchar()) != EOF && x != '\n');
           printf("Invalid inuput. Please input an integer range: ");
       }   
    } while (args < 2);

    }

    find_numbers(array, start, end, size);
    
    return 0;
}

void find_numbers(int array[], int start, int end, int size)
{
    int check = 0;
    for (int i = 0; i < size; i++)
    {
        if (array[i] >= start && array[i] <= end)
        {
            printf("Index: %d Value: %d\n", i, array[i]);
            check = 1;
        }    
    }

    if (check != 1)
    {
        printf("No indices found with given range.\n");
    }
       
}