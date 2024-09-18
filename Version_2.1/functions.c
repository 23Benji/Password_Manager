#include "functions.h"

// Define the struct globally
struct credentials cred;

int printTitle(void){

    printf(HCYN"      _____                                    _   __  __                                  \n");
    printf("     |  __ \\                                  | | |  \\/  |                                 \n");
    printf("     | |__) |_ _ ___ _____      _____  _ __ __| | | \\  / | __ _ _ __   __ _  __ _  ___ _ __ \n");
    printf("     |  ___/ _` / __/ __\\ \\ /\\ / / _ \\| '__/ _` | | |\\/| |/ _` | '_ \\ / _` |/ _` |/ _ \\ '__|\n");
    printf("     | |  | (_| \\__ \\__ \\\\ V  V / (_) | | | (_| | | |  | | (_| | | | | (_| | (_| |  __/ |   \n");
    printf("     |_|   \\__,_|___/___/ \\_/\\_/ \\___/|_|  \\__,_| |_|  |_|\___,_|_| |_|\\__,_|\\__,_|\\___|_|   \n");
    printf("                                                                             __/ |          \n");
    printf("                                                                            |___/      V:%s     \n", VERSION);
    printf(reset"\n");

    return 0;
}

// Function to add a new password
int add(void) {
    system("clear");  // Clear the screen
    printTitle();  // Print the title

    char choice;

    while (1) {  // Loop until a new, non-duplicate website is entered
        // Ask the user for the website name
        printf("\n\nEnter website name: ");
        scanf("%s", cred.website);

        // Check if the website already exists using checkWebsite function
        if (checkWebsiteExists(cred.website)) {
            printf(RED"\nWebsite '%s' already exists!\n"reset, cred.website);

            printf("Try another Website? (y/n)\n>>");
            scanf(" %c", &choice);
            if (tolower(choice) == 'n') {
                return 0;  // Exit if user does not want to try again
            }
        } else {
            break;  // Website doesn't exist, proceed to add credentials
        }
    }

    // Proceed to add the new credential
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
    
    system("clear");  // Clear the screen
    printTitle();  // Print the title

    printf(GRN"\n\nPassword added successfully!\n"reset);
    return pressAnyKey();
}

// Function to lookup a password
int lookup(void) {
    system("clear");  // Clear the screen
    printTitle();  // Print the title

    char searchWebsite[50];  // Website to search for
    char line[MAX_LINE_LENGTH];  // Buffer to store each line from the file

    // Ask the user for the website name
    printf("Enter the website name: ");
    scanf("%s", searchWebsite);

    // Check if the website exists
    if (!checkWebsiteExists(searchWebsite)) {
        printf(RED"Website not found!\n"reset);
        printf("Lookup another password? (y/n)\n>>");
        char choice;
        scanf(" %c", &choice);
        if (tolower(choice) == 'y') {
            return lookup();  // Recursive call to lookup again
        }
        return 0;
    }

    char inputPasscode[35];
    int tries = 0;
    int maxTries = 3; // Number of allowed attempts

    while (tries < maxTries) {
        printf("Enter passcode to access the Mode: ");
        disableEcho();
        scanf("%s", inputPasscode);
        enableEcho();

        if (strcmp(inputPasscode, PASSCODE) == 0) {
    
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
                    printf(GRN"\n\nDecrypted password: %s\n"reset, encryptedPassword);
                    return pressAnyKey();
                }
            }
        }
    }
        } else {
            printf(RED"\nIncorrect passcode. Try again.\n"reset);
            tries++;
        }
    }

    printf(RED"Too many failed attempts. Access denied.\n"reset);
    return pressAnyKey();

    

}

