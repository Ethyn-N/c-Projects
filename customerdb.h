#ifndef CUSTOMERDB_H
#define CUSTOMERDB_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 500

typedef struct {
    int ID;
    char *Name;
    char *Address;
    char *E_mail;
} customer_t;

int read_csv(char file[], customer_t ***data);
char *read_string(FILE *fp);
void display_data(customer_t ***data, int customers);
int add_entry(customer_t ***data, int num_customers);
void save_csv(customer_t ***data, int num_customers);
void save_binary(customer_t ***data, int num_customers);
void load_binary(char *file, customer_t ***data, int *num_customers);
int read_binary(char* file, customer_t ***data);
void free_data(customer_t **data, int customers);
void trim(char *str);
int input();
void choice(int num, char file[], customer_t ***data, int *custormers);
#endif