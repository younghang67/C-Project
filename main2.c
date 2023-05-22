#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void generatePassword(int length, char complexity, const char *forApp) {
    srand(time(NULL));

    const char easyChars[] = "abcdefghijklmnopqrstuvwxyz";
    const char mediumChars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char hardChars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()";

    const char *charSet;
    int charSetLength;

    switch (complexity) {
        case 'e':
            charSet = easyChars;
            charSetLength = strlen(easyChars);
            break;
        case 'm':
            charSet = mediumChars;
            charSetLength = strlen(mediumChars);
            break;
        case 'h':
            charSet = hardChars;
            charSetLength = strlen(hardChars);
            break;
        default:
            printf("Invalid complexity level.\n");
            return;
    }

    char password[length + 1];
    for (int i = 0; i < length; i++) {
        int randomIndex = rand() % charSetLength;
        password[i] = charSet[randomIndex];
    }
    password[length] = '\0';

    printf(" Your Password Is Ready Master : %s\n", password);

    FILE *file = fopen("Passwords Manager.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "For App: %s\n", forApp);
    fprintf(file, " Your Password Master: %s\n", password);
    fprintf(file, "\n");

    fclose(file);

    printf(" Master's Password has been saved in the file 'Passwords Manager.txt'.\n");
}

int main() {
    int length;
    char complexity;
    char forApp[100];
    char anotherPassword;

    do {
        printf("Enter the desired length of the password (8-100): ");
        if (scanf("%d", &length) != 1) {
            printf("Invalid input. Please enter a valid password length.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        if (length < 8 || length > 100) {
            printf("Invalid password length. Please enter a valid password length.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        printf("Enter the complexity level (e: easy, m: medium, h: hard): ");
        while (scanf(" %c", &complexity) != 1) {
            printf("Invalid input. Please enter a valid complexity level.\n");
            while (getchar() != '\n'); // Clear input buffer
            printf("Enter the complexity level (e: easy, m: medium, h: hard): ");
        }
        while (getchar() != '\n'); // Clear input buffer

        if (complexity != 'e' && complexity != 'm' && complexity != 'h') {
            printf("Invalid complexity level. Please enter a valid complexity level.\n");
            continue;
        }

        printf(" would you like to provide name of the app where the password is being used ? : ");
        fgets(forApp, sizeof(forApp), stdin);
        forApp[strcspn(forApp, "\n")] = '\0';

        generatePassword(length, complexity, forApp);

        printf("Do you want another password? (Y/N): ");
        while (scanf(" %c", &anotherPassword) != 1 || (anotherPassword != 'Y' && anotherPassword != 'y' && anotherPassword != 'N' && anotherPassword != 'n')) {
            printf("Invalid input. Please enter either 'Y' or 'N'.\n");
            while (getchar() != '\n'); // Clear input buffer
            printf("Do you want another password? (Y/N): ");
        }
        while (getchar() != '\n'); // Clear input buffer
    } while (anotherPassword == 'Y' || anotherPassword == 'y');

    return 0;
}
