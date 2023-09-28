// Including necessory libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

int *copycount = NULL;
// function to check if the word contains any duplicate letters
bool check_duplicate(char *word)
{
    int seen[26] = {0};
    // traversing till the word length
    for (int i = 0; word[i] != '\0'; i++)
    {
        char current = word[i]; // getting each character of word
        if (current >= 'A' && current <= 'Z')
        {
            current += 'a' - 'A'; // checking the character itself
        }
        if (seen[current - 'a'] == 1)
        { // if the char has already been seen return that duplicates exist
            return true;
        }
        else
        {
            seen[current - 'a'] = 1; // mark the char as already present in word
        }
    }
    return false; // return that no duplicate is seen in word
}

// Function for reading words of input length from the dictionary file
char **read_dictionary(int length, char **word_array, int *count, int *capacity)
{
    FILE *file; // creating object to read file
    char temp_word[100];
    file = fopen("dict.txt", "r"); // opening file in read mode

    if (file == NULL)
    { // If there is an error in opening a file
        printf("\n Error Opening file!\n");
        return 0;
    }

    // getting each word from the file until teh file ends
    while (fscanf(file, "%s", temp_word) != EOF)
    {
        // checking if the length of word =s length input by user
        // +
        // if the word with user input length contains any duplicates
        if (strlen(temp_word) == length && !check_duplicate(temp_word))
        {
            if (*count >= *capacity)
            {                                                                          // checking if the words of length input in dict > size of dynamic array
                *capacity *= 2;                                                        // if yes then doubling array size
                word_array = (char **)realloc(word_array, *capacity * sizeof(char *)); // reallocating the size of array
                if (word_array == NULL)
                {
                    perror("Memory Reallocation failed!"); // in case of error in memory allocation
                    return NULL;
                }
            }
            // copying word of length input with no dups in word_array
            word_array[*count] = strdup(temp_word);
            (*count)++;
        }
    }
    fclose(file);      // closing the file opened for reading
    return word_array; // returning word array
}

// Function to create a dynamic 1D string array
char **dynamic_array_generator(int capacity)
{
    // Allocating memory to dynamic array
    char **stringarray = (char **)malloc(capacity * sizeof(char *));
    if (stringarray == NULL)
    {
        perror("Memory Allocation Failed!");
        return NULL;
    }
    for (int i = 0; i < capacity; i++)
    {
        stringarray[i] = NULL;
    }
    // returning array
    return stringarray;
}

// Function to print the words in the dynamic array
void print_words_collected(char **word_array, int length)
{
    for (int i = 0; i < length; i++)
    { // printing till the reallocated capacity of array
        printf("[%d] - %s | ", i + 1, word_array[i]);
        if ((i + 1) % 10 == 0)
        {
            printf("\n");
        }
    }
}

bool guess_in_word(char *word, char guess)
{
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (word[i] == guess)
        {
            return true;
        }
    }
    return false;
}

// Function for dividing the original array into subarrays based on the index of guesses letter
char ***divide_array_on_guess(int counter, char **word_array, char guess, int length)
{
    char ***temp = (char ***)malloc((length + 1) * sizeof(char **)); // Allocate memory for subarrays
    if (temp == NULL)
    {
        perror("Memory allocation failed"); // checking if mem was allocated or not
        return NULL;
    }
    for (int i = 0; i <= length; i++)
    {
        temp[i] = (char **)malloc(counter * sizeof(char *));
        if (temp[i] == NULL)
        {
            perror("Subarray memory allocation failed!");
            return NULL;
        }
    }
    int *counters = (int *)malloc((length + 1) * sizeof(int));
    for (int i = 0; i <= length; i++)
    {
        counters[i] = 0;
        printf("%d", counters[i]);
    }

    for (int i = 0; i < counter; i++)
    {
        // printf("in loop\n");
        for (int j = 0; j < strlen(word_array[i]) && j <= length; j++)
        {
            if (word_array[i][j] == guess)
            {
                temp[j][counters[j]] = word_array[i];
                counters[j] += 1;
                continue;
            }
        }
        bool isGuessInWord = guess_in_word(word_array[i], guess);
        if (!isGuessInWord)
        {
            // printf(guess_in_word(word_array[i], guess) ? "true" : "false");
            temp[length][counters[length]] = word_array[i];
            counters[length] += 1;
            continue;
        }
    }
    copycount = counters;
    for (int i = 0; i <= length; i++)
    {
        printf("%d, ", counters[i]);
    }

    return temp;
}

