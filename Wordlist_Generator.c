#include <stdio.h>
#include<conio.h>
#include <string.h>
#include <stdlib.h>

void generate_wordlist(char *charset, char *prefix, int max_length, FILE *file, int *word_count) {
    if (max_length == 0) {
        fprintf(file, "%s\n", prefix);
        (*word_count)++;
        return;
    }

    for (size_t i = 0; i < strlen(charset); i++) {
        char new_prefix[100];
        snprintf(new_prefix, sizeof(new_prefix), "%s%c", prefix, charset[i]);
        generate_wordlist(charset, new_prefix, max_length - 1, file, word_count);
    }
}

void show_animation(int count) {
    const char spinner[] = "|/-\\";
    printf("\rGenerating wordlist... %c (%d words)", spinner[count % 4], count);
    fflush(stdout);
}

void get_available_filename(char *base_name, char *filename, size_t max_len) {
    FILE *file;
    int counter = 0;
    snprintf(filename, max_len, "%s.txt", base_name);

    while ((file = fopen(filename, "r")) != NULL) {
        fclose(file);
        counter++;
        snprintf(filename, max_len, "%s%d.txt", base_name, counter);
    }
}

int main() {
    char charset[100] = "";
    int option, max_length, word_count = 0;
    char filename[50];

    printf("Select the combination type for wordlist generation:\n");
    printf("1. Numbers\n");
    printf("2. Characters\n");
    printf("3. Symbols\n");
    printf("4. Numbers and Characters\n");
    printf("5. Numbers and Symbols\n");
    printf("6. Numbers, Characters and Symbols\n");
    printf("Enter option: ");
    scanf("%d", &option);

    printf("Enter the maximum length for words: ");
    scanf("%d", &max_length);

    switch(option) {
        case 1:
            strcpy(charset, "0123456789");
            break;
        case 2:
            strcpy(charset, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
            break;
        case 3:
            strcpy(charset, "!@#$%^&*()-_=+[]{}|;:',.<>?/`~");
            break;
        case 4:
            strcpy(charset, "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
            break;
        case 5:
            strcpy(charset, "0123456789!@#$%^&*()-_=+[]{}|;:',.<>?/`~");
            break;
        case 6:
            strcpy(charset, "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-_=+[]{}|;:',.<>?/`~");
            break;
        default:
            printf("Invalid option selected!\n");
            return 1;
    }

    get_available_filename("wordlist", filename, sizeof(filename));
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("\nStarting wordlist generation...\n");
    printf("Please Wait...\n");
    for (int length = 1; length <= max_length; length++) {
        generate_wordlist(charset, "", length, file, &word_count);
        show_animation(word_count);
    }

    fclose(file);
    printf("\nTotal words generated: %d\n", word_count);
    printf("Wordlist generated and saved to %s\n\n", filename);
    printf("Press any key to exit...");
    getch();

    return 0;
}
