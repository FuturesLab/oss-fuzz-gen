#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/hts.h"
#include "/src/htslib/htslib/regidx.h" // Include the necessary header for hts_reglist_t

int LLVMFuzzerTestOneInput_85(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0; // Exit early if size is zero to prevent unnecessary operations
    }

    // Allocate memory for hts_reglist_t
    hts_reglist_t *reglist = (hts_reglist_t *)malloc(sizeof(hts_reglist_t));
    if (reglist == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Initialize the hts_reglist_t structure
    reglist->reg = (char *)malloc(size + 1);
    if (reglist->reg == NULL) {
        free(reglist);
        return 0; // Exit if memory allocation fails
    }
    memcpy((char *)reglist->reg, data, size);
    ((char *)reglist->reg)[size] = '\0'; // Null-terminate the string

    reglist->intervals = (hts_pair_pos_t *)malloc(sizeof(hts_pair_pos_t));
    if (reglist->intervals == NULL) {
        free((char *)reglist->reg);
        free(reglist);
        return 0; // Exit if memory allocation fails
    }
    reglist->count = 1; // Set the count of intervals

    // Properly initialize the interval to avoid use-after-free
    reglist->intervals[0].beg = 0;
    reglist->intervals[0].end = size; // Set some valid range

    // Call the function under test
    // Note: hts_reglist_free should handle freeing reglist->reg and reglist->intervals
    hts_reglist_free(reglist, 1);

    // Clean up
    // Remove the manual free of reglist, as hts_reglist_free should handle it
    // free(reglist);

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_85(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
