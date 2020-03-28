/**
 * Flags represent the four different states that next block may encounter:
 * READ   - Still reading file
 * PAD0   - (Not enough space to complete the padding in the current block but the 1 bit has been appended already)
 * FINISH - Padding is complete.
*/
typedef enum {READ, PAD0, FINISH} PADFLAG;
/**
 * BIG    - System is big endian
 * LITTLE - System is little endian
*/
typedef enum {BIG, LITTLE} ENDIAN;