#include "customerdb.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("USAGE: ./a.out file\n");
        return 1;
    }

    printf("1. Load CSV File\n2. Load Binary File\n3. Display Data\n4. Add Entry\n5. Export as CSV\n6. Export as Binary\n7. Quit\nEnter Selection: ");

    customer_t **data = NULL;
    int customers = 0;

    choice(input(), argv[1], &data, &customers);

    return 0;

}

int read_csv(char file[], customer_t ***data)
{
    char *point = file + strlen(file);
    if((point = strrchr(file,'.')) != NULL )
    {
        if(strcmp(point,".csv") != 0)
         {
             printf("Warning: Not CSV file. Please use correct file format.\n");
             return 0;
         }
    }
    

    char buffer[BUF_SIZE] = { 0 };
    int num_customers = 0;


    FILE *fp = fopen(file, "r+");

    while (fgets(buffer, BUF_SIZE, fp)) {
        trim(buffer);

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

        *data = realloc(*data, (num_customers + 1) * sizeof(customer_t*));
        (*data)[num_customers] = calloc(1, sizeof(customer_t));

        char *token = strtok(buffer, ",");
        int num_feature = 0;
        
        while (token) {
            switch (num_feature) {
                case 0:
                    (*data)[num_customers]->ID = atoi(token);
                    //printf("ID[%d]: %d\n", num_customers, (*data)[num_customers]->ID);
                    break;
                case 1:
                    (*data)[num_customers]->Name = malloc(strlen(token) + 1);
                    strcpy((*data)[num_customers]->Name, token);
                    //printf("Name[%d]: %s\n", num_customers, (*data)[num_customers]->Name);
                    break;
                case 2:
                    (*data)[num_customers]->Address = malloc(strlen(token) + 1);
                    strcpy((*data)[num_customers]->Address, token);
                    //printf("Address[%d]: %s\n", num_customers, (*data)[num_customers]->Address);
                    break;
                case 3:
                    (*data)[num_customers]->E_mail = malloc(strlen(token) + 1);
                    strcpy((*data)[num_customers]->E_mail, token);
                    //printf("Email[%d]: %s\n", num_customers, (*data)[num_customers]->E_mail);
                    break;
                default:
                    printf("no\n");
        }
        num_feature++;
        token = strtok(NULL, ",");
    }

    num_customers++;      

    }

    fclose(fp);

    printf("csv data loaded\n");

    return num_customers;
}

char *read_string(FILE *fp)
{
    long p = ftell(fp);

    int count = 0;
    while (fgetc(fp))
    {
        count++;
    }

    char *str = calloc(count + 1, sizeof(char));
    fseek(fp,p,SEEK_SET);
    fread(str, sizeof(char), count + 1, fp);

    return str;
    
}

customer_t *read_entry(FILE *fp)
{
    customer_t *c = calloc(1, sizeof(customer_t));
    

    fread(&c->ID, 1, sizeof(int), fp);
    if (feof(fp))
    {   
        free(c);
        return NULL;
    }
    
    c->Name = read_string(fp);
    c->Address = read_string(fp);
    c->E_mail = read_string(fp);

    return c;
}

void load_binary(char *file, customer_t ***data, int *num_customers)
{
    FILE *fp = fopen(file, "rb");

    int signature_1;
    int signature_2;
    

    fread(&signature_1, sizeof(signature_1), 1, fp);
    if (signature_1 != 0x13)
    {
        printf("Warning: File does not have 1st signature.\n");
        fclose(fp);
        return;
    }
    

    fread(&signature_2, sizeof(signature_2), 1, fp);
    if (signature_2 != 0x20)
    {
        printf("Warning: File does not have 2nd signature.\n");
        fclose(fp);
        return;
    }

    while (1)
    {
        customer_t *temp = read_entry(fp);
        
        if (temp)
        {
            *data = realloc(*data, (*num_customers + 1) * sizeof(customer_t*));
            (*data)[(*num_customers)] = temp;
            // printf("\nID[%d]: %d\n", *num_customers, (*data)[*num_customers]->ID);
            // printf("Name[%d]: %s\n", *num_customers, (*data)[*num_customers]->Name);
            // printf("Address[%d]: %s\n", *num_customers, (*data)[*num_customers]->Address);
            // printf("E-mail[%d]: %s\n", *num_customers, (*data)[*num_customers]->E_mail);
            (*num_customers)++;
            //printf("customers: %d\n", *num_customers);
        }
        else
        {
            free(temp);
            fclose(fp);
            printf("Binary data loaded\n");
            return;
        }
        
    }
    
}

