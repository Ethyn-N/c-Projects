#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE 16

int half = ARRAY_SIZE/2;

float Addtraction(float array_1[], float array_2[], int size);

int main()
{
    int i = 0;
    int j = 0;
    float array_1[half];
    float array_2[half];
    float result;

    printf("Enter up to %d numbers separated by a space: ", ARRAY_SIZE);
    for(i = 0; i < ARRAY_SIZE; i++)
    {
        if(i < half)
        {
            fscanf(stdin, "%f", &array_1[i]);
        }
        else
        {
            fscanf(stdin, "%f", &array_2[j++]);
        }
    }

    result = Addtraction(array_1, array_2, half);
    
    printf("%.f\n", result);

    return 0;
}

float Addtraction(float array_1[], float array_2[], int size)
{
    float result;
    int i, temp, num1, num2;
    
    for(i = 0; i < size; i++)
    {
        temp = array_1[i] + array_2[i];
        
        num1 = (int)array_1[i];
        num2 = (int)array_2[i];
        
        if(num1 % 2 == 0 || num2 % 2 == 0)
        {
            result -= temp;
        }
        else
        {
            result += temp;
        }
        
    }
   
    return result;
}
















