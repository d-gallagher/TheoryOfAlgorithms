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
 * @param M
 * @param H
 */
void nexthash(union BLOCK *M, WORD *H)
{
    WORD a = H[0], b = H[1], c = H[2], d = H[3];

    // Round 1
    FF(&a, b, c, d, M->threetwo[0] , S11, 0xd76aa478);
    FF(&d, a, b, c, M->threetwo[1] , S12, 0xe8c7b756);
    FF(&c, d, a, b, M->threetwo[2] , S13, 0x242070db);
    FF(&b, c, d, a, M->threetwo[3] , S14, 0xc1bdceee);
    FF(&a, b, c, d, M->threetwo[4] , S11, 0xf57c0faf);
    FF(&d, a, b, c, M->threetwo[5] , S12, 0x4787c62a);
    FF(&c, d, a, b, M->threetwo[6] , S13, 0xa8304613);
    FF(&b, c, d, a, M->threetwo[7] , S14, 0xfd469501);
    FF(&a, b, c, d, M->threetwo[8] , S11, 0x698098d8);
    FF(&d, a, b, c, M->threetwo[9] , S12, 0x8b44f7af);
    FF(&c, d, a, b, M->threetwo[10], S13, 0xffff5bb1);
    FF(&b, c, d, a, M->threetwo[11], S14, 0x895cd7be);
    FF(&a, b, c, d, M->threetwo[12], S11, 0x6b901122);
    FF(&d, a, b, c, M->threetwo[13], S12, 0xfd987193);
    FF(&c, d, a, b, M->threetwo[14], S13, 0xa679438e);
    FF(&b, c, d, a, M->threetwo[15], S14, 0x49b40821);

    // Round 2
    GG(&a, b, c, d, M->threetwo[1] , S21, 0xf61e2562);
    GG(&d, a, b, c, M->threetwo[6] , S22, 0xc040b340);
    GG(&c, d, a, b, M->threetwo[11], S23, 0x265e5a51);
    GG(&b, c, d, a, M->threetwo[0] , S24, 0xe9b6c7aa);
    GG(&a, b, c, d, M->threetwo[5] , S21, 0xd62f105d);
    GG(&d, a, b, c, M->threetwo[10], S22, 0x02441453);
    GG(&c, d, a, b, M->threetwo[15], S23, 0xd8a1e681);
    GG(&b, c, d, a, M->threetwo[4] , S24, 0xe7d3fbc8);
    GG(&a, b, c, d, M->threetwo[9] , S21, 0x21e1cde6);
    GG(&d, a, b, c, M->threetwo[14], S22, 0xc33707d6);
    GG(&c, d, a, b, M->threetwo[3] , S23, 0xf4d50d87);
    GG(&b, c, d, a, M->threetwo[8] , S24, 0x455a14ed);
    GG(&a, b, c, d, M->threetwo[13], S21, 0xa9e3e905);
    GG(&d, a, b, c, M->threetwo[2] , S22, 0xfcefa3f8);
    GG(&c, d, a, b, M->threetwo[7] , S23, 0x676f02d9);
    GG(&b, c, d, a, M->threetwo[12], S24, 0x8d2a4c8a);

    // Round 3
    HH(&a, b, c, d, M->threetwo[5], S31, 0xfffa3942);
    HH(&d, a, b, c, M->threetwo[8], S32, 0x8771f681);
    HH(&c, d, a, b, M->threetwo[11],S33, 0x6d9d6122);
    HH(&b, c, d, a, M->threetwo[14],S34, 0xfde5380c);
    HH(&a, b, c, d, M->threetwo[1], S31, 0xa4beea44);
    HH(&d, a, b, c, M->threetwo[4], S32, 0x4bdecfa9);
    HH(&c, d, a, b, M->threetwo[7], S33, 0xf6bb4b60);
    HH(&b, c, d, a, M->threetwo[10],S34, 0xbebfbc70);
    HH(&a, b, c, d, M->threetwo[13],S31, 0x289b7ec6);
    HH(&d, a, b, c, M->threetwo[0], S32, 0xeaa127fa);
    HH(&c, d, a, b, M->threetwo[3], S33, 0xd4ef3085);
    HH(&b, c, d, a, M->threetwo[6], S34, 0x04881d05);
    HH(&a, b, c, d, M->threetwo[9], S31, 0xd9d4d039);
    HH(&d, a, b, c, M->threetwo[12],S32, 0xe6db99e5);
    HH(&c, d, a, b, M->threetwo[15],S33, 0x1fa27cf8);
    HH(&b, c, d, a, M->threetwo[2], S34, 0xc4ac5665);

    // Round 4
    II(&a, b, c, d, M->threetwo[0], S41, 0xf4292244);
    II(&d, a, b, c, M->threetwo[7], S42, 0x432aff97);
    II(&c, d, a, b, M->threetwo[14],S43, 0xab9423a7);
    II(&b, c, d, a, M->threetwo[5], S44, 0xfc93a039);
    II(&a, b, c, d, M->threetwo[12],S41, 0x655b59c3);
    II(&d, a, b, c, M->threetwo[3], S42, 0x8f0ccc92);
    II(&c, d, a, b, M->threetwo[10],S43, 0xffeff47d);
    II(&b, c, d, a, M->threetwo[1], S44, 0x85845dd1);
    II(&a, b, c, d, M->threetwo[8], S41, 0x6fa87e4f);
    II(&d, a, b, c, M->threetwo[15],S42, 0xfe2ce6e0);
    II(&c, d, a, b, M->threetwo[6], S43, 0xa3014314);
    II(&b, c, d, a, M->threetwo[13],S44, 0x4e0811a1);
    II(&a, b, c, d, M->threetwo[4], S41, 0xf7537e82);
    II(&d, a, b, c, M->threetwo[11],S42, 0xbd3af235);
    II(&c, d, a, b, M->threetwo[2], S43, 0x2ad7d2bb);
    II(&b, c, d, a, M->threetwo[9], S44, 0xeb86d391);


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

    printf("Empty String MD5:\nd41d8cd98f00b204e9800998ecf8427e\n");


    printf("bswap_32 test \n");
    for (int i = 0; i < 4; i++){
        printf("%08" PRIx32 "", bswap_32(H[i]));
    }
    printf("\n");
    printf("bswap_32 test \n");
    for (int i = 0; i < 4; i++){
        printf("%08" PRIx32 "", bswap_32(H[i]));
    }

    fclose(infile);
    return 0;
}
