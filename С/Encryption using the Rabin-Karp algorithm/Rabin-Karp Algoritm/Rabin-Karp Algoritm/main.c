#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define d 256           //значение 256 выбрано из-за того, что в кодировке ASCII имеется 256 символов. Таким образом, каждый символ в шаблоне и тексте может быть представлен числом от 0 до 255
#define MAX_STRING_SIZE 1024
#define MAX_WORD_SIZE 46

void search(char pattern[], char text[], int prime, int *counter) {
    int patternLength = strlen(pattern);
    int textLength = strlen(text);
    int i, j;
    int patternHash = 0;
    int textHash = 0;
    int h = 1;                  //используется для вычисления хеш-значения подстроки текста при сдвиге окна

    for (i = 0; i < patternLength - 1; i++)
        h = (h * d) % prime;

    for (i = 0; i < patternLength; i++) {                       //цикл вычисляет хеш-значения шаблона и первой подстроки текста
        patternHash = (d * patternHash + pattern[i]) % prime;
        textHash = (d * textHash + text[i]) % prime;
    }

    for (i = 0; i <= textLength - patternLength; i++) {         //цикл ищет шаблон в тексте. Шаг равен длине шаблона. Сравниваются                                                                  хеш-значения и, если они совпадают, сравниваются символы.
        if (patternHash == textHash) {
            for (j = 0; j < patternLength; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }

            if (j == patternLength) {
                (*counter)++;
                printf("Pattern found at index %d. This is %d meeting.\n", i+1, *counter);
            }
        }

        if (i < textLength - patternLength) {
            textHash = (d * (textHash - text[i] * h) + text[i + patternLength]) % prime;

            if (textHash < 0)
                textHash = (textHash + prime);
        }
    }
}

void textProcessing (char** text, char* textName, char* pattern, int prime, int* counter) {
    FILE* file = fopen(textName, "r");
    while (!feof(file)) {
        fgets((*text), 1024, file);
        search(pattern, (*text), prime, counter);
    }
    fclose(file);
}

char* inputPattern (char* pattern) {
    printf("Input Pattern: ");
    fgets(pattern, MAX_WORD_SIZE, stdin);
    pattern[strcspn(pattern, "\n")] = '\0';
    printf("\n");
    return pattern;
}

char* inputFileName (char* textName) {
    printf("Input name of file: ");
    fgets(textName, MAX_WORD_SIZE, stdin);
    while (strcmp(textName, "\n") == 0) {
        fgets(textName, MAX_WORD_SIZE, stdin);
    }
    textName[strcspn(textName, "\n")] = '\0';
    FILE* file = fopen(textName, "r");
    if (!file) {
        printf("\nError of opening %s! Try again\n", textName);
        system("afplay error.mp3 > /dev/null 2>&1");
        inputFileName (textName);
    }
    printf("\n");
    fclose(file);
    return textName;
}

void deleteWord(char* text, char* pattern, char* textName) {
    char* pos;
    FILE* file = fopen(textName, "r");
    if (!file) {
        printf("\nError of opening %s! Try again\n", textName);
        return;
    }
    FILE* newFile = fopen("newFile", "w");
    if (!file) {
        printf("\nError of creating newFile! Try again\n");
        return;
    }
    while (!feof(file)) {
        fgets(text, MAX_STRING_SIZE, file);
        while ((pos = strstr(text, pattern)) != NULL) {
            for (int i = pos - text; i < (strlen(text) - strlen(pattern)) - 3; i++)
                text[i] = text[i + strlen(pattern)];
            for (int i = 0; i< strlen(text); i++) {
                if (text[i] == ' ' && text[i+1] == ' ') {
                    for (int j = i; j < strlen(text); j++) {
                        text[j] = text[j+1];
                    }
                    i--;
                }
            }
        }
        fputs(text, newFile);
    }
    remove("Text.txt");
    rename("newFile", "Text.txt");
    fclose(file);
    fclose(newFile);
}

void changeWord(char* text, char* pattern, char* textName) {
    char* pos;
    char* newWord = calloc(MAX_WORD_SIZE, sizeof(char));

    printf("Input new word: ");
    getchar();
    fgets(newWord, MAX_WORD_SIZE, stdin);
    newWord[strcspn(newWord, "\n")] = '\0';
    printf("\n");

    FILE* file = fopen(textName, "r");
    if (!file) {
        printf("\nError of opening %s! Try again\n", textName);
        return;
    }

    FILE* newFile = fopen("newFile", "w");
    if (!file) {
        printf("\nError of creating newFile! Try again\n");
        return;
    }

    while (!feof(file)) {
        fgets(text, MAX_STRING_SIZE, file);

        while ((pos = strstr(text, pattern)) != NULL) {
            memmove(pos, pos + strlen(pattern), strlen(pos + strlen(pattern)) + 1);
            memmove(pos + strlen(newWord), pos, strlen(pos) + 1);
            memcpy(pos, newWord, strlen(newWord));
        }

        fputs(text, newFile);
    }

    remove("Text.txt");
    rename("newFile", "Text.txt");

    free(newWord);

    fclose(file);
    fclose(newFile);
}

int main() {
    char* textName = malloc(128 * sizeof(char));
    char* text = malloc(1024 * sizeof(char));
    char* pattern = malloc(1024 * sizeof(char));
    int countinuation = 1;
    int operation = 0;
    while (countinuation == 1) {
        int counter = 0;
        textName = inputFileName (textName);
        pattern = inputPattern (pattern);
        int prime = 101;
        textProcessing (&text, textName, pattern, prime, &counter);
        if (counter == 0) printf("Pattern not found.");
        else {
            printf("\nDo you want to delete or change this word in this text?\n");
            printf("1 - Delete word\n");
            printf("2 - Change word\n");
            printf("3 - Skip this step\n");
            printf("Youre choice: ");
            while(!scanf("%d", &operation) || operation < 0 || operation > 3) {
                printf("ERROR: Input a number in the range [1, 3]. \n");
                printf("Youre choice: ");
                rewind(stdin);
            }
            switch (operation) {
                case 1: deleteWord(text, pattern, textName);
                    printf("\nDeleting completed successfully.\n");
                    system("afplay sound.mp3 > /dev/null 2>&1");
                    break;
                case 2: changeWord(text, pattern, textName);
                    printf("\nReplacement completed successfully.\n");
                    system("afplay sound.mp3 > /dev/null 2>&1");
                    break;
                case 3:
                    system("afplay sound.mp3 > /dev/null 2>&1");
                    break;
            }
        }
        printf("\n------------------------------------\n");
        printf("Do you want to continue the processing?\n");
        printf("1 - Yes\n");
        printf("0 - No\n");
        printf("Youre choice: ");
        while(!scanf("%d", &countinuation) || countinuation < 0 || countinuation > 1) {
            printf("ERROR: Input a number in the range [1, 2]. \n");
            printf("Youre choice: ");
            rewind(stdin);
        }
        printf("------------------------------------\n");
        printf("\n");
    }
    return 0;
}
