//
// Created by jibis on 22/02/2020.
//

#include <stdio.h>
#include <inttypes.h>

// nobits is the number of bits we read form the file (reading file in blocks of x size)
// If numbits mod 512 (ULL = Unsingned long long) has a remainder, this is where we start padding.
// Hence the 512ULL minus the modulo of nobits to the 512.
uint64_t  numzerobytes(uint64_t nobits){
    uint64_t result = 512ULL - (nobits % 512ULL);

    // Check the size of result to decide padding
    // If there's not enough room in the last block to perform the padding, add another block.
    if(result < 65){
        result += 512;
    }

    // Make space for the 8 bits and the 64 bits which have to be included in the padding
    result -= 72;

    // Return the result as an 8bit ULL
    return (result / 8ULL);
}

int main(int argc, char *argv[]){

    // If No filename specified show error
    if (argc != 2){
        printf("Error.. Single filename expected as an argument.");
        return 1;
    }

    // File pointer
    FILE *infile = fopen(argv[1], "rb");

    // If can not open file show error
    if(!infile){
        printf("Error.. Could not open file: %s. \n", argv[1]);
        return 1;
    }

    // Bitesize to read
    uint8_t _bits;
    uint64_t _nobits;

    // Read the file one byte at a time
    // PTIx8 is using the inttypes lib to print the uint as hex
    for (_nobits = 0; fread(&_bits, 1, 1, infile) == 1; _nobits += 8) {
        printf("%02" PRIx8, _bits);
    }

    // Print bits of hex value 80 => 1000 0000 (this padding will always be required in sha256)
    printf("%08" PRIx8, 0x80);

    // Pad the input with zeros
    for (uint64_t i = numzerobytes(_nobits); i > 0; i--) {
        printf("%02" PRIx8, 0x00);
    }
    // Pad the input with the final 64 bits
    printf("%016" PRIx64, _nobits);

    // Formatting for easier readability.
    printf("\n");


    // Close the file reader
    fclose(infile);
    return 0;
}