// Function for printing Subarrays
void print_subarrays(char ***subarrays, int length)
{
    printf("Printing subarrays in division function\n");
    for (int i = 0; i <= length; i++)
    {
        printf("\n===================================================== Subarray %d ===================================================== \n", i + 1);
        for (int j = 0; j < copycount[i]; j++)
        {
            printf("%s | ", subarrays[i][j]);
            if ((j + 1 % 10) == 0)
            {
                printf("\n");
            }
        }
    }
}

// Function for dividing sub categoryu into further guess based sub arrays
void subarray_printer(char **category, int size)
{
    //printf("\nPrinting subarray %d\n", size);
    for (int i = 0; i < size; i++)
    {
        printf("[%d] - %s | ", i, category[i]);
        if ((i + 1) % 10 == 0)
        {
            printf("\n");
        }
    }
}


bool check_guess_result(char *word, int length)
{
    for (int i = 1; i <= length; i++)
    {
        if (word[i] == '-')
        {
            return false;
        }
    }
    return true;
}

// function to drive the game
void Driver(int counter, char **word_array, int length, int guess)
{
    char reveal;
    int category;
    char ***divided = NULL;
    char **subarray = NULL;
    char *result = (char *)malloc(length * sizeof(char));
    char *track = (char *)malloc(26 * sizeof(char));
    int k = 0;
    bool check = false;
    for (int i = 1; i <= length; i++)
    {
        result[i] = '-';
    }
    for (guess; guess >= 0;)
    {
        if(check_guess_result(result, length)){
            printf("Congratulations! You Won!");
            break;
        }
        if (guess == 0)
        {
            printf("You Lost!");
            break;
        }
        printf("\nWord: ");
        for (int i = 1; i <= length; i++)
        {
            printf("%c ", result[i]);
        }
        printf("\nGuesses Left: %d", guess);
        printf("\nLetters Guessed: ");
        for (int i = 0; i < k; i++){
            printf("%c, ", track[i]);
        }again:
        printf("\n\nEnter your guess: ");
        scanf(" %c", &reveal);
        track[k] = reveal;
        k+=1;
        if (reveal >= 'a' && reveal <= 'z')
        {
            if (guess == 10 || check == true)
            {
                divided = divide_array_on_guess(counter, word_array, reveal, length);
                check = false;
            }
            else if (guess < 10)
            {
                divided = divide_array_on_guess(copycount[category - 1], subarray, reveal, length);
            }
            for (int i = 0; i <= length; i++)
            {
                printf("%d, ", copycount[i]);
            }
            print_subarrays(divided, length);
        select:
            printf("\n Enter Sub Array to select for word selection: ");
            scanf("%d", &category);
            if (category > length + 1)
            {
                printf("Invalid Input - Category is from 1 to %d", length + 1);
                goto select;
            }
            if (category == length + 1)
            {
                printf("Letter [%c] not in word\n guesses = %d", reveal, guess);
                guess -= 1;
                check = true;
            }
            else
            {
                for (int i = 1; i <= length; i++)
                {
                    if (i == category)
                    {
                        result[category] = reveal;
                    }
                }
                subarray = divided[category - 1];
                subarray_printer(subarray, copycount[category - 1]);
                guess -= 1;
            }
        }else{
            printf("Invalid Input - Enter a letter from a to z");
            goto again;
        }
    }
}

// Main Driver funciton for the Game
int main()
{
    // Taking length & guesses as input from user
    int length, guess, counter = 0, capacity = 2048;

    printf("Enter Word length ~ Thinker: ");
    scanf("%d", &length);
    printf("Enter Total Guesses ~ Thinker: ");
    scanf("%d", &guess);
    printf("Word Length : %d, Gusses: %d", length, guess);

    // creating a dynamic array and returning it in main
    char **word_array = dynamic_array_generator(capacity);
    if (word_array == NULL)
    { // checking if array is not allocated
        printf("Exiting!");
        return 0;
    }
    // getting word_collection from dictionary of length and with no duplicates
    word_array = read_dictionary(length, word_array, &counter, &capacity);

    printf("\nPrinting Array of words collected from dictionary!\n");
    print_words_collected(word_array, counter); // Printing the collected words
    printf("\n Array Printed Successfully!\n");

    Driver(counter, word_array, length, guess);
    // freeing the memory allocated to word array
    for (int i = 0; i < counter; i++)
    {
        free(word_array[i]);
    }
    free(word_array);
    return 0;
}