#ifndef CUSTOMERQUEUE_H
#define CUSTOMERQUEUE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 500

typedef struct customer customer_t;
struct customer {
    int ID;
    char *Name;
    char *Address;
    char *E_mail;
};

typedef struct node Node_t;
struct node {
    void *data;
    Node_t *next;
    Node_t *prev;
};

Node_t *load_csv(char file[], int *num_customers, Node_t **head, Node_t **tail, int *total_count);
void display_data(Node_t **tail);
Node_t *create_node(void *data);
void process_customer(Node_t **head, Node_t **tail, int *num_customers);
void free_list(Node_t **head);
void choice(int num, char file[], int *customers, Node_t **head, Node_t **tail, int *total_count);
int input();
void trim(char *str);


#endif