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
union BLOCK
{
    uint64_t sixfour[8];
    uint32_t threetwo[16];
    uint8_t eight[64];
};

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

uint64_t bswap_64( uint64_t val )
{
    val = ((val << 8) & 0xFF00FF00FF00FF00ULL ) | ((val >> 8) & 0x00FF00FF00FF00FFULL );
    val = ((val << 16) & 0xFFFF0000FFFF0000ULL ) | ((val >> 16) & 0x0000FFFF0000FFFFULL );
    return (val << 32) | (val >> 32);
}

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

    printf("Empty String MD5:\nd41d8cd98f00b204e9800998ecf8427e\n");
    printf("No bswap test\n");
    for (int i = 0; i < 4; i++){
        printf("%08" PRIx32 "", H[i]);
    }
    printf("\n");

    printf("bswap_32 test \n");
    for (int i = 0; i < 4; i++){
        printf("%08" PRIx32 "", bswap_32(H[i]));
    }
    printf("\n");
    printf("bswap_64 test \n");

    for (int i = 0; i < 4; i++){
        printf("%08" PRIx32 "", bswap_64(H[i]));
    }
    printf("\n");
    printf("swap_endianness test \n");
    for (int i = 0; i < 4; i++){
        printf("%08" PRIx32 "", swap_endianness(H[i]));
    }
    printf("\n");

    fclose(infile);
    return 0;
}