// Function to edit a password
int edit(void) {
    system("clear");
    printTitle();

    char searchWebsite[50];
    char line[MAX_LINE_LENGTH];
    char tempFileName[] = "TempPassFile.txt";
    FILE *tempFile = fopen(tempFileName, "w");

    if (tempFile == NULL) {
        printf("Error opening temporary file!\n");
        return 1;
    }

    // Ask the user for the website name
    printf("Enter the website name to edit: ");
    scanf("%s", searchWebsite);

    // Check if the website exists
    if (!checkWebsiteExists(searchWebsite)) {
        printf(RED"Website not found.\n"reset);
        fclose(tempFile);
        return pressAnyKey();
    }

    // Validate the current password
    char providedPassword[35];
    int tries = 0;
    int valid = 0;

    while (tries < 3) {
        printf("Enter the current password: ");
        disableEcho();
        scanf("%s", providedPassword);
        enableEcho();

        if (validatePassword(searchWebsite, providedPassword)) {
            valid = 1;
            break;
        } else {
            printf(RED"\nIncorrect password. Try again.\n"reset);
            tries++;
        }
    }

    if (!valid) {
        printf(RED"Too many failed attempts. Try again later.\n"reset);
        fclose(tempFile);
        return pressAnyKey();
    }

    // Rewind the file to the beginning
    rewind(PassFile);

    // Loop through each line in the file
    while (fgets(line, MAX_LINE_LENGTH, PassFile) != NULL) {
        char *websitePos = strstr(line, "Website: ");
        if (websitePos != NULL) {
            websitePos += 9;
            char websiteInLine[50];
            sscanf(websitePos, "%[^|]", websiteInLine);

            if (strcmp(websiteInLine, searchWebsite) == 0) {
                // Ask for new credentials
                printf("\n\nEnter new username: ");
                scanf("%s", cred.username);

                printf("Enter new password: ");
                disableEcho();
                scanf("%s", cred.password);
                enableEcho();

                // Encrypt the new password
                caesarCipher(cred.password, shiftKey, 1);

                // Write updated credentials to the temp file
                fprintf(tempFile, "Website: %s|Username: %s|Password: %s\n", websiteInLine, cred.username, cred.password);
                printf(GRN"\n\nCredentials updated successfully!\n"reset);
            } else {
                // Copy lines that do not match the website
                fputs(line, tempFile);
            }
        } else {
            fputs(line, tempFile);
        }
    }

    fclose(tempFile);
    fclose(PassFile);
    remove("PassC.txt");
    rename(tempFileName, "PassC.txt");

    // Reopen the password file for future operations
    PassFile = fopen("PassC.txt", "a+");

    return pressAnyKey();
}

// Function to delete a password
int delete(void) {
    system("clear");
    printTitle();

    char searchWebsite[50];
    char line[MAX_LINE_LENGTH];
    char tempFileName[] = "TempPassFile.txt";
    FILE *tempFile = fopen(tempFileName, "w");
    FILE *currentFile = fopen("PassC.txt", "r");

    if (tempFile == NULL || currentFile == NULL) {
        printf("Error opening file!\n");
        if (tempFile) fclose(tempFile);
        if (currentFile) fclose(currentFile);
        return 1;
    }

    // Ask the user for the website name to delete
    printf("Enter the website name to delete: ");
    scanf("%s", searchWebsite);

    // Check if the website exists
    if (!checkWebsiteExists(searchWebsite)) {
        printf(RED"Website not found.\n"reset);
        fclose(tempFile);
        fclose(currentFile);
        return pressAnyKey();
    }

    // Validate the current password
    char providedPassword[35];
    int tries = 0;
    int valid = 0;

    while (tries < 3) {
        printf("Enter the current password: ");
        disableEcho();
        scanf("%s", providedPassword);
        enableEcho();

        if (validatePassword(searchWebsite, providedPassword)) {
            valid = 1;
            break;
        } else {
            printf(RED"\nIncorrect password. Try again.\n"reset);
            tries++;
        }
    }

    if (!valid) {
        printf(RED"Too many failed attempts. Try again later.\n"reset);
        fclose(tempFile);
        fclose(currentFile);
        return pressAnyKey();
    }

    // Loop through each line in the current file
    int found = 0;
    while (fgets(line, MAX_LINE_LENGTH, currentFile) != NULL) {
        char *websitePos = strstr(line, "Website: ");
        if (websitePos != NULL) {
            websitePos += 9;
            char websiteInLine[50];
            sscanf(websitePos, "%[^|]", websiteInLine);

            if (strcmp(websiteInLine, searchWebsite) == 0) {
                // If the website is found, do not write this line to the temp file
                found = 1;
                printf(GRN"\n\nCredentials for '%s' deleted successfully!\n"reset, searchWebsite);
                continue;
            }
        }
        fputs(line, tempFile);
    }

    if (!found) {
        printf(RED"Website not found!\n"reset);
    }

    fclose(tempFile);
    fclose(currentFile);

    // Replace the old file with the new one
    remove("PassC.txt");
    rename(tempFileName, "PassC.txt");

    // Reopen the password file for future operations
    PassFile = fopen("PassC.txt", "a+");

    return pressAnyKey();
}

