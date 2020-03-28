#include "enums.c"
#include "unions.c"

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

#define F(x, y, z) ((x & y) | (~x & z))

#define G(x, y, z) ((x & z) | (y & ~z))

#define H(x, y, z) (x ^ y ^ z)

#define I(x, y, z) (y ^ (x | ~z))

uint32_t bswap_32( uint32_t val );
int is_big_endian(void);

void nexthash(union BLOCK *M, WORD *H);
int nextBlock(union BLOCK *M, FILE *inFile, uint64_t *numbits, PADFLAG *status);
