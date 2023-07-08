#include <stdio.h>

int main() {
    FILE *inputFile, *outputFile;
    char ch;

    // Open the input file in read mode
    inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Cannot open input file.\n");
        return 1;
    }

    // Open the output file in write mode
    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Cannot create output file.\n");
        return 1;
    }

    // Read from the input file and write to the output file
    while ((ch = fgetc(inputFile)) != EOF) {
        fputc(ch, outputFile);
    }

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    printf("File copied successfully.\n");

    return 0;
}
