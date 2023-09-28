// Including necessory libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

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

// Function for dividing the original array into subarrays based on the index of guesses letter
char ***divide_array_on_guess(int counter, char **word_array, char guess, int length)
{
    //char **temp2 = (char **)malloc(counter * sizeof(char *));
    char ***temp = (char ***)malloc((length + 1) * sizeof(char **)); // Allocate memory for subarrays
    const int len = length;
    if (temp == NULL)
    {
        perror("Memory allocation failed"); // checking if mem was allocated or not
        return NULL;
    }
    for (int i = 0; i < length; i++){
        temp[i] = (char **)malloc(counter * sizeof(char *));
        if (temp[i] == NULL){
            perror("Subarray memory allocation failed!");
            return NULL;
        }
    }
    //int counters[len] = {0};
    int *counters = (int *)(length * sizeof(int));
    for (int i = 0; i < length; i++){
        counters[i] = 0;
        printf("%d", counters[i]);
    }
        for (int i = 0; i < counter; i++){
        printf("in loop\n");
        for (int j = 0; j < strlen(word_array[i]); j++)
        {
            if (word_array[i][j] == guess){
                temp[j][counters[j]] = word_array[i];
                counters[j] += 1;
                break;
            }
        }
    }

    // Initialize subarrays for words that contain the guessed letter at respective index
    // for (int i = 0; i < length; i++)
    // {
    //     temp[i] = (char **)malloc(counter * sizeof(char *));
    //     if (temp[i] == NULL)
    //     {
    //         perror("Subarray memory allocation failed!");
    //         return NULL;
    //     }
    //     // copying words into subarrays based on the index of guess in each word
    //     for (int j = 0; j < counter; j++)
    //     {
    //         if (strlen(word_array[j]) > i && word_array[j][i] == guess)
    //         { // checking if guess exists in word
    //             temp[i][j] = (char *)malloc((strlen(word_array[j]) + 1) * sizeof(char));
    //             strcpy(temp[i][j], word_array[j]); // copying word in its respective array
    //         }
    //         else
    //         {
    //             temp[i][j] = NULL;
    //         }
    //     }
    // }
    // // Initialize the last subarray for words that do not contain the guessed letter
    // temp[length] = (char **)malloc(counter * sizeof(char *));
    // if (temp[length] == NULL)
    // { // allocating memory for last subarray
    //     perror("Subarray memory allocation failed!");
    //     return NULL;
    // }
    // for (int j = 0; j < counter; j++)
    // {
    //     if (strchr(word_array[j], guess) == NULL)
    //     { // checking if guess is not in word
    //         temp[length][j] = (char *)malloc((strlen(word_array[j]) + 1) * sizeof(char));
    //         strcpy(temp[length][j], word_array[j]); // copying no guess word to an extra subarray
    //     }
    //     else
    //     {
    //         temp[length][j] = NULL;
    //     }
    // }
    return temp;
}

// Function for printing Subarrays
void print_subarrays(char ***subarrays, int length, int counter)
{
    for (int i = 0; i < length; i++)
    { // printing subarrays
        printf("\n===================================================== Subarray %d ===================================================== \n", i + 1);
        for (int j = 0; j < counter; j++)
        {
            if (subarrays[i][j] != NULL)
            { // checking if index is not null
                printf("%s | ", subarrays[i][j]);
                if ((j + 1 % 10) == 0)
                { // printing new line after 10 words
                    printf("\n");
                }
            }
        }
    }
}

// Function for dividing sub categoryu into further guess based sub arrays
void subarray_printer(char **category, char guess, int length, int size)
{
    printf("In sub array divider %s", *category[0]);
    for (int i = 0; i < size; i++)
    {
        printf("[%d] - %s | ", i, *category[i]);
        if ((i + 1) % 10 == 0)
        {
            printf("\n");
        }
    }
}

// function to drive the game
void Driver(int counter, char **word_array, int length, int guess)
{
    char reveal;
    int category;
again:
    printf("\nGuess Character: ");
    for (int i = 0; i < length; i++)
    {
        printf("-- ");
    }
    printf("\n\nEnter your 1st guess ~ Player: ");
    scanf(" %c", &reveal);
    char ***divided = divide_array_on_guess(counter, word_array, reveal, length);
    guess -= 1;
    print_subarrays(divided, length + 1, counter); // printing original array divided into subarrays
    printf("\n Enter Sub Array to select for word selection: ");
    scanf("%d", &category);

    if (category == length + 1)
    {
        printf("Letter [%c] not in word\n guesses = %d", reveal, guess);
        goto again;
    }
    else
    {
        for (int i = 0; i < length; i++)
        {
            if (i + 1 == category)
            {
                printf("%c ", reveal);
            }
            else
            {
                printf("-- ");
            }
        }
        int size = 0, i= 0;
        //size = sizeof(divided) ;
        //size = len(divided[category]);
        // while (divided[category][i] != NULL)
        // {
        //     //printf("in while\n");
        //     size++;
        //     i++;
        // }
        printf("\n size: %d\n", size);
        char **subarray = divided[category];
        // char **subarray = (char **)malloc((size + 1) * sizeof(char *));
        for (int i = 0; subarray[i] != NULL; i++)
        {
            printf("---\nThis loo[] is running checker\n---");
            //subarray[i] = strdup(divided[category][i]);
            printf("%s", subarray[i]);
        }
        //subarray[size] = NULL;

        for (int i = 0; i < size; i++)
        {
            printf("[%d] - %s | ", i, subarray[i]);
            if ((i + 1) % 10 == 0)
            {
                printf("\n");
            }
        }
        char next_guess;

        printf("\nEnter next guess: ");
        scanf(" %c", &next_guess);
        subarray_printer(subarray, next_guess, length, size);
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