// Including necessory libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// Global 1d dynamic array to keep track of the sizes of subarrays
int *copycount = NULL;
// function to check if the word contains any duplicate letters
bool check_duplicate(char *word){
    
    int seen[26] = {0};
    // traversing till the word length
    for (int i = 0; word[i] != '\0'; i++){
        char current = word[i]; // getting each character of word
        if (current >= 'A' && current <= 'Z'){
            current += 'a' - 'A'; // checking the character itself
        }
        if (seen[current - 'a'] == 1){ // if the char has already been seen return that duplicates exist
            return true;
        }
        else{
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

    if (file == NULL){ // If there is an error in opening a file
        printf("\n Error Opening file!\n");
        return 0;
    }

    // getting each word from the file until teh file ends
    while (fscanf(file, "%s", temp_word) != EOF){
        // checking if the length of word =s length input by user
        // +
        // if the word with user input length contains any duplicates
        if (strlen(temp_word) == length && !check_duplicate(temp_word)){
            if (*count >= *capacity){                                                  // checking if the words of length input in dict > size of dynamic array
                *capacity *= 2;                                                        // if yes then doubling array size
                word_array = (char **)realloc(word_array, *capacity * sizeof(char *)); // reallocating the size of array
                if (word_array == NULL){
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
char **dynamic_array_generator(int capacity){
    // Allocating memory to dynamic array
    char **stringarray = (char **)malloc(capacity * sizeof(char *));// allocating memory to array
    if (stringarray == NULL){
        perror("Memory Allocation Failed!");// checking if memory was allocated or not
        return NULL;
    }
    for (int i = 0; i < capacity; i++){
        stringarray[i] = NULL;// initializing each index with NULL
    }
    // returning array
    return stringarray;
}

// Function to print the words in the dynamic array
void print_words_collected(char **word_array, int length){
    
    for (int i = 0; i < length; i++){ // printing till the reallocated capacity of array
        printf("[%d] - %s | ", i + 1, word_array[i]); // Printing teh words of fetched word_array
        if ((i + 1) % 10 == 0){
            printf("\n");// printing new line after every 10 words
        }
    }
}

// Fucntion for checking if guessed char was in word or not and returning true or false
bool guess_in_word(char *word, char guess){
    
    for (int i = 0; word[i] != '\0'; i++){ // checking the word until its last character
        if (word[i] == guess){// returning true if the word contains the guessed letter
            return true;
        }
    }
    return false;// returning false if the word does not contain the guessed letter to add into a last extra subarray
}

// Function for dividing the original array into subarrays based on the index of guesses letter
char ***divide_array_on_guess(int counter, char **word_array, char guess, int length)
{
    char ***temp = (char ***)malloc((length + 1) * sizeof(char **)); // Allocate memory for 2D String array
    if (temp == NULL)
    {
        perror("Memory allocation failed"); // checking if mem was allocated or not
        return NULL;
    }
    for (int i = 0; i <= length; i++){ // Allocating memory for 2D String array's subarrays (3rd dimension in char * array)
        temp[i] = (char **)malloc(counter * sizeof(char *));
        if (temp[i] == NULL)
        {
            perror("Subarray memory allocation failed!"); // checking if memory allocation was successful or not
            return NULL;
        }
    }
    // creating a 1D array to keep track of the sizes of dynamic subarrays
    int *counters = (int *)malloc((length + 1) * sizeof(int));
    for (int i = 0; i <= length; i++){ // Initializing sizes of subarrays with 0s
        counters[i] = 0;
    }

    // Dividing the original array into subarrays based on the index of guesses letter
    for (int i = 0; i < counter; i++){ // running loop until teh size of the original word_array
        for (int j = 0; j < strlen(word_array[i]) && j <= length; j++){ // running loop until the size of word in word_array
            if (word_array[i][j] == guess){ // checking if any character in word equal guess char entered by user
                temp[j][counters[j]] = word_array[i]; // assigning the word to its respective subarray
                counters[j] += 1; // incrementing tracker for each subarray
                continue;
            }
        }
        // Checking if the word does not contain the guessed letter then assigning it to the last subarray
        bool isGuessInWord = guess_in_word(word_array[i], guess);
        if (!isGuessInWord){
            temp[length][counters[length]] = word_array[i]; // assigning word to the last subarray at each incremented index
            counters[length] += 1; // incrementing tracker for the last subarray
            continue;
        }
    }
    // copying the sizes of subarrays to a global array to use in other functions
    copycount = counters;
    // returning 2D string or 3D char array
    return temp;
}

// Function for printing divided subarrays from the original word_array
void print_subarrays(char ***subarrays, int length){
    //printf("Printing subarrays in division function\n");
    for (int i = 0; i <= length; i++){
        printf("\n===================================================== Subarray %d ===================================================== \n", i + 1);
        for (int j = 0; j < copycount[i]; j++){
            printf("%s | ", subarrays[i][j]); // Printing words of the respective subarray
            if ((j + 1 % 10) == 0){
                printf("\n");   // Printing new line after every 10 words
            }
        }
    }
}

// Function for printing a single subarray from dividee word_array into subarrays
void subarray_printer(char **category, int size){
    //printf("\nPrinting subarray %d\n", size);
    for (int i = 0; i < size; i++){
        printf("[%d] - %s | ", i, category[i]); // Printing words of the respective subarray
        if ((i + 1) % 10 == 0){
            printf("\n");
        }
    }
}

// Function fro checking if the word has been guessed or not
bool check_guess_result(char *word, int length)
{
    for (int i = 1; i <= length; i++){
        if (word[i] == '-'){ // checking if index == - or some letter
            return false;
        }
    }
    return true;// returning that word has been guessed | congratulate user
}

// function to drive the game
void Driver(int counter, char **word_array, int length, int guess)
{
    // Declaring & initializing variables
    char reveal;
    int category;
    char ***divided = NULL;
    char **subarray = NULL;
    char *result = (char *)malloc(length * sizeof(char));
    char *track = (char *)malloc(26 * sizeof(char));
    int k = 0;
    bool check = false;
    // Initializing result array with '-', this is the word that user will guess
    for (int i = 1; i <= length; i++)
    {
        result[i] = '-'; // initializing result array with '-'
    }
    // running loop until user runs out of guesses or guesses the word
    for (guess; guess >= 0;)
    {
        // checking if the result(word) has been guessed
        if(check_guess_result(result, length)){
            // Congratulating user on guessing the word correctly
            printf("\n\033[34m[+]\033[0m - Word: ");
            for (int i = 1; i <= length; i++)
            {
                printf("\033[32m%c\033[0m", result[i]);
            }
            printf("\n\033[34m[+] - Congratulations! You Won!\033[0m");
            break;
        }
        // checking if the user has run out of guesses
        if (guess == 0)
        {
            printf("\n\033[31m[+] - You Lost!\033[0m");// user lost the game
            break;
        }
        // Printing modified word after each guess/ iteration
        printf("\n\033[34m[+]\033[0m - Word: ");
        for (int i = 1; i <= length; i++)
        {
            if(result[i] != '-'){
                printf("\033[32m%c \033[0m", result[i]); // printng unguessed letters as '-'
            }else{
                printf("%c ", result[i]); // printing the guessed letters
            }
        }
        // Displaying relavent information to the player
        printf("\n\033[34m[+]\033[0m - Guesses Left: \033[31m%d\033[0m", guess);
        printf("\n\033[34m[+]\033[0m - Letters Guessed: ");
        // Keeping track of the characters guessed by the user
        // Easy for user to remember the chars that are not in the word
        for (int i = 0; i < k; i++){
            printf("\033[32m%c\033[0m, ", track[i]);
        }again:
        // Taking input from user for the letter to guess
        printf("\n\n\033[34m[+]\033[0m - Enter your guess: ");
        scanf(" %c", &reveal);
        track[k] = reveal; // keeping track of the guessed letters
        k+=1;
        // Checking if letter guessed isan alphabet
        if (reveal >= 'a' && reveal <= 'z')
        {
            // if its the first guess than dividing the originally fetched word_array into subarrays based on the guessed letter
            if (guess == 10 || check == true)
            {
                // dividing word_array into word_length+1 subarrays based on the letter user eneterd and returning the subarrays
                divided = divide_array_on_guess(counter, word_array, reveal, length);
                check = false;
            }
            // if its not the first guess than dividing the subarray of previous guess into subarrays based on the guessed letter
            else if (guess < 10)
            {
                // dividing the subarrays into further categories based on next guessed letter
                divided = divide_array_on_guess(copycount[category - 1], subarray, reveal, length);
            }
            // Printing the sizes of subarrays after each guess
            printf("\n\033[34m[+]\033[0m - Subarray sizes: ");
            for (int i = 0; i <= length; i++)
            {
                printf("\033[32m%d\033[0m, ", copycount[i]);// printing sizes
            }
            printf("\n");
            /*--------------- UnComment This line to print the divided subarrays from teh word_array or subarray from word_array ---------------*/
            //print_subarrays(divided, length);
            /* ---------------------------------------------------------------------------------------------------------------------------------*/
        select:
            // Taking input from game designer to select the subcategory for word deviation
            printf("\n\033[34m[+]\033[0m -  Enter Sub Array to select for word selection: ");
            scanf("%d", &category);
            // Checking if the category entered was > length of word or not
            if (category > length + 1)
            {
                // Printing invalid input message
                printf("\n\033[31m[+] - Invalid Input - Category is from 1 to %d \033[0m", length + 1);
                goto select; // navigating back to the letter guessing stage
            }
            // Checking if teh category selected was the one which contained words having no guessed letter in them
            else if (category == length + 1)
            {
                // Printing message that the category selected was the one which contained words having no guessed letter in them
                printf("\n\033[31m[+] - Letter [%c] not in word\n guesses = %d \033[0m", reveal, guess);
                guess -= 1; // user lost his 1 guess
                check = true;
            }else
            {
                for (int i = 0; i < length; i++){ // running loop to assign the guessed letter to the result array
                    if (i+1 == category && divided[category - 1][0][i] == reveal) // checking if the guessed letter is present in the word in respective array
                    {
                        result[category] = reveal;// assigning letter to its respective index
                        break;
                    }
                }
                // assigning the subcategory selected to subarray for further division
                subarray = divided[category - 1];
                /*--------------- UnComment This line to print the single subarrays from that game designer selected after 1st guess ---------------*/
                //subarray_printer(subarray, copycount[category - 1]);
                /* ---------------------------------------------------------------------------------------------------------------------------------*/
                guess -= 1; // user lost his guess
            }
        }else{
            // Checking for invalid letter input
            printf("\n\031[34m[+] - Invalid Input - Enter a letter from a to z \033[0m");
            goto again;// navigating to the letter guessing stage
        }
    }
}

// Main Driver funciton for the Game
int main()
{
    // Taking length & guesses as input from user
    int length, guess, counter = 0, capacity = 2048;

    // Taking user input for word length, total guesses & printing them
    printf("\n\033[34m[+]\033[0m - Enter Word length ~ Thinker: ");
    scanf("%d", &length);
    printf("\n\033[34m[+]\033[0m - Enter Total Guesses ~ Thinker: ");
    scanf("%d", &guess);
    printf("\n\033[34m[+]\033[0m - Word Length : \033[33m%d\033[0m, Gusses: \033[33m%d\033[0m", length, guess);

    // creating a dynamic array and returning it in main
    char **word_array = dynamic_array_generator(capacity);
    if (word_array == NULL)
    { // checking if array is not allocated
        printf("Exiting!");
        return 0;
    }
    // getting word_collection from dictionary of length and with no duplicates
    word_array = read_dictionary(length, word_array, &counter, &capacity);


    /*----------------------------Uncomment these lines to print all the words collected from dictionary on length basis ----------------------------*/

    /*printf("\nPrinting Array of words collected from dictionary!\n");
      print_words_collected(word_array, counter); // Printing the collected words
      printf("\n Array Printed Successfully!\n");*/
    
    /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

    // Calling the driver function to drive the game
    Driver(counter, word_array, length, guess);

    // freeing the memory allocated to word array
    for (int i = 0; i < counter; i++)
    {
        free(word_array[i]);// freeing the memory allocated to each word
    }
    free(word_array);
    return 0;
}