void display_data(customer_t ***data, int customers)
{
    for (int i = 0; i < customers; i++)
    {
        printf("%-10d", (*data)[i]->ID);
        printf("%-25s", (*data)[i]->Name);
        printf("%-30s", (*data)[i]->Address);
        printf("%-25s", (*data)[i]->E_mail);
        printf("\n");
    }
}

int add_entry(customer_t ***data, int num_customers)
{
    *data = realloc(*data, (num_customers + 1) * sizeof(customer_t*));
    (*data)[num_customers] = calloc(1, sizeof(customer_t));
    char temp[BUF_SIZE];

    printf("Enter new customer data\n");

    printf("ID: ");
    scanf("%d", &(*data)[num_customers]->ID);
    while (getchar() != '\n');

    printf("Name: ");
    fgets(temp, BUF_SIZE, stdin);
    trim(temp);
    (*data)[num_customers]->Name = malloc(strlen(temp) + 1);
    strcpy((*data)[num_customers]->Name, temp);

    printf("Address: ");
    fgets(temp, BUF_SIZE, stdin);
    trim(temp);
    (*data)[num_customers]->Address = malloc(strlen(temp) + 1);
    strcpy((*data)[num_customers]->Address, temp);
   
    printf("E-mail: ");
    fgets(temp, BUF_SIZE, stdin);
    trim(temp);
    (*data)[num_customers]->E_mail = malloc(strlen(temp) + 1);
    strcpy((*data)[num_customers]->E_mail, temp);
  
    printf("\nUser Added!\n");

    return num_customers + 1;
}

void save_csv(customer_t ***data, int num_customers)
{
    char buffer[BUF_SIZE] = { 0 };
    printf("Enter file name for data to be stored: ");
    fgets(buffer, BUF_SIZE, stdin);
    trim(buffer);
    FILE *fp = fopen(buffer, "r");
    if (fp == NULL)
    {
        fp = fopen(buffer, "w+");
        for (int i = 0; i < num_customers; i++)
        {
            if (i != num_customers - 1)
            {
                fprintf(fp,"%d,", (*data)[i]->ID);
                fprintf(fp,"%s,", (*data)[i]->Name);
                fprintf(fp,"%s,", (*data)[i]->Address);
                fprintf(fp,"%s", (*data)[i]->E_mail);
                fprintf(fp,"\n");
            }
            else
            {
                fprintf(fp,"%d,", (*data)[i]->ID);
                fprintf(fp,"%s,", (*data)[i]->Name);
                fprintf(fp,"%s,", (*data)[i]->Address);
                fprintf(fp,"%s", (*data)[i]->E_mail);
            }
            
        }
        printf("\n");
        printf("csv data saved\n");
        fclose(fp);
    }
    else
    {
        printf("File already exists. Would you like to overwrite? (y/n): ");
        char answer = fgetc(stdin);

        switch (answer) 
        {
        case 'y': case 'Y':
            fclose(fp);
            fp = fopen(buffer, "w+");
            for (int i = 0; i < num_customers; i++)
            {
                if (i != num_customers - 1)
                {
                    fprintf(fp,"%d,", (*data)[i]->ID);
                    fprintf(fp,"%s,", (*data)[i]->Name);
                    fprintf(fp,"%s,", (*data)[i]->Address);
                    fprintf(fp,"%s", (*data)[i]->E_mail);
                    fprintf(fp,"\n");
                }
                else
                {
                    fprintf(fp,"%d,", (*data)[i]->ID);
                    fprintf(fp,"%s,", (*data)[i]->Name);
                    fprintf(fp,"%s,", (*data)[i]->Address);
                    fprintf(fp,"%s", (*data)[i]->E_mail);
                }
            }
            printf("\n");
            printf("csv data saved\n");
            fclose(fp);
            break;
        case 'n': case 'N':
            while (getchar() != '\n');
            fclose(fp);
            save_csv(data, num_customers);
            break;
        default:
            while (getchar() != '\n');
            printf("Invalid answer\n");
            fclose(fp);
            save_csv(data, num_customers);
        }
    
    }
}

