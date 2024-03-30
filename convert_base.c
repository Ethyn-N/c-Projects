#include <stdio.h>

#define TRUE 1
#define FALSE 0

void convert_base(int num);

int isInteger(double val);

int main()
{
    int args;
    char x;
    float num;

    printf("Enter an integer: ");
    args = scanf("%f", &num);
    if (args < 1)
    {
        while ((x = getchar()) != EOF && x != '\n');
        printf("Invalid inuput\n");
        return 1;      
    }
    if (isInteger(num) == FALSE)
    {
        while ((x = getchar()) != EOF && x != '\n');
        printf("Invalid inuput\n");
        return 2;       
    }

    convert_base((int)num);
}

void convert_base(int num)
{
    int i, j;
    int remainder;
    char remainder_array[100];

    while (num > 0)
    {
        remainder = num % 16;
        if (remainder < 10)
            remainder_array[j++] = remainder + 48;
        else
            remainder_array[j++] = remainder + 55;
        
        num/=16;
    }

    for (i = j; i >= 0; i--)
    {
        printf("%c", remainder_array[i]);
    }

    printf("\n");
}

int isInteger(double val)
{
    int truncated = (int)val;
    if (val == truncated)
        return TRUE;
    else
        return FALSE;
}