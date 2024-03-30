#include "wordle.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("USAGE: ./a.out file.txt\n");
        return 1;
    }

    wordlist_t wordlist = load_words(argv[1]);

    char answer[6];
    strcpy(answer, select_random_answer(wordlist));
    int num_tries = 0;
    char guess[6];

    printf("DEBUG - Answer: %s\n", answer);
    
    while (num_tries < MAX_TRIES)
    {
        printf("Enter your guess (%d left): ", MAX_TRIES - num_tries);
        fgets(guess, 6, stdin);
        while (getchar() != '\n');
        
        int num_correct = 0;
        char hint[6] = {0};

        for (int i = 0; i < 5; i++)
        {
            if (guess[i] == answer[i])
            {
                hint[i] = '^';
                num_correct++;
            }
            else
            {
                hint[i] = ' ';
            }
        }

        for (int i = 0; i < 5; i++)
        {
            if(hint[i] == ' ')
            {
                for (int j = 0; j < 5; j++)
                {
                    if ((guess[i] == answer[j]))
                    {
                        hint[i] = '*';
                        break;
                    }
                    
                }
                
            }
        }

        printf("\n");
        printf("%s\n", guess);
        printf("%s\n", hint);
        

        if(num_correct == 5)
        {
            printf("%s is correct!\n", answer);
            break;
        }

        num_tries++;
    }

    printf("\n");

    if (strcmp(guess, answer) != 0)
    {
        printf("Out of tries.\nCorrect Answer: %s.\nBetter luck next time.\n", answer);
    }
    
    for (int i = 0; i < wordlist.num_words; i++) {
        free(wordlist.words[i]);
    }
    free(wordlist.words);

    return 0;
}

wordlist_t load_words(char file[])
{
    FILE *fp = fopen(file, "r");
    wordlist_t wordlist = { 0 };

    if (!fp) {
        return wordlist;
    }

    char buffer[BUF_SIZE] = { 0 };
    int num_words = 0;


    while (fgets(buffer, BUF_SIZE, fp)) {
        trim(buffer);
        wordlist.words = realloc(wordlist.words, sizeof(void *) * (num_words + 1));
        wordlist.words[num_words] = malloc(strlen(buffer) + 1);
        strcpy(wordlist.words[num_words++], buffer);
    }

    wordlist.num_words = num_words;

    fclose(fp);

    return wordlist;

}

char* select_random_answer(wordlist_t wordlist)
{
    time_t t = time(NULL);
    srand(t);

    int max = wordlist.num_words - 1;
    int index = rand() % max;

    return wordlist.words[index];
}

void trim(char *str) {
    int l = strlen(str);

    if (str[l-1] == '\n') {
        str[l-1] = 0;
    }
}