#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>// for printf() and scanf()
#include <stdlib.h>// for rand() and srand()
#include <string.h>// for strlen(), strcpy(), ecc.
#include <ctype.h>// for Character Handling
#include <termios.h>// for disabling/eneabling echo
#include <unistd.h>// for open() and close()
#include <time.h>// for time()
#include <stdbool.h>// for bool data type

#define MAX_LINE_LENGTH 256
#define shiftKey 19
#define VERSION "3.0"
#define PASSCODE "3333"  // Replace this with your desired passcode

// ANSI color codes
#define RED "\e[0;31m"// Red
#define GRN "\e[0;32m"// Green
#define YEL "\e[0;33m"// Yellow
#define BLU "\e[0;34m"// Blue
#define MAG "\e[0;35m"// Magenta
#define CYN "\e[0;36m"// Cyan
#define HCYN "\e[0;96m"// High Cyan
#define HYEL "\e[0;93m"// High Yellow
#define HGRN "\e[0;92m"// High Green
#define HRED "\e[0;91m"// High Red
#define HBLU "\e[0;94m"// High Blue
#define BHGRN "\e[1;92m"// Bold High Green
#define URED "\e[4;31m"// Underline Red
#define reset "\e[0m"// Reset color

// Struct to store credentials
struct credentials {
    char website[50];
    char username[50];
    char password[35];
};

extern struct credentials cred;

// Declare PassFile as a global file pointer
extern FILE *PassFile;

// Function prototypes
int printTitle(void);
int add(void);
int lookup(void);
int edit(void);
int delete(void);
int generate(void);
void caesarCipher(char *text, int shift, int encrypt);
int validatePassword(const char *website, const char *password);
void disableEcho(void);
void enableEcho(void);
int pressAnyKey(void);
int about_project(void);
int about_developer(void);
int authenticate(void);
int checkWebsiteExists(const char *website);
void export_passwords(void);

#endif // FUNCTIONS_H
