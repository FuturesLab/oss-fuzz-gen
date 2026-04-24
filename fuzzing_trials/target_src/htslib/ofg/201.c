#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <htslib/hts.h>
#include <string.h>

// Function to create a copy of a string literal
char *copy_string_literal(const char *str) {
    size_t len = strlen(str) + 1;
    char *copy = (char *)malloc(len);
    if (copy != NULL) {
        strncpy(copy, str, len);
    }
    return copy;
}

int LLVMFuzzerTestOneInput_201(const uint8_t *data, size_t size) {
    // Allocate memory for hts_reglist_t
    hts_reglist_t *reglist = (hts_reglist_t *)malloc(sizeof(hts_reglist_t));
    if (reglist == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Initialize the hts_reglist_t structure with some non-NULL values
    reglist->reg = copy_string_literal("test_reg");
    if (reglist->reg == NULL) {
        free(reglist);
        return 0;
    }

    reglist->intervals = (hts_pair_pos_t *)malloc(sizeof(hts_pair_pos_t));
    if (reglist->intervals == NULL) {
        free(reglist->reg);
        free(reglist);
        return 0;
    }
    reglist->intervals[0].beg = 0;
    reglist->intervals[0].end = 100;
    reglist->count = 1;
    reglist->min_beg = 0;
    reglist->max_end = 100;

    // Use the first byte of the data as an integer parameter
    int is_sorted = size > 0 ? data[0] % 2 : 0;

    // Call the function-under-test
    hts_reglist_free(reglist, is_sorted);

    // Free allocated memory
    // Note: No need to free reglist->reg and reglist->intervals as hts_reglist_free should handle it

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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_201(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
