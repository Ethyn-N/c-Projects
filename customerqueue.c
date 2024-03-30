#include "customerqueue.h"


int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("USAGE: ./a.out file\n");
        return 1;
    }

    Node_t *head = NULL;
    Node_t *tail = NULL;

    printf("\n1. Load CSV File\n2. Process Next\n3. View Queue\n4. Quit\nEnter Selection: ");

    int num_customers = 0;
    int total_count = 0;

    choice(input(), argv[1], &num_customers, &head, &tail, &total_count);

    free_list(&head);

    return 0;
}

Node_t *load_csv(char file[], int *num_customers, Node_t **head, Node_t **tail, int *total_count)
{
    char *point = file + strlen(file);
    if((point = strrchr(file,'.')) != NULL )
    {
        if(strcmp(point,".csv") != 0)
         {
             printf("Warning: Not CSV file. Please use correct file format.\n");
             return NULL;
         }
    }
    
    printf("\n");

    char buffer[BUF_SIZE] = { 0 };

    FILE *fp = fopen(file, "r+");

    int starting_num = 0;
    
    if(*num_customers > 0)
    {
        for (int i = 0; i < *total_count; i++)
        {
            fgets(buffer, BUF_SIZE, fp);
        }
        
    }
    

    while (fgets(buffer, BUF_SIZE, fp) && *num_customers < 10) {
        trim(buffer);

        if (buffer[0] == '\0')
        {
            continue;
        }
        

        int token_count = 0;

        for(int i = 0; i < strlen(buffer); i++)
        {
            if(buffer[i] == ',')
            {
                token_count++;
            }   
        }

        if (token_count != 3)
        {
            continue;
        }


        customer_t *new_node = calloc(1, sizeof(customer_t));
        

        char *token = strtok(buffer, ",");
        int num_feature = 0;
        
        while (token) {
            switch (num_feature) {
                case 0:
                    new_node->ID = atoi(token);
                    break;
                case 1:
                    new_node->Name = malloc(strlen(token) + 1);
                    strcpy(new_node->Name, token);
                    break;
                case 2:
                    new_node->Address = malloc(strlen(token) + 1);
                    strcpy(new_node->Address, token);
                    break;
                case 3:
                    new_node->E_mail = malloc(strlen(token) + 1);
                    strcpy(new_node->E_mail, token);
                    break;
                default:
                    printf("no\n");
        }
        num_feature++;
        token = strtok(NULL, ",");
    }

    Node_t *n = create_node(new_node);

    n->next = *head;

    if (*head != NULL) {
        (*head)->prev = n;
    } else {
        *tail = n;
    }

    (*head) = n;


    (*num_customers)++;
    starting_num++;
    (*total_count)++;      

    }

    fclose(fp);

    if (starting_num > 0)
    {
        printf("Loaded %d customers\n", starting_num);
    }
    
    return *head;
}

void process_customer(Node_t **head, Node_t **tail, int *num_customers)
{
    customer_t *c = (*tail)->data;

    printf("Processing customer...\n");
    printf("%-10d", c->ID);
    printf("%-25s", c->Name);
    printf("%-30s", c->Address);
    printf("%-25s", c->E_mail);
    printf("\n");

    if (*head == *tail) {
        free(c->Name);
        free(c->Address);
        free(c->E_mail);
        free(c);
        free((*tail));
        *head = NULL;
        *tail = NULL;
    } else {
        Node_t *prev = (*tail)->prev;
        prev->next = NULL;

        free(c->Name);
        free(c->Address);
        free(c->E_mail);
        free(c);
        free((*tail));

        *tail = prev;

    }

    (*num_customers)--;
}

void display_data(Node_t **tail)
{
    int i = 0;
    Node_t *temp = (*tail);
    customer_t *tail_data = (*tail)->data;
    printf("Current Queue\n=============\n");
    while (*tail != NULL)
    {
        tail_data = (*tail)->data;
        printf("%-5d", i++ + 1);
        printf("%-10d", tail_data->ID);
        printf("%-25s", tail_data->Name);
        printf("%-30s", tail_data->Address);
        printf("%-25s", tail_data->E_mail);
        printf("\n");

        (*tail) = (*tail)->prev;
    }
    (*tail) = temp;
}

Node_t *create_node(void *data) {
    Node_t *n = calloc(1, sizeof(Node_t));
    n->data = data;

    return n;
}



void free_list(Node_t **head) {
	Node_t *prev = *head;
	Node_t *cur = *head;
	while (cur) {
		prev = cur;
        customer_t *prev_data = cur->data;
		cur = prev->next;
        free(prev_data->Name);
        free(prev_data->Address);
        free(prev_data->E_mail);
		free(prev_data);
        free(prev);
	}
}

void choice(int num, char file[], int *num_customers, Node_t **head, Node_t **tail, int *total_count)
{
    char x;
    while(1)
    {
        printf("\n");

        switch (num) {
        case 1:
            while ((x = getchar()) != EOF && x != '\n');
            if (*num_customers != 0)
            {
                printf("Data already loaded.\n");
                printf("\n1. Load CSV File\n2. Process Next\n3. View Queue\n4. Quit\nEnter Selection: ");
                num = input();
                break;
            }
            else
            {
                load_csv(file, num_customers, head, tail, total_count);
                printf("\n1. Load CSV File\n2. Process Next\n3. View Queue\n4. Quit\nEnter Selection: ");
                num = input();
                break;
            }
            break;
        case 2:
             while ((x = getchar()) != EOF && x != '\n');
             if (*tail == NULL)
             {
                printf("Warning: no customers in queue\n");
                printf("\n1. Load CSV File\n2. Process Next\n3. View Queue\n4. Quit\nEnter Selection: ");
                num = input();
                break;
             }
             else
             {
                if (*num_customers > 0)
                {
                    process_customer(head, tail, num_customers);
                }
                
                if (*num_customers < 5 && *num_customers > 0)
                {
                    load_csv(file, num_customers, head, tail, total_count);
                }
                printf("\n1. Load CSV File\n2. Process Next\n3. View Queue\n4. Quit\nEnter Selection: ");
                num = input();
                break;
             } 
            break;
        case 3:
            while ((x = getchar()) != EOF && x != '\n');
            if (*num_customers <= 0)
            {
                printf("No data loaded.\n");
                printf("\n1. Load CSV File\n2. Process Next\n3. View Queue\n4. Quit\nEnter Selection: ");
                num = input();
                break;
            }        
            display_data(tail);
            printf("\n1. Load CSV File\n2. Process Next\n3. View Queue\n4. Quit\nEnter Selection: ");
            num = input();
            break;
        case 4:
            while ((x = getchar()) != EOF && x != '\n');
            printf("Goodbye...\n");
            free_list(head);
            exit(0);
            break;
        default:
            while ((x = getchar()) != EOF && x != '\n');
            printf("Invalid choice. Try again\n");
            printf("\n1. Load CSV File\n2. Process Next\n3. View Queue\n4. Quit\nEnter Selection: ");
            num = input();
            break;
        }
    }
    
}


void trim(char *str) {
    int l = strlen(str);

    if (str[l-1] == '\n') {
        str[l-1] = 0;
    }
}

int input() {
    int number, args;
    char x;
    do
    {
        args = scanf("%d", &number);
        if (args < 1)
       {
           while ((x = getchar()) != EOF && x != '\n');
           printf("\nInvalid choice. Try again\n");
           printf("\n1. Load CSV File\n2. Process Next\n3. View Queue\n4. Quit\nEnter Selection: ");
       }   
    } while (args < 1);
    
    return (number);
}