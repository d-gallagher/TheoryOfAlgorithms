// https://tools.ietf.org/html/rfc1321
// The MD5 Hash Algorithm.
// David Gallagher.

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

// Custom
#include "constants.c"
#include "functions.c"
void go_to_sleep(int seconds){
    Sleep(seconds);
}
// Processing functions for:
// Round 1
void FF(WORD *a, WORD b, WORD c, WORD d, WORD x, WORD s, WORD ac){
    *a += F(b, c, d) + x + ac;
    *a = b + ROTATE_LEFT(*a, s);
}
// Round 2
void GG(WORD *a, WORD b, WORD c, WORD d, WORD x, WORD s, WORD ac){
*a += G(b, c, d) + x + ac;
*a = b + ROTATE_LEFT(*a, s);
}
// Round 3
void HH(WORD *a, WORD b, WORD c, WORD d, WORD x, WORD s, WORD ac){
    *a += H(b, c, d) + x + ac;
    *a = b + ROTATE_LEFT(*a, s);
}
// Round 4
void II(WORD *a, WORD b, WORD c, WORD d, WORD x, WORD s, WORD ac){
    *a += I(b, c, d) + x + ac;
    *a = b + ROTATE_LEFT(*a, s);
}

/**
 * Check endianness of machine
 * e.c = 0001 (LITTLE endian) or 1000 (BIG endian)
 * @return 0 or 1
 */
int is_big_endian(void)
{
    union {
        uint32_t i;
        char c[4];
    } e = { 0x01000000 };
    return e.c[0];
}

/**
 * MD5 specifies big endian byte order, but this implementation assumes a little
 * endian byte order CPU. swap_endianness will swap from big-little or little-big
 * Byte swap unsigned int Big to little endian
 * @param val
 * @return
 */
uint32_t bswap_32( uint32_t val )
{
    val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF );
    return (val << 16) | (val >> 16);
}


/**
 * MD5 basic transformation. Transforms state based on block (RFC Comment - update description)
 * Each round performs 16 operations
 * @param M - union block
 * @param H - 32 bit unsigned integer
 */