void save_binary(customer_t ***data, int num_customers)
{
    char buffer[BUF_SIZE] = { 0 };
    printf("Enter file name for data to be stored: ");
    fgets(buffer, BUF_SIZE, stdin);
    FILE *fp = fopen(buffer, "rb");
    trim(buffer);
    int signature_1 = 0x13;
    int signature_2 = 0x20;

    if (fp == NULL)
    {
        fp = fopen(buffer, "wb");
        fwrite(&signature_1, sizeof(signature_1), 1, fp);
        fwrite(&signature_2, sizeof(signature_2), 1, fp);

        for (int i = 0; i < num_customers; i++)
        {
            fwrite(&(*data)[i]->ID, sizeof((*data)[i]->ID), 1, fp);
            fwrite((*data)[i]->Name, sizeof(char), strlen((*data)[i]->Name) + 1, fp);
            fwrite((*data)[i]->Address, sizeof(char), strlen((*data)[i]->Address) + 1, fp);
            fwrite((*data)[i]->E_mail, sizeof(char), strlen((*data)[i]->E_mail) + 1, fp);
        }
        printf("\n");
        printf("Binary data saved\n");
        fclose(fp);
    }
    else
    {
        printf("File already exists. Would you like to overwrite? (y/n): ");
        char answer = fgetc(stdin);

        switch (answer) 
        {
        case 'y': case 'Y':
            fclose(fp);
            fp = fopen(buffer, "wb");
            fwrite(&signature_1, sizeof(signature_1), 1, fp);
            fwrite(&signature_2, sizeof(signature_2), 1, fp);
            for (int i = 0; i < num_customers; i++)
            {
                fwrite(&(*data)[i]->ID, sizeof((*data)[i]->ID), 1, fp);
                fwrite((*data)[i]->Name, sizeof(char), strlen((*data)[i]->Name) + 1, fp);
                fwrite((*data)[i]->Address, sizeof(char), strlen((*data)[i]->Address) + 1, fp);
                fwrite((*data)[i]->E_mail, sizeof(char), strlen((*data)[i]->E_mail) + 1, fp);
            }
            printf("\n");
            printf("Binary data saved\n");
            fclose(fp);
            break;
        case 'n': case 'N':
            while (getchar() != '\n');
            fclose(fp);
            save_binary(data, num_customers);
            break;
        default:
            while (getchar() != '\n');
            printf("Invalid answer\n");
            fclose(fp);
            save_binary(data, num_customers);
        }
    
    }
}

