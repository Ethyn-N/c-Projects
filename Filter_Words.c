#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 4) {
        printf("USAGE: ./a.out list output letter\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");
    char letter = *argv[3];

    if (!fp) {
        return 1;
    }

    if(!output){
        return 1;
    }

    char buffer[10] = { 0 };

    while (fgets(buffer, 10, fp))
    {
        for (int i = 0; buffer[i] != '\0'; i++)
        {
            if(buffer[i] == letter)
            {
                fprintf(output,"%s", buffer);
                break;
            }
        }
    }

    fclose(fp);
    fclose (output);

    return 0;
}