void nexthash(union BLOCK *M, WORD *H)
{
    WORD a = H[0], b = H[1], c = H[2], d = H[3];

    // Round 1
    FF(&a, b, c, d, M->threetwo[0] , S11, K[0]);
    FF(&d, a, b, c, M->threetwo[1] , S12, K[1]);
    FF(&c, d, a, b, M->threetwo[2] , S13, K[2]);
    FF(&b, c, d, a, M->threetwo[3] , S14, K[3]);
    FF(&a, b, c, d, M->threetwo[4] , S11, K[4]);
    FF(&d, a, b, c, M->threetwo[5] , S12, K[5]);
    FF(&c, d, a, b, M->threetwo[6] , S13, K[6]);
    FF(&b, c, d, a, M->threetwo[7] , S14, K[7]);
    FF(&a, b, c, d, M->threetwo[8] , S11, K[8]);
    FF(&d, a, b, c, M->threetwo[9] , S12, K[9]);
    FF(&c, d, a, b, M->threetwo[10], S13, K[10]);
    FF(&b, c, d, a, M->threetwo[11], S14, K[11]);
    FF(&a, b, c, d, M->threetwo[12], S11, K[12]);
    FF(&d, a, b, c, M->threetwo[13], S12, K[13]);
    FF(&c, d, a, b, M->threetwo[14], S13, K[14]);
    FF(&b, c, d, a, M->threetwo[15], S14, K[15]);

    // Round 2
    GG(&a, b, c, d, M->threetwo[1] , S21, K[16]);
    GG(&d, a, b, c, M->threetwo[6] , S22, K[17]);
    GG(&c, d, a, b, M->threetwo[11], S23, K[18]);
    GG(&b, c, d, a, M->threetwo[0] , S24, K[19]);
    GG(&a, b, c, d, M->threetwo[5] , S21, K[20]);
    GG(&d, a, b, c, M->threetwo[10], S22, K[21]);
    GG(&c, d, a, b, M->threetwo[15], S23, K[22]);
    GG(&b, c, d, a, M->threetwo[4] , S24, K[23]);
    GG(&a, b, c, d, M->threetwo[9] , S21, K[24]);
    GG(&d, a, b, c, M->threetwo[14], S22, K[25]);
    GG(&c, d, a, b, M->threetwo[3] , S23, K[26]);
    GG(&b, c, d, a, M->threetwo[8] , S24, K[27]);
    GG(&a, b, c, d, M->threetwo[13], S21, K[28]);
    GG(&d, a, b, c, M->threetwo[2] , S22, K[29]);
    GG(&c, d, a, b, M->threetwo[7] , S23, K[30]);
    GG(&b, c, d, a, M->threetwo[12], S24, K[31]);

    // Round 3
    HH(&a, b, c, d, M->threetwo[5], S31, K[32]);
    HH(&d, a, b, c, M->threetwo[8], S32, K[33]);
    HH(&c, d, a, b, M->threetwo[11],S33, K[34]);
    HH(&b, c, d, a, M->threetwo[14],S34, K[35]);
    HH(&a, b, c, d, M->threetwo[1], S31, K[36]);
    HH(&d, a, b, c, M->threetwo[4], S32, K[37]);
    HH(&c, d, a, b, M->threetwo[7], S33, K[38]);
    HH(&b, c, d, a, M->threetwo[10],S34, K[39]);
    HH(&a, b, c, d, M->threetwo[13],S31, K[40]);
    HH(&d, a, b, c, M->threetwo[0], S32, K[41]);
    HH(&c, d, a, b, M->threetwo[3], S33, K[42]);
    HH(&b, c, d, a, M->threetwo[6], S34, K[43]);
    HH(&a, b, c, d, M->threetwo[9], S31, K[44]);
    HH(&d, a, b, c, M->threetwo[12],S32, K[45]);
    HH(&c, d, a, b, M->threetwo[15],S33, K[46]);
    HH(&b, c, d, a, M->threetwo[2], S34, K[47]);

    // Round 4
    II(&a, b, c, d, M->threetwo[0], S41, K[48]);
    II(&d, a, b, c, M->threetwo[7], S42, K[49]);
    II(&c, d, a, b, M->threetwo[14],S43, K[50]);
    II(&b, c, d, a, M->threetwo[5], S44, K[51]);
    II(&a, b, c, d, M->threetwo[12],S41, K[52]);
    II(&d, a, b, c, M->threetwo[3], S42, K[53]);
    II(&c, d, a, b, M->threetwo[10],S43, K[54]);
    II(&b, c, d, a, M->threetwo[1], S44, K[55]);
    II(&a, b, c, d, M->threetwo[8], S41, K[56]);
    II(&d, a, b, c, M->threetwo[15],S42, K[57]);
    II(&c, d, a, b, M->threetwo[6], S43, K[58]);
    II(&b, c, d, a, M->threetwo[13],S44, K[59]);
    II(&a, b, c, d, M->threetwo[4], S41, K[60]);
    II(&d, a, b, c, M->threetwo[11],S42, K[61]);
    II(&c, d, a, b, M->threetwo[2], S43, K[62]);
    II(&b, c, d, a, M->threetwo[9], S44, K[63]);


    H[0] += a;
    H[1] += b;
    H[2] += c;
    H[3] += d;
}

/**
 * Process the blocks from the message input.
 * @param M
 * @param inFile
 * @param numbits
 * @param status
 * @return
 */
int nextBlock(union BLOCK *M, FILE *inFile, uint64_t *numbits, PADFLAG *status)
{
    // Exit when padding is complete - Finish
    if ( *status == FINISH){ return 0; }

    // pad message with 0's to the end of the block
    if(*status == PAD0) {
        for (int i = 0; i < 56; i++) {
            M->eight[i] = 0x00;
        }
        M->sixfour[7] = *numbits;
        // Set padding status to FINISH
        *status = FINISH;
    }

    // Read in 64 * 1 byte items from infile and store in M.eight
    size_t numbytesread = fread(M->eight, 1, 64, inFile);
    // Count how many bits we read in
    *numbits += (8ULL * ((uint64_t) numbytesread));

    // There's enough space in the block to append 1 and finish padding
    if (numbytesread < 56)
    {
        // Append 1 bit to block
        M->eight[numbytesread] = 0x80;

        // pad block with zeros
        for(int i = numbytesread + 1; i < 56; i++)
        {
            M->eight[i] = 0x00;
        }
        // Append final byte (Original message length)
        M->sixfour[7] = *numbits;
        // Exit when padding is complete - Finish
        *status = FINISH;
        return 1;
    }

    // Not enough space tom complete padding in block
    // Append 1 to current block and pad zeros to end of block
    else if(numbytesread < 64)
    {
        // Append 1 bit to block
        M->eight[numbytesread] = 0x80;
        for (int i = numbytesread + 1; i < 64; i++)
        {
            M->eight[i] = 0x00;
        }
        // Swap to PAD0 and fill last block with padding.
        *status = PAD0;
    }

    return 1;
}

/**
 * Print --help menu
 */
