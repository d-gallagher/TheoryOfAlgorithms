//
// Created by jibis on 22/02/2020.
//

#include <stdio.h>
#include <inttypes.h>

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
    uint8_t _byte;
    
    // Read the file one byte at a time
    for (; fread(&_byte, 1, 1, infile) ==1;) {
        printf("%02" PRIx8 " ", _byte);
    }


    // Close the file reader
    fclose(infile);
    return 0;
}