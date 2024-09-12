#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#include<termios.h>
#include<unistd.h>
//#include <colorCodes.h>
#define shiftKey 19 // Shift key for Caesar cipher encryption/decryption
#define MAX_LINE_LENGTH 256 // Maximum length of a line in the input file




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
int generate(void);
int printTitle(void);
void caesarCipher(char *text, int shift, int encrypt);
void disableEcho();
void enableEcho();
int pressAnyKey(void);


// Global variable for storing credentials
struct Credential cred;
FILE *PassFile;



// ANSI color codes
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
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
    char choice;// User's choice variable

// Main loop
    while (1) {
        do {
            system("clear");  // Clear the screen
            printTitle();  // Print the title
            printf(YEL"\n\nWelcome to the Password Manager!--Version 1.0--\n\n"reset);

            printf(RED"Please select an option:"reset"\n\n");
            printf(BLU"  @\n");
            printf("  |\n");
            printf("-[1]--Add Password\n");
            printf("  |\n");
            printf("-[2]--Lookup Password\n");
            printf("  |\n");
            printf("-[3]--Edit Password\n");
            printf("  |\n");
            printf("-[4]--Delete Password\n");
            printf("  |\n");
            printf("-[5]--Generate Password\n");
            printf("  |\n");
            printf("  |\n"reset);
            printf(RED"-[00]--Exit\n"reset);
            printf(BLU"  |\n");            
            printf("  @\n"reset);

            printf("-[");
            scanf(" %c", &choice);  //Scan choice and remove space before %c to ignore previous newline
        } while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '0');

        switch(choice) {
            case '1':
                add();
                fflush(stdin);  // Clear the input buffer
                break;
            case '2':
                lookup();
                fflush(stdin);  // Clear the input buffer                
                break;
            case '3':
                edit();
                fflush(stdin);  // Clear the input buffer
                break;
            case '4':
                delete();
                fflush(stdin);  // Clear the input buffer
                break;
            case '5':
                generate();
                fflush(stdin);  // Clear the input buffer
                break;
            case '0':
                system("clear");  // Clear the screen
                printTitle();  // Print the title
                printf(GRN"\n\n❤ Thank you for using the Password Manager!\n");
                printf("See You soon! :D\n"reset);
                return 0;
            default:
                printf(RED"Invalid choice. Please try again.\n"reset);
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
    printf("                                                                            |___/      By: Benji Paun     \n");
    printf(reset"\n");

    return 0;
}

// Function to add a new password
int add(void) {
    char line[MAX_LINE_LENGTH];
    char choice;

    // Ask the user for the website name
    printf("Enter website name: ");
    scanf("%s", cred.website);

    // Rewind the file to the beginning for checking
    rewind(PassFile);

    // Check if the website already exists
    while (fgets(line, MAX_LINE_LENGTH, PassFile) != NULL) {
        char *websitePos = strstr(line, "Website: ");
        if (websitePos != NULL) {
            websitePos += 9;  // Move 9 characters forward to the website name

            char websiteInLine[50];
            sscanf(websitePos, "%[^|]", websiteInLine);

            if (strcmp(websiteInLine, cred.website) == 0) {
                // If the website is already found
                printf(RED"\nWebsite '%s' already exists!\n"reset, cred.website);
                
                 printf("Try another Website? (y/n)\n>>");
                char choice;
                scanf(" %c", &choice);
                if(tolower(choice) == 'y'){
                    add();
                }else{
                    return 0;
                }
                
 
                
                
            }
        }
    }

    // If the website does not exist, proceed to add the new credential
    printf("Enter username: ");
    scanf("%s", cred.username);
    fprintf(PassFile, "Website: %s|Username: %s", cred.website, cred.username);

    printf("Enter password: ");
    disableEcho();  // Disable terminal echoing
    scanf("%s", cred.password);
    enableEcho();  // Enable terminal echoing
    caesarCipher(cred.password, shiftKey, 1);  // Encrypt the password using Caesar cipher
    fprintf(PassFile, "|Password: %s\n", cred.password);

    fflush(PassFile);  // Flush the file buffer

    printf(GRN"\nPassword added successfully!\n"reset);
    return(pressAnyKey());
}


// Function to lookup a password
int lookup(void) {
    char searchWebsite[50];  // Website to search for
    char line[MAX_LINE_LENGTH];  // Buffer to store each line from the file

    // Ask the user for the website name
    printf("Enter the website name: ");
    scanf("%s", searchWebsite);

    // Rewind the file to the beginning
    rewind(PassFile);

    // Loop through each line in the file
    while (fgets(line, MAX_LINE_LENGTH, PassFile) != NULL) {
        // Look for the website in the line
        char *websitePos = strstr(line, "Website: ");
        if (websitePos != NULL) {
            // Move 9 characters forward (to the website name itself)
            websitePos += 9;

            // Extract the website name until the first '|'
            char websiteInLine[50];
            sscanf(websitePos, "%[^|]", websiteInLine);

            // Compare the website name
            if (strcmp(websiteInLine, searchWebsite) == 0) {
                // Find the position of the password
                char *passwordPos = strstr(line, "Password: ");
                if (passwordPos != NULL) {
                    // Move 10 characters forward to get the encrypted password
                    passwordPos += 10;

                    // Extract the password until the end of the line
                    char encryptedPassword[35];
                    sscanf(passwordPos, "%s", encryptedPassword);

                    // Decrypt the password
                    caesarCipher(encryptedPassword, shiftKey, 0);  // 0 to decrypt

                    // Output the decrypted password
                    printf(GRN"Decrypted password: %s\n"reset, encryptedPassword);
                    return(pressAnyKey());
                }
            }
        }
    }

    // If no matching website was found
    printf(RED"Website not found!\n"reset);
    printf("Lookup another password? (y/n)\n>>");
        char choice;
        scanf(" %c", &choice);
        if(tolower(choice) == 'y'){
            lookup();
        }
        
    return 1;
}

// Function to edit a password
int edit(void){

}

// Function to delete a password
int delete(void){

}

// Function to generate a password
int generate(void){
    system("clear");  // Clear the screen
    printTitle();  // Print the title

    int len;
    printf(BLU"\n\nWelcome to the Password Generator!\n\n"reset);
    printf("You will reciev a Password made out of random Numbers, Letters and Special characters.\n\n");
    printf(RED"Please enter the length of desired password:\n"reset);
    printf("-[");
    scanf("%d", &len);
   char possibleChars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()_+-=[]{}|;:,.<>?";
   char password[len+1];
   
   srand(time(0)); // seed for random number generation
   for(int i = 0; i < len; i++) {
      int randomIndex = rand() % (sizeof(possibleChars) - 1);
      password[i] = possibleChars[randomIndex];
   }
   
   password[len] = '\0'; // null terminate the string
   printf(GRN"\nPassword generated successfully!\n\n");
   printf("You\'r Password: %s\n"reset,password);

   pressAnyKey();

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

// Function to pause the program and wait for the user to press a key
int pressAnyKey(void) {
    printf(BLU"\nPress ENTER to go back to Main Menu..."reset);
    getchar();
    getchar();
    return 0;
}