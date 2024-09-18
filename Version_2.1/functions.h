#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 256
#define shiftKey 19
#define VERSION "2.1"
#define PASSCODE "1111"  // Replace this with your desired passcode

// ANSI color codes
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define HCYN "\e[0;96m"
#define HYEL "\e[0;93m"
#define HRED "\e[0;91m"
#define URED "\e[4;31m"
#define reset "\e[0m"

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
