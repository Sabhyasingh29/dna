#include <stdio.h>
#include <stdlib.h>


//function declaration
const char* nucleotideToBinary(char nucleotide);
char binaryToChar(const char *bitStream);

int main() {
    FILE *inputFile, *outputFile;
    char nucleotide;
    char bitBuffer[9]; // 8 bits + null terminator
    int bitIndex = 0;

    // Open input and output files
    if ((inputFile = fopen("encoded.txt", "r")) == NULL ||
        (outputFile = fopen("decoded_output.txt", "w")) == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    printf("Decoding...\n");
    bitBuffer[0] = '\0';

    // Read nucleotides from input file
    while ((nucleotide = fgetc(inputFile)) != EOF) {
        if (nucleotide == '\n' || nucleotide == ' ' || nucleotide == '\r') 
		        continue;

        const char *binaryPair = nucleotideToBinary(nucleotide);
        if (!binaryPair) {
            fprintf(stderr, "Invalid nucleotide: %c\n", nucleotide);
            continue;
        }

        // Append the binary pair to the bit buffer
        bitBuffer[bitIndex++] = binaryPair[0];
        bitBuffer[bitIndex++] = binaryPair[1];

        // When 8 bits are collected, convert to a character
        if (bitIndex == 8) {
            bitBuffer[8] = '\0';  // Null-terminate
            char decodedChar = binaryToChar(bitBuffer);
            fputc(decodedChar, outputFile);
            bitIndex = 0;
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Decoded output written to 'decoded_output.txt'\n");
    return 0;
}



// Function to convert a nucleotide to a 2-bit binary string
const char* nucleotideToBinary(char nucleotide) {
    switch (nucleotide) {
        case 'A': return "00";
        case 'C': return "01";
        case 'G': return "10";
        case 'T': return "11";
        default: return NULL;
    }
}

// Simplified function to convert an 8-bit binary string to a character
char binaryToChar(const char *bitStream) {
    int result = 0;
    int weight = 128;  // 2^7 = 128

    for (int i = 0; i < 8; i++) {
        if (bitStream[i] == '1') {
            result += weight;
        }
        weight /= 2;
    }

    return (char)result;
}



