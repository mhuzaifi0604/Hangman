#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>

bool check_duplicate(char* word){
    int seen[26] = {0};
    for (int i = 0; word[i] != '\0'; i++){
        char current = word[i];
        if(current >= 'A' && current <= 'Z'){
            current += 'a' - 'A';
        }
        if(seen[current - 'a'] == 1){
            return true; // Letter is already seen, indicating a duplicate
        } else {
            seen[current - 'a'] = 1; // Mark the letter as seen
        }
    }
    return false; // No duplicate letters found
}



char** read_dictionary(int length, char** word_array, int* count, int* capacity){
    FILE *file;
    char temp_word[100];
    file = fopen("dict.txt", "r");
    
    if(file == NULL){
        printf("\n Error Opening file!\n");
        return 0;
    }
    printf("file opened!");

    while(fscanf(file, "%s", temp_word) != EOF){
        if(strlen(temp_word) == length && !check_duplicate(temp_word)){
            if (*count >= *capacity){
                *capacity *= 2;
                word_array = (char **)realloc(word_array, *capacity * sizeof(char*));
                if(word_array == NULL){
                    perror("Memory Reallocation failed!");
                    return NULL;
                }
            }
            word_array[*count] = strdup(temp_word);
            (*count)++;
        }
    }
    fclose(file);
    return word_array;
}



char ** dynamic_array_generator(int capacity){
    char **stringarray = (char **)malloc(capacity * sizeof(char *));
    if(stringarray == NULL){
        perror("Memory Allocation Failed!");
        return NULL;
    }
    for (int i = 0; i < capacity; i++) {
        stringarray[i] = NULL;
    }
    return stringarray;
}

void print_words_collected(char ** word_array, int length){
    for (int i = 0; i < length; i++){
        printf("[%d] - %s | ", i + 1, word_array[i]);
        if((i+1) % 10 == 0){
            printf("\n");
        }
    }
}

int main() {
    int length, guess, counter = 0, capacity = 2048;
    printf("Enter Word length: ");
    scanf("%d", &length);
    printf("Enter Total Guesses: ");
    scanf("%d", &guess);
    printf("Word Length : %d, Gusses: %d", length, guess);
    char **word_array = dynamic_array_generator(capacity);
    if(word_array == NULL){
        printf("Exiting!");
        return 0;
    }
    word_array = read_dictionary(length, word_array, &counter, &capacity);

    printf("\nPrinting Array of words collected from dictionary!\n");
    print_words_collected(word_array, counter);
    for (int i = 0; i < counter; i++){
        free(word_array[i]);
    }
    free(word_array);
    return 0;
}