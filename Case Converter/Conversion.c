#include <stdio.h>
#include <ctype.h> 

int main() {
    char inputFileName[] = "dict.txt";   
    char outputFileName[] = "UPPERCASE.txt"; 

    FILE *inputFile = fopen(inputFileName, "r");
    FILE *outputFile = fopen(outputFileName, "w");

    if (inputFile == NULL || outputFile == NULL) {
        perror("File opening failed");
        return 1;
    }

    char word[100]; 

    while (fscanf(inputFile, "%s", word) == 1) {
        for (int i = 0; word[i]; i++) {
            word[i] = toupper(word[i]);
        }
        
        fprintf(outputFile, "%s\n", word); // Write the uppercase word on a new line
    }

    printf("Conversion completed. Uppercase words written to %s\n", outputFileName);

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
