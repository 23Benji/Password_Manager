#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>
#include <ANSI-color-codes.h>

struct Credential {
    char website[50];  // Website name
    char username[35];  // Username
    char password[35];  // Encrypted password
};

int add(void);
int lookup(void);
int edit(void);
int delete(void);
int printTitle(void);

// Global variable for storing credentials
struct Credential cred;
#define RED "\e[0;31m"
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
    
    printTitle(); // Print title




  char choice;

    do {
        printf(RED"Options: (A)dd Password, (L)ookup Password, (E)dit Password, (D)elete Password, (Q)uit\n");
        printf(">> ");
        scanf(" %c", &choice);  //Scan choice and remove space before %c to ignore previous newline
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
            printf("See You soon! :D\n");

            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
    }
    fclose(PassFile);
    
    return 0;
}

int printTitle(void){

    printf("      _____                                    _   __  __                                  \n");
    printf("     |  __ \\                                  | | |  \\/  |                                 \n");
    printf("     | |__) |_ _ ___ _____      _____  _ __ __| | | \\  / | __ _ _ __   __ _  __ _  ___ _ __ \n");
    printf("     |  ___/ _` / __/ __\\ \\ /\\ / / _ \\| '__/ _` | | |\\/| |/ _` | '_ \\ / _` |/ _` |/ _ \\ '__|\n");
    printf("     | |  | (_| \\__ \\__ \\\\ V  V / (_) | | | (_| | | |  | | (_| | | | | (_| | (_| |  __/ |   \n");
    printf("     |_|   \\__,_|___/___/ \\_/\\_/ \\___/|_|  \\__,_| |_|  |_|\___,_|_| |_|\\__,_|\\__,_|\\___|_|   \n");
    printf("                                                                             __/ |          \n");
    printf("                                                                            |___/           \n");
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