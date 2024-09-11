#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
//#include <colorCodes.h>
#define shiftKey 19 // Shift key for Caesar cipher encryption/decryption



struct Credential {
    char website[50];  // Website name
    char username[35];  // Username
    char password[35];  // Encrypted password
};

// Function prototypes
int add(void);
int lookup(void);
int edit(void);
int delete(void);
int generate(int);
int printTitle(void);
void caesarCipher(char *text, int shift, int encrypt);
void disableEcho();
void enableEcho();


// Global variable for storing credentials
struct Credential cred;
FILE *PassFile;



// ANSI color codes
#define RED "\e[0;31m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define reset "\e[0m"


int main(void){

    

PassFile = fopen("PassC.txt", "a+");  // Open for appending and reading, create if it doesn't exist

if (PassFile == NULL) {
    printf("Error creating file!\n");
    exit(1);  //
}
    printTitle(); // Print title

    char choice;// User's choice variable

// Main loop
    while (1) {
        do {
            printf("Options:"
             "("BLU"A"reset")dd Password,"
              "("BLU"L"reset")ookup Password,"
               "("BLU"E"reset")dit Password,"
                "("BLU"D"reset")elete Password,"
                 "("BLU"G"reset")enerate Password,"
                  "("BLU"Q"reset")uit\n");

            printf(">> ");
            scanf(" %c", &choice);  //Scan choice and remove space before %c to ignore previous newline
            choice = tolower(choice);  // Convert to lowercase
        } while (choice != 'a' && choice != 'l' && choice != 'e' && choice != 'd' && choice != 'g' && choice != 'q');

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
            case 'g':
                printf(BLU"Welcome to the Password Generator!\n"reset);
                printf("You will reciev a Password made out of random Numbers, Letters and Special characters.\n");
                printf("Enter length of password: ");
                int len;
                scanf("%d", &len);
                generate(len);
                break;
            case 'q':
                printf("Thank you for using the Password Manager!\n");
                printf("See You soon! :D\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
    fclose(PassFile);
    
    return 0;
}

// Function to print the title
int printTitle(void){

    printf(CYN"      _____                                    _   __  __                                  \n");
    printf("     |  __ \\                                  | | |  \\/  |                                 \n");
    printf("     | |__) |_ _ ___ _____      _____  _ __ __| | | \\  / | __ _ _ __   __ _  __ _  ___ _ __ \n");
    printf("     |  ___/ _` / __/ __\\ \\ /\\ / / _ \\| '__/ _` | | |\\/| |/ _` | '_ \\ / _` |/ _` |/ _ \\ '__|\n");
    printf("     | |  | (_| \\__ \\__ \\\\ V  V / (_) | | | (_| | | |  | | (_| | | | | (_| | (_| |  __/ |   \n");
    printf("     |_|   \\__,_|___/___/ \\_/\\_/ \\___/|_|  \\__,_| |_|  |_|\___,_|_| |_|\\__,_|\\__,_|\\___|_|   \n");
    printf("                                                                             __/ |          \n");
    printf("                                                                            |___/           \n");
    printf(reset"\n");

    printf(YEL"Welcome to the Password Manager!\n"reset);
    printf("You can add, lookup, edit, delete and generate passwords.\n");
    printf("Press any key to continue...\n");  

    return 0;
}

// Function to add a new password
int add(void){


    printf("Enter website name: ");
    scanf("%s", cred.website);
    fprintf(PassFile, "Website: %s", cred.website);

    printf("Enter username: ");
    scanf("%s", cred.username);
    fprintf(PassFile, "|Username: %s", cred.username);


    printf("Enter password: ");
    disableEcho();  // Disable terminal echoing
    scanf("%s", cred.password);
    enableEcho();  // Enable terminal echoing
    caesarCipher(cred.password, shiftKey, 1); // Encrypt the password using Caesar cipher
    fprintf(PassFile, "|Password: %s\n", cred.password);

    fflush(PassFile); // Clear the file buffer

}

// Function to lookup a password
int lookup(void) {
 
}

// Function to edit a password
int edit(void){

}

// Function to delete a password
int delete(void){

}

// Function to generate a password
int generate(int len){
   char possibleChars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$^&*()";
   char password[len+1];
   
   srand(time(0)); // seed for random number generation
   for(int i = 0; i < len; i++) {
      int randomIndex = rand() % (sizeof(possibleChars) - 1);
      password[i] = possibleChars[randomIndex];
   }
   
   password[len] = '\0'; // null terminate the string
   printf("Generated Password: %s\n", password);
   return 0;
   }

// Function to encrypt or decrypt a string using Caesar cipher
void caesarCipher(char *text, int shift, int encrypt) {
    // Ensure the shift is within 0-25 for alphabetic characters and 0-9 for digits
    shift = shift % 26;
    int digitShift = shift % 10;

    // If decrypting, reverse the shift direction
    if (!encrypt) {
        shift = -shift;
        digitShift = -digitShift;
    }

    for (int i = 0; text[i] != '\0'; i++) {
        char ch = text[i];

        // Encrypt or decrypt uppercase letters
        if (isupper(ch)) {
            text[i] = (ch - 'A' + shift + 26) % 26 + 'A'; // Add 26 to ensure positive result
        }
        // Encrypt or decrypt lowercase letters
        else if (islower(ch)) {
            text[i] = (ch - 'a' + shift + 26) % 26 + 'a'; // Add 26 to ensure positive result
        }
        // Encrypt or decrypt digits
        else if (isdigit(ch)) {
            text[i] = (ch - '0' + digitShift + 10) % 10 + '0'; // Add 10 to ensure positive result
        }
        // Non-alphabetic and non-digit characters remain unchanged
    }
}

// Function to disable terminal echoing
void disableEcho() {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

// Function to enable terminal echoing
void enableEcho() {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}