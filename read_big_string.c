#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 8

void trim(char *str) {
    int l = strlen(str);
    if (str[l-1] == '\n') {
        str[l-1] = 0;
    }
}

int main() {
    char *str = NULL;
    char buffer[BUF_SIZE] = { 0 };

    printf("Enter a string of any size: ");

    while (fgets(buffer, BUF_SIZE, stdin)) {
        trim(buffer);
        long bl = strlen(buffer);
        long sl = str ? strlen(str) : 0;

        // TODO: Allocate memory properly for this

        if (strlen(buffer) == 0)
        {
            str = malloc((sl * 2) + 1);
            strcpy(str, buffer);
        }
        else
        {
            str = malloc((bl * 2) + 1);
            strcpy(str, buffer);
        }
        

        strcat(str, buffer);

        if (strlen(buffer) < BUF_SIZE - 1) {
            break;
        }
    }

    printf("%s has %ld characters. Wow!\n", str, strlen(str));

    free(str);

    return 0;
}
