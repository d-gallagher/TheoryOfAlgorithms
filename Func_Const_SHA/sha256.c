// Sha - 256 bit version
// https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

// Constants (Cubed root of the first 64 primes, first 32 bits after the decimal point to integer then hex)
const uint32_t K[] ={
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
        0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
        0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
        0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
        0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
        0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
        0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
        0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
        0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};
// initial values for 'H' used in the algorithm (first 32 bits of the fractional parts of sqRoot of first 8 primes)
uint32_t H[] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

// Choose
uint32_t Ch(uint32_t x, uint32_t y, uint32_t z){
	return (x & y) ^ (~x & z);
}
// Majority
uint32_t Maj(uint32_t x, uint32_t y, uint32_t z){
    return (x & y) ^ (x & z) ^ (y & z);
}
// Shift Right
uint32_t SHR(uint32_t x, int n){
    return x >> n;
}
// Rotate Right
uint32_t ROTR(uint32_t x, int n){
    return (x >> n) | (x << (23 - n));
}
// Big Sigma Zero
uint32_t Sig0(uint32_t x){
    return ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22);
}
// Big Sigma One
uint32_t Sig1(uint32_t x){
    return ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25);
}
// Small Sigma Zero
uint32_t sig0(uint32_t x){
    return ROTR(x, 7) ^ ROTR(x, 18) ^ SHR(x, 3);
}
// Small Sigma one
uint32_t sig1(uint32_t x){
    return ROTR(x, 17) ^ ROTR(x, 19) ^ SHR(x, 10);
}

// Adding from Padding
// Represents the currrent block which has been read from the padded message
// Can be read as an array of 64, 32 or 8 bit integers
union block{
    uint64_t sixfour[8];
    uint32_t threetwo[16];
    uint8_t eight[64];
};

// Flags represent the four different states that nextblock may encounter:
// READ   - Still reading file
// PAD0   - Started padding zero's to end of message (Not enough space to complete the padding in the current block but the 1 bit has been appended already)
// PAD1   - Reached end of file requiring exactly one full block of padding. (The first bit of the padding will be a 1)
// FINISH - Padding is complete.
enum flag {READ, PAD0, FINISH};

// numbits is the number of bits we read form the file (reading file in blocks of x size)
// If numbits mod 512 (ULL = Unsingned long long) has a remainder, this is where we start padding.
// Hence the 512ULL minus the modulo of numbits to the 512.
uint64_t  numzerobytes(uint64_t numbits){
    uint64_t result = 512ULL - (numbits % 512ULL);

    // Check the size of result to decide padding
    // If there's not enough room in the last block to perform the padding, add another block.
    if(result < 65){
        result += 512;
    }

    // Make space for the 8 bits and the 64 bits which have to be included in the padding
    result -= 72;

    // Return the result as an 8bit ULL
    return (result / 8ULL);
}

// Track at which point the message has been padded
// Nextblock will read from infile into M.
// Track how many bytes have been read (to determine how much padding to apply), using numbits
// Set a status flag depending on the state it's at (Still reading file(READ), Started padding zero's(PAD0) ...
int nextblock (union block *M, FILE *infile, uint64_t *numbits, enum flag *status){

    // Check status before reading anything
    if (*status == FINISH) return 0;

    if (*status == PAD0){
        for (int i = 0; i < 56; i++) {
            M->eight[i] = 0;
        }
        M->sixfour[7] = *numbits;
        *status = FINISH;
        return 1;
    }
    
    // http://man7.org/linux/man-pages/man3/fread.3.html
    // Read in 64 * 1 byte items from infile and store in M.eight
    size_t numbytesread = fread(M->eight, 1, 64, infile);

    if (numbytesread == 64) return 1;

    // Fit all padding in last block if there is enough space (If less than 56 bits read then there is space..)
    if (numbytesread < 56){
        M->eight[numbytesread] = 0x80;
        for (int i = numbytesread + 1; i < 56; i++) {
            M->eight[i] = 0;
        }
        M->sixfour[7] = *numbits;
        *status = FINISH;
        return 1;
    }
    
    // 56 - 64 bytes read
    M->eight[numbytesread] = 0x80;
    for (int i = numbytesread + 1; i < 64; i++) {
        M->eight[i] = 0;
    }
    *status = PAD0;
    return 1;
}

// Block will be 512 bits
// Current hash value will be stored in an array of 32 bit unsigned integers.
void nexthash(union block *M, uint32_t *H){
    uint32_t W[64];
    uint32_t a, b, c, d, e, f, g, h, T1, T2;
    int t;

    // Prepare the message schedule
    for (t = 0; t < 16; t++) {
        W[t] = M->threetwo[t];
    }
    for (t = 16; t < 64; t++) {
        W[t] = sig1(W[t-2]) + W[t-7] + sig0(W[t-15]) + W[t-16];
    }

    // Init working variables with hash values
    a = H[0]; b = H[1]; c = H[2]; d = H[3];
    e = H[4]; f = H[5]; g = H[6]; h = H[7];

    for (t = 0; t < 64; t++) {
        T1 = h + Sig1(e) + Ch(e, f, g) + K[t] + W[t];
        T2 = Sig0(a) + Maj(a, b, c);
        h = g; g = f; f = e; e = d + T1;
        d = c; c = b; b = a; a = T1 + T2;
    }

    H[0] += a; H[1] += b ; H[2] += c; H[3] += d;
    H[4] += e; H[5] += f ; H[6] += g; H[7] += h;

}

int main(int argc, char *argv[]){

    // If No filename specified show error
    if (argc != 2){
        printf("Error.. Single filename expected as an argument.");
        return 1;
    }

    // File pointer
    FILE *infile = fopen(argv[1], "rb");

    // If can not open file show error
    if(!infile){
        printf("Error.. Could not open file: %s. \n", argv[1]);
        return 1;
    }

    // Current padded message block (read from the message of whatever finite length)
    union block M;
    uint64_t numbits = 0;
    enum flag status = READ;

    // Loop through the padded message blocks until the end of file
    // Pass nextblock() a pointer to M so that it can read into that memory location, the next 512 bits for the next block
    // - This is using the union data structure so 'M.eight' is an array of (64 * 8bit) unsigned integers into which can be read a byte at a time from the file.
    while(nextblock(&M, infile, &numbits, &status)){
        // Calculate the next hash value
        // 'H' is our initial hash value
         nexthash(&M, H);
    }

    for (int i = 0; i < 8; ++i) {
        printf("%02" PRIx32, H[i]);
    }
    printf("\n");

    // Close the file reader
    fclose(infile);
	return 0;
}
