// Including Necessory Libraries for usage in the program
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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
    for (int i = 0; i < total_nums; i++){ // printing the numbers entered
        printf("\nnum [%d] - %d, ", i, nums[i]);
    }
    for (int i = 0; i < total_nums; i++){ // printing the lengths of numbers entered
        printf("\nlength [%d] - %d, ", i, lengths[i]);
    }
    printf("\nTotal length: %d\n", total_length); // printing the total length of all the numbers entered for permutations
}

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
            print_fetched_arrays(arrays[i], count[i]); // printing the arrays of words fetched from the upper case dict file.
            checks[current] = true;
        }
    }
    // getting total capacity and total count for merging all the arrays
    int total_count = 0, total_capacity = 0;
    for (int i = 0; i < total_nums; i++){
        total_count += count[i]; // calculating the total capacity of all the arrays
        total_capacity += capacity[i];
    }
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
    grouped_array[total_capacity] = NULL;            // initializing the last index of grouped array to NULL
    print_fetched_arrays(grouped_array, total_capacity); // printing the grouped array
    return grouped_array;
}
// Main Function
int main(int argc, char *argv[])
{
    if (argc != (atoi(argv[1]) + 2)){ // checking if the no of arguments are 3 or not 1 for object files and 2 for arguments
        printf("Usage: %s <Total_nums> <total_nums> * [numbers]\n", argv[0]);
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
    int total_length = 0;

    // Conerting the numbers from arguments from char* to int and stroing them in nums array
    for (int i = 0; i < total_nums; i++){
        nums[i] = atoi(argv[i + 2]);
        lengths[i] = strlen(argv[i + 2]); // getting the length of each number entered
        total_length += lengths[i];       // calculating the total length of all the numbers entered for permutations
    }

    // printing all numbers from args and their lengths
    print_arguments(total_nums, nums, lengths, total_length);

    // calculating the total permutations for the numbers entered
    long long perms = calculatePermutations(26, total_length);
    printf("Total permutations: %lld\n", perms);

    // function to fetch words of respective lengths + print those words + group them in one array for permutation mapping
    char **grouped = fetch_print_group(total_nums, arrays, count, capacity, lengths);
    return 0;
}
