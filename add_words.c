#include <stdio.h>
#include <string.h>

#define BUF_SIZE 64
#define MAX_WORDS 10

void trim(char *str) {
    int len = strlen(str);
    if (str[len-1] == '\n') {
        str[len-1] = 0;
    }
}

void print_words(char words[][BUF_SIZE], int num_words) {
    for (int i = 0; i < num_words; i++) {
        printf("words[%d] = %s\n", i, words[i]);
    }
}

// TODO: Implement `add_to_list` in order to complete the task.

void add_to_list(char words[][BUF_SIZE], char buffer[], int *num_words)
{
    if(*num_words >= MAX_WORDS)
        return;

    strcpy(words[*num_words], buffer);
    (*num_words)++;
}

int main() {
    char buffer[BUF_SIZE] = { 0 };
    char words[MAX_WORDS][BUF_SIZE] = { 0 };
    int num_words = 0;

    while (num_words < MAX_WORDS) {
        printf("Enter a string: ");
        fgets(buffer, BUF_SIZE, stdin);
        trim(buffer);

        // You may modify this call, but no other code in `main`.
        add_to_list(words, buffer, &num_words);
    }

    print_words(words, num_words);

    return 0;
}
