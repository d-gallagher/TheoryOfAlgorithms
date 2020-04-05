// https://tools.ietf.org/html/rfc1321
// The MD5 Hash Algorithm.
// David Gallagher.

#include <stdio.h>
#include <inttypes.h>
#include "constants.c"
#include "functions.c"

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

int main(int argc, char *argv[]) {
    printf("System is %s-endian.\n",
           is_big_endian() ? "big" : "little");

    // Expect and open a single filename.
    if (argc != 2) {
        printf("Error: expected single filename as argument.\n");
        return 1;
    }

    FILE *infile = fopen(argv[1], "rb");
    if (!infile) {
        printf("Error: couldn't open file %s.\n", argv[1]);
        return 1;
    }

    WORD H[] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 };


    // The current padded message block.
    union BLOCK M;
    uint64_t numbits = 0;
    enum flag status = READ;


    while(nextBlock(&M, infile, &numbits, &status))
    {
        nexthash(&M, H);
    }
    
    printf("MD5 Output: \n");
    for (int i = 0; i < 4; i++){
        printf("%08" PRIx32 "", bswap_32(H[i]));
    }

    fclose(infile);
    return 0;
}
