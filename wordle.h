#ifndef WORDLE_H
#define WORDLE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define BUF_SIZE 10
#define MAX_TRIES 6

typedef struct {
    char **words;
    int num_words;
} wordlist_t;

void trim(char *str);
wordlist_t load_words(char file[]);
char* select_random_answer(wordlist_t wordlist);

#endif