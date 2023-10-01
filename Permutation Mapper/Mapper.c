// Including Necessory Libraries for usage in the program
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Declaring Global Variables
int grouped_count = 0;
int solutionCount = 0;
int combos = 0;
char **solutions;

// Declaring Function protoype for below defined function
char **dynamic_array_generator(int capacity);

// Function for reading the dictionary file and storing the words in an array
char **read_dictionary(int length, int *count, int capacity){
    // creating dynamic array for storing words of length input by user
    char **word_array = dynamic_array_generator(capacity); 

    FILE *file; // creating object to read file
    char temp_word[100];
    file = fopen("UPPERCASE.txt", "r"); // opening file in read mode

    if (file == NULL){ // If there is an error in opening a file
        printf("\n Error Opening file!\n");
        return 0;
    }

    // getting each word from the file until teh file ends
    while (fscanf(file, "%s", temp_word) != EOF){
        // checking if the length of word =s length input by user
        // +
        // if the word with user input length contains any duplicates
        if (strlen(temp_word) == length){
            if (*count >= capacity){                                                  // checking if the words of length input in dict > size of dynamic array
                capacity *= 2;                                                        // if yes then doubling array size
                word_array = (char **)realloc(word_array, capacity * sizeof(char *)); // reallocating the size of array
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

// Function for generating dynamic array
char **dynamic_array_generator(int capacity){
    // Allocating memory to dynamic array
    char **stringarray = (char **)malloc(capacity * sizeof(char *)); // allocating memory to array
    if (stringarray == NULL){
        perror("Memory Allocation Failed!"); // checking if memory was allocated or not
        return NULL;
    }
    for (int i = 0; i < capacity; i++){
        stringarray[i] = NULL; // initializing each index with NULL
    }
    // returning array
    return stringarray;
}

// Function for creating dynamic integer array generator
int *dynamic_int_array_generator(int total_nums, int num){
    // Allocating memory to dynamic array
    int *intarray = (int *)malloc(total_nums * sizeof(int)); // allocating memory to array
    if (intarray == NULL){
        perror("Memory Allocation Failed!"); // checking if memory was allocated or not
        return NULL;
    }
    for (int i = 0; i < total_nums; i++){
        intarray[i] = num; // initializing each index with NULL
    }
    // returning array
    return intarray;
}

// Function for generating dynamic 3D array
char ***D3_array_generetor(int total_nums){
    char ***D3_array = (char ***)malloc(total_nums * sizeof(char **)); // allocating memory to array
    if (D3_array == NULL){
        perror("Memory Allocation Failed!"); // checking if memory was allocated or not
        return NULL;
    }
    for (int i = 0; i < total_nums; i++){
        D3_array[i] = NULL; // initializing each index with NULL
    }
    // returning array
    return D3_array;
}

// Fucntion for printing the fetched array from dictionary
void print_fetched_arrays(char **array, int count){
    printf("\n\n\033[32m================================ Printing Araay of words ================================\033[0m\n\n");
    for (int i = 0; i < count; i++){
        if(array[i] == NULL){
            continue;
        }
        printf("[%d ]- %s | ", i + 1, array[i]); // printing each word in array
        if ((i + 1) % 10 == 0){
            printf("\n"); // printing new line after every 10 words
        }
    }
}

// Fucntion for calculating the total no of permutations for the numbers enetered
long long calculatePermutations(int n, int r){
    if (n < r){ // permutations cannot be calculated if number entered > 26 i.e. no of alphabets
        return 0;
    }
    long long permutations = 1; // initializing permutations to 1
    for (int i = n; i > (n - r); i--){ // calculating permutations
        permutations *= i;
    }
    // returning permuattions
    return permutations;
}

// Funtion for printing the argumnets & their lengths
void print_arguments(int total_nums, int *nums, int *lengths, int total_length){
    // Loop for printing all entered arguments
    for (int i = 0; i < total_nums; i++){ // printing the numbers entered
        printf("\033[34m[+] - \033[0mnum [%d] - \033[33m%d\033[0m, ", i, nums[i]); // prinitng entered numbers
    }
    printf("\n");
    // Loop  for printing the lengths of all the numbers entered
    for (int i = 0; i < total_nums; i++){ // printing the lengths of numbers entered
        printf("\033[34m[+] - \033[0mlength [%d] - \033[33m%d\033[0m, ", i, lengths[i]); // printing ;engths
    }
    printf("\n");
    // Printing total length of arguments enetered for calculating permutations
    printf("\n\033[34m[+] - \033[0mTotal length: %d\n", total_length); // printing the total length of all the numbers entered for permutations
}

// Function for integrating the arrays fetched from the dictionary into a single array and then print them
char **fetch_print_group(int total_nums, char*** arrays, int* count, int* capacity, int* lengths){
    bool *checks = (bool *)malloc(total_nums * sizeof(bool));      // array for storing the checks for each number entered
    for (int i = 0; i < total_nums; i++){
        checks[i] = false; // initializing all checks to false
    }
    // reading the dictionary file and storing the words in respective arrays
    for (int i = 0; i < total_nums; i++){
        int current = lengths[i];
        if (!checks[current]){ // checking if the length has already been fetched from the array{
            arrays[i] = read_dictionary(lengths[i], &count[i], capacity[i]); // reading from dictionary according to teh length of the number in argument entered
            printf("\n\033[32mArray[%d] - Total Words = %d\033[0m\n", i, count[i]);         // printing the total words fetched from the upper case dict file.

            /*------------------------------------ Uncomment this line to print the arrays of words fetched from the dictionary ------------------------------------ */
            //print_fetched_arrays(arrays[i], count[i]); // printing the arrays of words fetched from the upper case dict file.
            checks[current] = true;
        }
    }
    // getting total capacity and total count for merging all the arrays
    int total_count = 0, total_capacity = 0;
    for (int i = 0; i < total_nums; i++){
        total_count += count[i]; // calculating the total capacity of all the arrays
        total_capacity += capacity[i];
    }
    grouped_count = total_capacity;
    printf("\n\033[32mTotal Count = %d\033[0m\n", total_count); // printing the total capacity of all the arrays
    printf("\n\033[32mTotal Capacity = %d\033[0m\n", total_capacity); // printing the total capacity of all the arrays
    
    // creating a grouped array for storing all the words from the arrays of words fetched from the dictionary
    char ** grouped_array = dynamic_array_generator(total_capacity); 
    for (int i = 0; i < total_nums; i++){
        for (int j = 0; j < count[i]; j++){
            for (int k = 0; k < total_capacity; k++){
                if (grouped_array[k] == NULL){
                    grouped_array[k] = strdup(arrays[i][j]); // copying the words from the arrays of words fetched from the dictionary to the grouped array
                    break;
                }
            }
        }
    }
    grouped_array[grouped_count] = NULL;            // initializing the last index of grouped array to NULL

    /*------------------------------------ Uncomment this line to print the combined array of words fetched from the dictionary ------------------------------------ */
    //print_fetched_arrays(grouped_array, total_count); // printing the grouped array
    return grouped_array;
}

// function for checking if the possible combination for arguments entered is in dictionary or not
bool is_in_dictionary(char word_array[][10], char **dictionary, int count, int total_nums) {
    // Loop for iterating each arguments equivalent word in the dictionary
    for (int i = 0; i < total_nums; i++) {
        bool found = false; // Initialize a flag for each word
        for (int j = 0; j < grouped_count; j++) {
            if (dictionary[j] != NULL && strcmp(word_array[i], dictionary[j]) == 0) { // checking if there is a word at the index and if the word and possible combo word are same
                found = true; // Set the flag to true if the word is found
                break; // No need to check further, exit the inner loop
            }
        }
        if (!found) {
            return false; // If any word is not found, return false
        }
    }
    return true; // If all words are found, return true
}


// function for mapping letters to digits in numbers enetered in arguments and creating total permutation possible combinations
void digit_to_letter_mappings(char** grouped, int grouped_count, char* finalnum, char* combination, int index, int length, int total_nums, int* lengths){
    char total_strings[total_nums][10];         // Initializing
    int start = 0;                              // Necessory 
    bool check = false;                         // Variables & Arrays
    char *temp = NULL;
    
    // Checking if the index of possible combo equals the total length of arguments (1 combo is complete)
    if (index == length){
        // Dividing the combination into words of respective lengths
        for (int i = 0; i < total_nums; i++) {
            // Extract the current string using strncpy
            strncpy(total_strings[i], combination + start, lengths[i]);
            total_strings[i][lengths[i]] = '\0'; // Null-terminate the extracted string
            // Update the start index for the next iteration
            start += lengths[i];
        }
        /*------------------------------------ Print The current Combo of words ------------------------------------  */
        // for (int i = 0; i < total_nums; i++){
        //     printf("total_strings[%d] = %s, ", i, total_strings[i]);
        // }
        /*------------------------------------------------------------------------------------------------------------ */
        start = 0;
        // checking if the possible combo is present in dictionary or not
        if (is_in_dictionary(total_strings, grouped, grouped_count, total_nums)){
            // craeting a string to store concatenated words of possible combo
            char concatenated_string[total_nums * 10]; // Adjust the size accordingly
            concatenated_string[0] = '\0';

            for (int i = 0; i < total_nums; i++) {// concatenating the combo into a sentence
                strcat(concatenated_string, total_strings[i]);
                strcat(concatenated_string, " "); // concatenating spaces between words
            }
            // adding the combination to the array of solutions
            solutions[solutionCount] = strdup(concatenated_string);
            solutionCount++;
        }
            combos++; // checking total combinations
            return;
    }
    
    char currentDigit = finalnum[index] - '0';
    for (char letter = 'A'; letter <= 'Z'; letter++){// Loop for mapping the letters to digits in the numbers entered in arguments
        combination[index] = letter;
        int isRepeat = 0;
        for (int i = 0; i < index; i++){// Loop for checking if the letter is already mapped to a digit or not
            if (finalnum[i] == finalnum[index] && combination[i] != letter){// checking if the letter is already mapped to a digit or not
                isRepeat = 1;
                break;
            }
        }
        if (!isRepeat){// if letter is not mapped to a digit moving to the next recursive call
        digit_to_letter_mappings(grouped, grouped_count, finalnum, combination, index + 1, length, total_nums, lengths);
    }
    combination[index] = '\0';
    }
}

// Function for printing computation details onto the screen
void printer(clock_t start, clock_t end){
    printf ("\033[34m[+] - \033[0mTotal Combos \033[34m%d\033[0m\n", combos);                // printing total combinations of words against numbers eneterde
    printf ("\033[34m[+] - \033[0msolutions count \033[31m%d\033[0m\n", solutionCount);      // printing no. of possible solutions against numbers enetered
    printf("\n\033[34m[+] - \033[0mPrinting Possible Solutions for Enetred Arguments\n");    // printing possible solutions for the numbers enetered
    print_fetched_arrays(solutions, solutionCount);
    double time_taken = ((double)end - start) / CLOCKS_PER_SEC;         // calculating the time taken by the system to calculate teh possible solutions
    printf("\n\033[34m[+] - \033[0mTime taken: \033[32m%f\033[0m\n", time_taken);            // printing the total time taken by the system
}
// Main Function
int main(int argc, char *argv[])
{
    if (argc != (atoi(argv[1]) + 2)){ // checking if the no of arguments are 3 or not 1 for object files and 2 for arguments
        printf("\031[34m[+] - Usage: %s <Total_nums> <total_nums> * [numbers]\033[0m\n", argv[0]);
        return 1;
    }
    // getting total numbers of numbers entered as arguments
    const int total_nums = atoi(argv[1]);

    // Creating all the dynamic arrays we are going to need for this program
    char ***arrays = D3_array_generetor(total_nums);               // 3D array containing words of length of each number got from teh arguments user entered
    int *count = dynamic_int_array_generator(total_nums, 0);       // array for storing the total length of each dynamic word array accord to length of number generated
    int *capacity = dynamic_int_array_generator(total_nums, 2048); // array storing the capacity of each dynamic word arrays ...
    int *lengths = dynamic_int_array_generator(total_nums, 0);     // array for stroing the length of each number entered
    int *nums = dynamic_int_array_generator(total_nums, 0);        // array for storing the numbers entered
    solutions = dynamic_array_generator(grouped_count);
    int total_length = 0;
    clock_t start, end;

    // Conerting the numbers from arguments from char* to int and stroing them in nums array
    for (int i = 0; i < total_nums; i++){
        nums[i] = atoi(argv[i + 2]); // ing the numbers from arguments from char* to int and stroing them in nums array
        lengths[i] = strlen(argv[i + 2]); // getting the length of each number entered
        total_length += lengths[i];       // calculating the total length of all the numbers entered for permutations
    }

    // printing all numbers from args and their lengths
    print_arguments(total_nums, nums, lengths, total_length);

    // calculating the total permutations for the numbers entered
    long long perms = calculatePermutations(26, total_length);
    printf("\033[34m[+] - \033[0mTotal permutations: \033[31m%lld\033[0m\n", perms);

    // function to fetch words of respective lengths + print those words + group them in one array for permutation mapping
    char **grouped = fetch_print_group(total_nums, arrays, count, capacity, lengths);

    // array to store the possible combinations of letters for the numbers entered
    char assignment[total_length + 1];
    memset(assignment, 0, sizeof(assignment)); // Initialize to null characters
    // chared array for into to string converted numbers enetered as arguments
    char **chared = (char **)malloc(total_nums * sizeof(char *));
    for (int i = 0; i < total_nums; i++) { // Allocating memory to teh chared array
        chared[i] = (char *)malloc((strlen(argv[i + 2]) + 1) * sizeof(char)); // +1 for the null terminator
        strcpy(chared[i], argv[i + 2]); // copying the numbers to each index enetered as arguments
    }
    /*------------------------------------ Uncomment These lines to print the divided chared numbers from arguments ------------------------------------ */
    // for (int i = 0; i < total_nums; i++) {
    //     printf("\033[34m[+] - \033[0mchared[%d] = %s\n", i, chared[i]);
    // }
    /*--------------------------------------------------------------------------------------------------------------------------------------------------- */
    
    // A final string to store concatenated comination of letters for the numbers entered
    char finalnum[total_length + 1];
    strcpy(finalnum, chared[0]); // concatenating the 1st number entered
    for (int i = 1; i < total_nums; i ++){
        strcat(finalnum, chared[i]); // concatenatine argv[1 ~ end] numbers from teh arguments
    }
    printf("\033[34m[+] - \033[0mfinalnum = %s\n", finalnum);
    // starting the clock for cpu time and printing the start time
    start = clock(); 
    printf("\033[34m[+] - \033[0mstart time: \033[31m%ld\033[0m\n", start);
    // function for mapping letters to digits in numbers enetered in arguments and creating total permutation possible combinations
    digit_to_letter_mappings(grouped, grouped_count, finalnum, assignment, 0, total_length, total_nums, lengths);
    // ending the clock for cpu time and printing the end time
    end = clock();
    printf("\033[34m[+] - \033[0mend time: \033[31m%ld\033[0m\n", end);
    printer(start, end); // printing the computation details
    
    return 0;
}
