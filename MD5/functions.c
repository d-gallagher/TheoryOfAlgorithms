#include "enums.c"
#include "unions.c"

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))
#define F(x, y, z) ((x & y) | (~x & z))
#define G(x, y, z) ((x & z) | (y & ~z))
#define H(x, y, z) (x ^ y ^ z)
#define I(x, y, z) (y ^ (x | ~z))

void FF(WORD *a, WORD b, WORD c, WORD d, WORD x, WORD s, WORD ac);
void GG(WORD *a, WORD b, WORD c, WORD d, WORD x, WORD s, WORD ac);
void HH(WORD *a, WORD b, WORD c, WORD d, WORD x, WORD s, WORD ac);
void II(WORD *a, WORD b, WORD c, WORD d, WORD x, WORD s, WORD ac);

uint32_t bswap_32( uint32_t val );
int is_big_endian(void);
void go_to_sleep(int miliseconds);
void nexthash(union BLOCK *M, WORD *H);
int nextBlock(union BLOCK *M, FILE *inFile, uint64_t *numbits, PADFLAG *status);
char* md5_file(FILE *f);
int string_to_file(char* c);
void run_all_tests();
void menu_no_args();
FILE * getFile(char* c);
void run_hash_comparison_test(int testID, char* testFile, const char *expected);
