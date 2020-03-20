// https://tools.ietf.org/html/rfc1321
// The MD5 Hash Algorithm.
// David Gallagher.

#include <stdio.h>
#include <inttypes.h>

// word as 32 bit integer
#define WORD uint32_t
// Rotate Left
#define ROTL(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

#define F(x, y, z) ((x & y) | (~x & z))

#define G(x, y, z) ((x & z) | (y & ~z))

#define H(x, y, z) (x ^ y ^ z)

#define I(x, y, z) (y ^ (x | ~z))
// Check endianness of machine
int is_big_endian(void)
{
    union {
        uint32_t i;
        char c[4];
    } e = { 0x01000000 };

    return e.c[0];
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
