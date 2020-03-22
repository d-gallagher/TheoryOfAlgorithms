// https://tools.ietf.org/html/rfc1321
// The MD5 Hash Algorithm.
// David Gallagher.

#include <stdio.h>
#include <inttypes.h>

// Constants for MD5 transform routine taken direct from rfc1321
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21


// word as 32 bit integer
#define WORD uint32_t
// Rotate Left
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

#define F(x, y, z) ((x & y) | (~x & z))

#define G(x, y, z) ((x & z) | (y & ~z))

#define H(x, y, z) (x ^ y ^ z)

#define I(x, y, z) (y ^ (x | ~z))

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

// A sixty-four byte block of memory, accessed with different types.
// Represents the current block which has been read from the padded message
// The Union will consume 64 bytes of memory
// Can be read as an array of 64, 32 or 8 bit integers
typedef union
{
    uint64_t sixfour[8];
    WORD threetwo[16];
    uint8_t eight[64];
} BLOCK;

// Flags represent the four different states that next block may encounter:
// READ   - Still reading file
// PAD0   - (Not enough space to complete the padding in the current block but the 1 bit has been appended already)
// FINISH - Padding is complete.
typedef enum {READ, PAD0, FINISH} PADFLAG;
typedef enum {BIG, LITTLE} ENDIAN;

// Check endianness of machine
int is_big_endian(void)
{
    union {
        uint32_t i;
        char c[4];
    } e = { 0x01000000 };

    return e.c[0];
}

// MD5 specifies big endian byte order, but this implementation assumes a little
// endian byte order CPU. swap_endianness will swap from big-little or little-big
uint64_t  swap_endianness(uint64_t x){

    uint64_t mask[8];
    mask[0] = 0xff;
    for (int i = 1; i < 8; i++) {
        mask[i] = mask[0] << (8 * i);
    }
    uint64_t y =    (x >> 56) & mask[0]
                    ^ ((x >> 40) & mask[1])
                    ^ ((x >> 24) & mask[2])
                    ^ ((x >>  8) & mask[3])
                    ^ ((x <<  8) & mask[4])
                    ^ ((x << 24) & mask[5])
                    ^ ((x << 40) & mask[6])
                    ^ ((x << 56) & mask[7]);

    return y;
}
// Byte swap unsigned int Big to little endian
uint32_t bswap_32( uint32_t val )
{
    val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF );
    return (val << 16) | (val >> 16);
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

    fclose(infile);
    return 0;
}
