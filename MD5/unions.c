/**
 * A sixty-four byte block of memory, accessed with different types.
 * Represents the current block which has been read from the padded message
 * The Union will consume 64 bytes of memory
 * Can be read as an array of 64, 32 or 8 bit integers
 */
union BLOCK
{
    uint64_t sixfour[8];
    uint32_t threetwo[16];
    uint8_t eight[64];
};