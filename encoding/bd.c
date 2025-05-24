
/***********Conversion of code from string to DNA nucleotide form*****************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to convert a character to 8-bit binary and store in bitStream
void binary(char c, char *bitStream) {
    for (int i = 7; i >= 0; i--) {
        bitStream[7 - i] = (c & (1 << i)) ? '1' : '0';
    }
    bitStream[8] = '\0'; // Null-terminate
}

// Function to map 2-bit binary string to nucleotide
char binaryToNucleotide(const char *bits) {
    if (bits[0] == '0' && bits[1] == '0') return 'A';
    if (bits[0] == '0' && bits[1] == '1') return 'C';
    if (bits[0] == '1' && bits[1] == '0') return 'G';
    if (bits[0] == '1' && bits[1] == '1') return 'T';
    return '?'; // Invalid input
}

int main() {
    int ch;
    FILE *inputFile;
    FILE *outputFile;
    char bitStream[9]; // 8 bits + null terminator

    // Open input and output files
    if ((inputFile = fopen("input.txt", "rb")) == NULL ||
        (outputFile = fopen("output.txt", "w")) == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Process each character from input.txt
    while ((ch = fgetc(inputFile)) != EOF) {
        binary((char)ch, bitStream); // Convert character to binary

        // Convert every 2 bits to a nucleotide and write to output
        for (int i = 0; i < 8; i += 2) {
            char bits[3] = {bitStream[i], bitStream[i + 1], '\0'};
            char nucleotide = binaryToNucleotide(bits);
            fputc(nucleotide, outputFile);
        }
    }

    // Close files
    fclose(inputFile);
    fclose(outputFile);

    printf("Output written to 'output.txt'\n");
    return 0;
}