void choice(int num, char file[], customer_t ***data, int *customers)
{
    char x;
    while(1)
    {
        printf("\n");
        
        switch (num) {
        case 1:
            while ((x = getchar()) != EOF && x != '\n');
            if (*customers == 0)
            {
                *customers = read_csv(file, data);
                printf("\n1. Load CSV File\n2. Load Binary File\n3. Display Data\n4. Add Entry\n5. Export as CSV\n6. Export as Binary\n7. Quit\nEnter Selection: ");
                num = input();
            }
            else
            {
                printf("Data already loaded.\n");
                printf("\n1. Load CSV File\n2. Load Binary File\n3. Display Data\n4. Add Entry\n5. Export as CSV\n6. Export as Binary\n7. Quit\nEnter Selection: ");
                num = input();
            } 
            break;
        case 2:
             while (getchar() != '\n');
             if (*customers == 0)
             {
                load_binary(file, data, customers);
                printf("\n1. Load CSV File\n2. Load Binary File\n3. Display Data\n4. Add Entry\n5. Export as CSV\n6. Export as Binary\n7. Quit\nEnter Selection: ");
                num = input();
             }
             else
             {
                printf("Data already loaded.\n");
                printf("\n1. Load CSV File\n2. Load Binary File\n3. Display Data\n4. Add Entry\n5. Export as CSV\n6. Export as Binary\n7. Quit\nEnter Selection: ");
                num = input();
             } 
            break;
        case 3:
            while (getchar() != '\n');
            if (*customers == 0)
            {
                printf("No data loaded.\n");
                display_data(data, *customers);
                printf("\n1. Load CSV File\n2. Load Binary File\n3. Display Data\n4. Add Entry\n5. Export as CSV\n6. Export as Binary\n7. Quit\nEnter Selection: ");
                num = input();
                break;
            }        
            display_data(data, *customers);
            printf("\n1. Load CSV File\n2. Load Binary File\n3. Display Data\n4. Add Entry\n5. Export as CSV\n6. Export as Binary\n7. Quit\nEnter Selection: ");
            num = input();
            break;
        case 4:
            while (getchar() != '\n');
            *customers = add_entry(data, *customers);
            printf("\n1. Load CSV File\n2. Load Binary File\n3. Display Data\n4. Add Entry\n5. Export as CSV\n6. Export as Binary\n7. Quit\nEnter Selection: ");
            num = input();
            break;
        case 5:
            while (getchar() != '\n');
            if (*customers == 0)
            {
                printf("Warning: No data loaded. Must load data before saving.\n");
                printf("\n1. Load CSV File\n2. Load Binary File\n3. Display Data\n4. Add Entry\n5. Export as CSV\n6. Export as Binary\n7. Quit\nEnter Selection: ");
                num = input();
                break;
            }        
            save_csv(data, *customers);
            printf("\n1. Load CSV File\n2. Load Binary File\n3. Display Data\n4. Add Entry\n5. Export as CSV\n6. Export as Binary\n7. Quit\nEnter Selection: ");
            num = input();
            break;
        case 6:
            while (getchar() != '\n');
            if (*customers == 0)
            {
                printf("Warning: No data loaded. Must load data before saving.\n");
                printf("\n1. Load CSV File\n2. Load Binary File\n3. Display Data\n4. Add Entry\n5. Export as CSV\n6. Export as Binary\n7. Quit\nEnter Selection: ");
                num = input();
                break;
            }       
            save_binary(data, *customers);
            printf("\n1. Load CSV File\n2. Load Binary File\n3. Display Data\n4. Add Entry\n5. Export as CSV\n6. Export as Binary\n7. Quit\nEnter Selection: ");
            num = input();
            break;
        case 7:
            while (getchar() != '\n');
            printf("Goodbye...\n");
            free_data(*data, *customers);
            exit(0);
            break;
        default:
            while (getchar() != '\n');
            printf("Invalid choice. Try again\n");
            printf("\n1. Load CSV File\n2. Load Binary File\n3. Display Data\n4. Add Entry\n5. Export as CSV\n6. Export as Binary\n7. Quit\nEnter Selection: ");
            num = input();
            break;
        }
    }
    
}

void free_data(customer_t **data, int customers)
{
    for (int i = 0; i < customers; i++) {
        free((data)[i]->Name);
        free((data)[i]->Address);
        free((data)[i]->E_mail);
        free(data[i]);
    }
    free(data);
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
           printf("\n1. Load CSV File\n2. Load Binary File\n3. Display Data\n4. Add Entry\n5. Export as CSV\n6. Export as Binary\n7. Quit\nEnter Selection: ");
       }   
    } while (args < 1);
    
    return (number);
}


void trim(char *str) {
    int l = strlen(str);

    if (str[l-1] == '\n') {
        str[l-1] = 0;
    }
}