#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<termios.h>
#include<unistd.h>
#include"functions.h"


FILE *PassFile;  // Global variable for the password file

int main(void){

    system("clear");  // Clear the screen
    printTitle();  // Print the title
    if (!authenticate()) {
        return 1; // Exit program if authentication fails
    }

PassFile = fopen("PassC.txt", "a+");  // Open for appending and reading, create if it doesn't exist

if (PassFile == NULL) {
    printf("Error creating file!\n");
    exit(1);  //
}
    char choice;// User's choice variable

// Main loop
    while (1) {
        
            system("clear");  // Clear the screen
            printTitle();  // Print the title
            printf(YEL"\n\nWelcome to the Password Manager!\n\n"reset);


            printf(RED"Please select an option:"reset"\n\n");
            printf(BLU"  @\n");
            printf("  |\n");
            printf("-["reset HYEL"1"reset BLU"]--Add Password\n");
            printf("  |\n");
            printf("-["reset HYEL"2"reset BLU"]--Lookup Password\n");
            printf("  |\n");
            printf("-["reset HYEL"3"reset BLU"]--Edit Password\n");
            printf("  |\n");
            printf("-["reset HYEL"4"reset BLU"]--Delete Password\n");
            printf("  |\n");
            printf("-["reset HYEL"5"reset BLU"]--Generate Password\n");
            printf("  |\n");
            printf("-["reset HYEL"6"reset BLU"]--About the Program\n");
            printf("  |\n");
            printf("-["reset HYEL"7"reset BLU"]--About the Developer\n");
            printf("  |\n");
            printf("-["reset HYEL"8"reset BLU"]--Export all decripted Passwords\n");
            printf("  |\n");                        
            printf("  |\n"reset);
            printf(HRED"-["HYEL"00"reset HRED"]--Exit\n"reset);
            printf(BLU"  |\n");            
            printf(BLU" -@-["reset);

            scanf(" %c", &choice);  //Scan choice and remove space before %c to ignore previous newline

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
            case '6':
                about_project();
                fflush(stdin);  // Clear the input buffer
                break;
            case '7':
                about_developer();
                fflush(stdin);  // Clear the input buffer
                break;
            case '8':
                export_passwords();
                fflush(stdin);  // Clear the input buffer
                break;
            case '0':
                system("clear");  // Clear the screen
                printTitle();  // Print the title
                printf(GRN"\n❤ Thank you for using the Password Manager!\n");
                printf("❤ Hope to see You soon! :D\n\n\n"reset);
                return 0;
            default:
                break;
        }
        
    }
    fclose(PassFile);
    
    return 0;
}
