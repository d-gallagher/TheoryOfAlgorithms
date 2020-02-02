#include <stdio.h>
#include <inttypes.h>
/// Take an unsigned 64 bit integer and print the bits
/// Compare values at i & s using bitwise AND (both 1 = 1, else =0)
/// printf the result of the bitwise comparison, using ternary operator
/// \param s
void printbits(uint64_t s) {
  for (int i = 63; i >= 0; i--)
      // 1ULL - Treat 1 as an Unsigned Long Long (Treat as a literal, not a variable)
    printf("%d", ((1ULL << i) & s) ? 1 : 0);
}

int main(int argc, char *argv[]){
  uint64_t s = 65;

  printbits(s);
  printf("\t%llx\t%lld\n", s, s);

  return 0;
}