// Function to generate a password
int generate(void) {
    system("clear"); // Clear the screen
    printTitle();    // Print the title

    int len;
    printf(BLU"\n\nWelcome to the Password Generator!\n\n"reset);
    printf("You will receive a Password made out of random Numbers, Letters, and Special characters.\n\n");
    printf(RED"Please enter the length of desired password:\n"reset);
    printf("-[");
    scanf("%d", &len);

    // Validate password length
    if (len <= 0) {
    // Prompt user for character type inclusion
        printf(RED"Invalid password length! Must be greater than 0.\n"reset);
        return pressAnyKey();
    }

    int includeLowercase, includeUppercase, includeNumbers, includeSymbols;
    
    printf(BLU"Include lowercase letters? ("reset GRN"1 for Yes"reset", "RED"0 for No"reset BLU"):"reset);
    scanf("%d", &includeLowercase);
    printf(BLU"Include uppercase letters? ("reset GRN"1 for Yes"reset", "RED"0 for No"reset BLU"):"reset);
    scanf("%d", &includeUppercase);
    printf(BLU"Include numbers? ("reset GRN"1 for Yes"reset", "RED"0 for No"reset BLU"):"reset);
    scanf("%d", &includeNumbers);
    printf(BLU"Include special symbols? ("reset GRN"1 for Yes"reset", "RED"0 for No"reset BLU"):"reset);
    scanf("%d", &includeSymbols);

    // Build the possible characters string based on user choices
    char possibleChars[256] = ""; // Initialize to an empty string
    if (includeLowercase) {
        strcat(possibleChars, "abcdefghijklmnopqrstuvwxyz");
    }
    if (includeUppercase) {
        strcat(possibleChars, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    }
    if (includeNumbers) {
        strcat(possibleChars, "1234567890");
    }
    if (includeSymbols) {
        strcat(possibleChars, "!@#$%^&*()_+-=[]{}|;:,.<>?");
    }

    // Check if at least one character type is selected
    if (strlen(possibleChars) == 0) {
        printf(RED"No character types selected! Exiting...\n"reset);
        return pressAnyKey();
    }


    // Generate password
    char password[len + 1]; // Create an array for the password, with space for null terminator
    srand(time(0)); // Seed for random number generation

    for (int i = 0; i < len; i++) {
        int randomIndex = rand() % strlen(possibleChars);
        password[i] = possibleChars[randomIndex];
    }

    // Null-terminate the password string at the end
    password[len] = '\0'; 

    // Print the generated password
    printf(GRN"\nPassword generated successfully!\n\n");
    printf("Generated password: %s\n"reset, password);

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

// Function to validate the password for a given website
int validatePassword(const char *website, const char *password) {
    char line[MAX_LINE_LENGTH];
    rewind(PassFile);

    while (fgets(line, MAX_LINE_LENGTH, PassFile) != NULL) {
        char *websitePos = strstr(line, "Website: ");
        if (websitePos != NULL) {
            websitePos += 9;
            char websiteInLine[50];
            sscanf(websitePos, "%[^|]", websiteInLine);

            if (strcmp(websiteInLine, website) == 0) {
                char *passwordPos = strstr(line, "Password: ");
                if (passwordPos != NULL) {
                    passwordPos += 10;
                    char storedPassword[35];
                    sscanf(passwordPos, "%s", storedPassword);

                    // Decrypt the stored password
                    caesarCipher(storedPassword, shiftKey, 0);

                    // Check if the provided password matches the stored password
                    if (strcmp(password, storedPassword) == 0) {
                        return 1;  // Password is correct
                    } else {
                        return 0;  // Password is incorrect
                    }
                }
            }
        }
    }

    return 0;  // Website not found
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
    disableEcho();  // Disable terminal echoing
    getchar();
    getchar();
    enableEcho();  // Enable terminal echoing
    return 0;
}

// Function to print the about project page
int about_project(void){
    system("clear");  // Clear the screen
    printTitle();  // Print the title

    printf("About the Project:\n\nThis is a Password Manager created by Benji. More about can be found under the '"YEL"About the Developer"reset"' option.\n\n"
    "You are currently using Version "YEL"%s"reset". This is the "YEL"securest version"reset" of the program, implementing also Headers."
    "\nIn this version, the "YEL"security of the passwords"reset" is "YEL"guranteed"reset" and the "YEL"Managment of the passwords"reset" is "YEL"also guranteed thanks to a LogIn Passcode"reset"."
    "\nPassword Manager is a simple program that allows you to "YEL"store your passwords securely"reset" and manage them without worrying about security."
    "\n\nYou can "YEL"add"reset", "YEL"edit"reset", "YEL"delete"reset" and "YEL"lookup"reset" your passwords."
    "\nYou can find the "YEL"saved passwords"reset" in a the password Txt-file named "YEL"PassC.txt"reset". "YEL"Passwords"reset" are "YEL"encrypted"reset", so they are "YEL"not readable"reset"."
    "\nYou can also "YEL"generate"reset" a random password of your desired length, ready to be copied and used."
    "\n\nThe program uses "YEL"Caesar cipher"reset" to encrypt and decrypt your passwords."
    "\nThis program was "YEL"created with the help of AI"reset", like "YEL"ChatGPT-4o"reset" and a "YEL"Visual Studio Code Extension"reset" called "YEL"Fitten Code"reset"."
    "\n\n"RED"Note:"reset, VERSION);
    printf("If your concerned about the security of the Managment of your passwords or find any bugs, please do not hesitate to report any security vulnerabilities to me under the "YEL"Password_Manager/Issues"reset".\n\n");

    return pressAnyKey();
}

// Function to print the about the developer page
int about_developer(void){
    system("clear");  // Clear the screen
    printTitle();  // Print the title
    
    printf("About the Developer:\n\n");
    printf("This Password Manager created by Me, "YEL"Benji"reset".\n");
    printf("I am a 17 year old student from "YEL"Bolzano, Italy"reset".\n");
    printf(YEL"More about me and my Projectss"reset" can be found in my Githib profile:"YEL"https://github.com/23Benji"reset"\n");
    return pressAnyKey();
}

// Function to check if a website already exists in the password file
int checkWebsiteExists(const char *website) {
    char line[MAX_LINE_LENGTH];
    rewind(PassFile);  // Rewind to the beginning of the file

    // Loop through each line in the file
    while (fgets(line, MAX_LINE_LENGTH, PassFile) != NULL) {
        char *websitePos = strstr(line, "Website: ");
        if (websitePos != NULL) {
            websitePos += 9;  // Move 9 characters forward to get the website name
            char websiteInLine[50];
            sscanf(websitePos, "%[^|]", websiteInLine);

            // Compare the website name
            if (strcmp(websiteInLine, website) == 0) {
                return 1;  // Website exists
            }
        }
    }

    return 0;  // Website does not exist
}

// Function to authenticate the user
int authenticate(void) {
    char inputPasscode[35];
    int tries = 0;
    int maxTries = 3; // Number of allowed attempts

    while (tries < maxTries) {
        printf("Enter passcode to access the program: ");
        disableEcho();
        scanf("%s", inputPasscode);
        enableEcho();

        if (strcmp(inputPasscode, PASSCODE) == 0) {
            return 1; // Authentication successful
        } else if (maxTries == 2) {
            tries++;
        }else {
            printf(RED"\nIncorrect passcode. Try again.\n"reset);
            tries++;
        }
    }

    printf(RED"\n\nToo many failed attempts. Access denied.\n"reset);
    return 0; // Authentication failed
}

// Function to export the passwords to a file
void export_passwords(void) {
    system("clear");
    printTitle();
    
    printf(YEL"Info:"reset"This feature allows you to export all your decrypted passwords into a new Txt-file.\n\n");

    // Variables to store the file name and the line from the file
    char exportFileName[100];
    char line[MAX_LINE_LENGTH];
    
    // Ask the user for the name of the new file to save the decrypted passwords
    printf("Enter name of the file of the exported passwords ("RED"without extension"reset"): ");
    scanf("%s", exportFileName);
    
    // Append the .txt extension to the file name
    strcat(exportFileName, ".txt");

    // Open the original password file and the export file
    FILE *exportFile = fopen(exportFileName, "w");
    if (exportFile == NULL) {
        printf(RED"Error creating export file!\n"reset);
        return;
    }

    // Rewind the file to the beginning
    rewind(PassFile);

    // Read through each line in the original file
    while (fgets(line, MAX_LINE_LENGTH, PassFile) != NULL) {
        char website[50], username[50], encryptedPassword[35], decryptedPassword[35];

        // Extract website, username, and password from the line
        sscanf(line, "Website: %[^|]|Username: %[^|]|Password: %s", website, username, encryptedPassword);

        // Decrypt the password
        strcpy(decryptedPassword, encryptedPassword);  // Copy encrypted password to a new variable
        caesarCipher(decryptedPassword, shiftKey, 0);  // Decrypt

        // Write the decrypted information to the export file
        fprintf(exportFile, "Website: %s|Username: %s|Password: %s\n", website, username, decryptedPassword);
    }

    // Close the export file
    fclose(exportFile);

    printf(GRN"\nPasswords exported successfully to '%s'!\n"reset, exportFileName);
    printf(RED"Atention!: "reset URED"These passwords are decrypted before being written to the file, so they are readable.\n");
    printf("           Be sure to keep the file secure and do not share it with anyone.\n"reset);
    pressAnyKey();
}
