#include <stdio.h>
#include <inttypes.h>
/// Take an unsigned 8 bit integer and print the bits
/// Compare values at i & s using bitwise AND - (if both 1 then 1, else 0)
/// printf the result of the bitwise comparison, using ternary operator
/// \param s
void printbits(uint8_t s) {
    for (int i = (8 - 1); i >= 0; i--) {
        // 1ULL - Treat 1 as an Unsigned Long Long (Treat as a literal, not a variable)
        printf("%d", ((1ULL << i) & s) ? 1 : 0);
    }
    printf("\n");
}

int main(int argc, char *argv[]){
    uint8_t a = 73;
    uint8_t b = 99;
    uint8_t aANDb = (a & b);
    uint8_t aORb = (a | b);
    uint8_t aXORb = (a ^ b);


    printf("    b = "); printbits(b);
    printf("    a = "); printbits(a);
    printf("aANDb = "); printbits(aANDb);
    printf(" aORb = "); printbits(aORb);
    printf("aXORb = "); printbits(aXORb);

    printf("\n\n");

    printf("Tilde flips the bits..");
    printf(" a = "); printbits( a);
    printf("~a = "); printbits(~a);

    printf("\n\n");

    printf("<< Shift the bits..");
    printf(" 1       = "); printbits( 1      );
    printf("(1 << 3) = "); printbits((1 << 3));

    printf("\n\n");

    printf(" 99       = "); printbits(            99                   );
    printf("(99 << 3) = "); printbits((((uint8_t) 99) << ((uint8_t) 3)));

    printf("\n\n");

    printf("              99 = "); printbits(              99);
    printf("(1ULL << 5)      = "); printbits((1ULL << 5)     );
    printf("(1ULL << 5) & 99 = "); printbits((1ULL << 5) & 99);

    return 0;
}