void menu_no_args(){
    printf("=== MD5 Message Digest ===\n\n");

    // Menu - User can perform MD5 message digest on a given string or file
    printf("The following commands may be used:\n");
    printf("--help                           --> Prints help Menu.\n");
    printf("--test                           --> Run tests to verify MD5 hash.\n");
    printf("--check-endian                   --> Check system endianness.\n");
    printf("--version                        --> Check current version.\n");
    printf("--string 'type your string'      --> Type an input to hash.\n");
    printf("--file path/to/file.extension    --> Return the MD5 hash of file input.\n");
}
/**
 * Run tests to validate the MD5 calculates and outputs the correct encodings.
 * MD5 Test Suite taken from RFC1321
 * MD5 input                                                                          = MD5 encoding
 * ""                                                                                 = d41d8cd98f00b204e9800998ecf8427e
 * "a"                                                                                = 0cc175b9c0f1b6a831c399e269772661
 * "abc"                                                                              = 900150983cd24fb0d6963f7d28e17f72
 * "message digest"                                                                   = f96b697d7cb7938d525a2f31aaf161d0
 * "abcdefghijklmnopqrstuvwxyz"                                                       = c3fcd3d76192e4007dfb496cca67e13b
 * "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"                   = d174ab98d277d9f5a5611c2c9f419d9f
 * "12345678901234567890123456789012345678901234567890123456789012345678901234567890" = 57edf4a22be3c955ac49da2e2107b67a
 */
void run_tests(){
    printf("== Running MD5 Test Suite ==\n");
    /**================================== TEST 0 =======================================*/
    go_to_sleep(500);
    printf("Test 0...\n");
    printf("MD5 Test 0  : %s\n", MD5_Test_Outputs[0]);
    FILE* Test0 = getFile("Test0.txt");
    char* t0 = md5_file(Test0);
    printf("Output Str  : %s\n", t0);
    printf("Matching    : %s\n", strcmp(MD5_Test_Outputs[0], t0)==0? "true":"false");
    /**================================== TEST 1 =======================================*/
    go_to_sleep(500);
    printf("Test 1...\n");
    printf("MD5 Test 1  : %s\n", MD5_Test_Outputs[1]);
    FILE* Test1 = getFile("Test1.txt");
    char* t1 = md5_file(Test1);
    printf("Output Str  : %s\n", t1);
    printf("Matching    : %s\n", strcmp(MD5_Test_Outputs[1], t1)==0? "true":"false");
    /**================================== TEST 2 =======================================*/
    go_to_sleep(500);
    printf("Test 2...\n");
    printf("MD5 Test 2  : %s\n", MD5_Test_Outputs[2]);
    FILE* Test2 = getFile("Test2.txt");
    char* t2 = md5_file(Test2);
    printf("Output Str  : %s\n", t2);
    printf("Matching    : %s\n", strcmp(MD5_Test_Outputs[2], t2)==0? "true":"false");
    /**================================== TEST 3 =======================================*/
    go_to_sleep(500);
    printf("Test 3...\n");
    printf("MD5 Test 3  : %s\n", MD5_Test_Outputs[3]);
    FILE* Test3 = getFile("Test3.txt");
    char* t3 = md5_file(Test3);
    printf("Output Str  : %s\n", t3);
    printf("Matching    : %s\n", strcmp(MD5_Test_Outputs[3], t3)==0? "true":"false");
    /**================================== TEST 4 =======================================*/
    go_to_sleep(500);
    printf("Test 4...\n");
    printf("MD5 Test 4  : %s\n", MD5_Test_Outputs[4]);
    FILE* Test4 = getFile("Test4.txt");
    char* t4 = md5_file(Test4);
    printf("Output Str  : %s\n", t4);
    printf("Matching    : %s\n", strcmp(MD5_Test_Outputs[4], t4)==0? "true":"false");
    /**================================== TEST 5 =======================================*/
    go_to_sleep(500);
    printf("Test 5...\n");
    printf("MD5 Test 5  : %s\n", MD5_Test_Outputs[5]);
    FILE* Test5 = getFile("Test5.txt");
    char* t5 = md5_file(Test5);
    printf("Output Str  : %s\n", t5);
    printf("Matching    : %s\n", strcmp(MD5_Test_Outputs[5], t5)==0? "true":"false");
    /**================================== TEST 6 =======================================*/
    go_to_sleep(500);
    printf("Test 6...\n");
    printf("MD5 Test 6  : %s\n", MD5_Test_Outputs[6]);
    FILE* Test6 = getFile("Test6.txt");
    char* t6 = md5_file(Test6);
    printf("Output Str  : %s\n", t6);
    printf("Matching    : %s\n", strcmp(MD5_Test_Outputs[6], t6)==0? "true":"false");
    printf("Testing Complete...");
}

/**
 * Take file input from command line.
 * Process file
 * Closes file
 * Return MD5 hash as char array.
 * @param f
 * @return char*
 */
