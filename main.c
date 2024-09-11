#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>

struct Credential {
    char website[50];  // Website name
    char username[35];  // Username
    char password[35];  // Encrypted password
};

int add(void);
int lookup(void);
int edit(void);
int delete(void);

struct Credential cred;
FILE *PassFile;


int main(void){

    

    PassFile = fopen("PassC.txt", "rb+");

    if(PassFile == NULL) // If file does not exist, create it
    {
        PassFile = fopen("PassC.txt", "wb");
        if (PassFile == NULL) {
            printf("Error creating file!\n");
            exit(1);  // Exit if file creation fails
        }
    }
    
    printf("Hello and Welcome to the Password Manager\n");


  char choice;

    do {
        printf("Options: (A)dd Password, (L)ookup Password, (E)dit Password, (D)elete Password, (Q)uit\n");
        scanf(" %c", &choice);  // Notice the space before %c to ignore previous newline
        choice = tolower(choice);  // Convert to lowercase
    } while (choice != 'a' && choice != 'l' && choice != 'e' && choice != 'd' && choice != 'q');

    switch(choice) {
        case 'a':
            add();
            break;
        case 'l':
            lookup();
            break;
        case 'e':
            edit();
            break;
        case 'd':
            delete();
            break;
        case 'q':
            printf("Thank you for using the Password Manager!\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
    }
    fclose(PassFile);
    
    return 0;
}

int add(void){

    printf("Enter website name: ");
    scanf("%s", cred.website);
    fwrite(&cred, sizeof(struct Credential), 1, PassFile);

    printf("Enter username: ");
    scanf("%s", cred.username);

    printf("Enter password: ");
    scanf("%s", cred.password);
}

int lookup(void){

    printf("Enter website name: ");
}

int edit(void){

}

int delete(void){

}