char* md5_file(FILE *f){
    // Init Word Constants
    WORD H[] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 };

    // The current padded message block.
    union BLOCK M;
    // Count the bits
    uint64_t numbits = 0;
    // Set the status flag
    PADFLAG status = READ;

    // Process the input in blocks
    while(nextBlock(&M, f, &numbits, &status))
    {
        nexthash(&M, H);
    }

    // Output the hash
    unsigned char block1[9];
    unsigned char block2[9];
    unsigned char block3[9];
    unsigned char block4[9];

//    printf("MD5 Output  : ");
//    for (int i = 0; i < 4; i++){
//        printf("%08" PRIx32 "", bswap_32(H[i]));
//    }

    snprintf(block1, 9, "%08x" PRIx32 "", bswap_32(H[0]));
    snprintf(block2, 9, "%08x" PRIx32 "", bswap_32(H[1]));
    snprintf(block3, 9, "%08x" PRIx32 "", bswap_32(H[2]));
    snprintf(block4, 9, "%08x" PRIx32 "", bswap_32(H[3]));
//    printf("\n" );
//    printf("snprintf    : %s", block1);
//    printf("%s", block2);
//    printf("%s", block3);
//    printf("%s", block4);
//    printf("\n" );

    char* finalOut = malloc(32);
    strncpy(finalOut, block1, 9);//finalOut += block1;
    strncat(finalOut, block2, 9);//finalOut += block1;
    strncat(finalOut, block3, 9);//finalOut += block1;
    strncat(finalOut, block4, 9);//finalOut += block1;
//    printf("Output Str  : %s\n", finalOut);
//

    // Close the file
    fclose(f);

    return finalOut;
}

/**
 * Take string input from command line.
 * Parse into file for md5 processing.
 * Save file and print MD5 hash.
 * @param c
 */
void string_to_file(char* c){
    // Allocate string input to file
    FILE* plaintext_file;
    // set file path
    char plaintext_file_path[] = "plaintext.txt";

    // open file for write operations
    plaintext_file = fopen(plaintext_file_path, "w");

    // check file not null
    if (plaintext_file == NULL)
    {
        printf("Error: Unable to process input to file ");
        exit(0);
    }

    // put the char contents to the file
    fputs(c, plaintext_file);

    // close file
    fclose(plaintext_file);
}

/**
 * Open file from given file name
 * @param c
 * @return opened file
 */
FILE * getFile(char* c){
    FILE *infile = NULL;
//    printf("Opening File: %s\n", c);
    infile = fopen(c, "rb");
    if (!infile) {
        printf("Error: An error occurred while processing the input string to file.\n");
        return NULL;
    }
    return infile;
}

int main(int argc,char *argv[]) {

//    // Debugging args
//    int ctr;
//    printf("argc %d: \n",argc);
//    for( ctr=0; ctr < argc; ctr++ )
//    {
//        printf("Input %d: ",ctr);
//        printf("argv: %s\n", argv[ctr] );
//    }

    // Check args
    if (argc < 2) {
        printf("Error: Expected input but none was entered..\n");
        printf("Enter --help for assistance.\n");
        return 1;
    }

    // --help command
    if(argc == 2 && strcmp(argv[1], "--help")==0){
        menu_no_args();
        return 0;
    }
    // --test command
    if(argc == 2 && strcmp(argv[1], "--test")==0){
        run_tests();
        return 0;
    }

    // --check-endian command
    if(argc == 2 && strcmp(argv[1], "--check-endian")==0){
        printf("System is %s-endian.\n",is_big_endian() ? "big" : "little");
        return 0;
    }

    // --version command
    if(argc == 2 && strcmp(argv[1], "--version")==0){
        printf("MD5 - Version 1.01\n");
        return 0;
    }
    // --string command (write to file and process)
    if(argc == 3 && strcmp(argv[1], "--string")==0){
        // parse input string to file
        string_to_file(argv[2]);
        // Open new file and continue (return 1)
//        FILE *infile = fopen("plaintext.txt", "rb");
//        if (!infile) {
//            printf("Error: An error occurred while processing the input string to file.\n");
//            return 1;
//        }
        FILE* infile = getFile("plaintext.txt");
        char* c = md5_file(infile);
        printf("Output Str  : %s\n", c);
    }// end --string

    // --file command (process input file)
    if(argc == 3 && strcmp(argv[1], "--file")==0){
//        FILE *infile = fopen(argv[2], "rb");
//        if (!infile) {
//            printf("Error: couldn't open file %s.\n", argv[2]);
//            return 1;
//        }
        FILE* infile = getFile(argv[2]);
        char* c = md5_file(infile);
        printf("Output Str  : %s\n", c);
    }// end --file

    // Terminate the program
    printf("Terminating program..");
    return 0;
}// end main



