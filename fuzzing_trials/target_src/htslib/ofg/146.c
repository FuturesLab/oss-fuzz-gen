#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/hts.h>
#include <htslib/hts_defs.h>

// Replace the non-existent hts_idx.h with the correct header
#include "/src/htslib/htslib/hts.h"  // Correct path for hts_idx_t and related functions

int LLVMFuzzerTestOneInput_146(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create meaningful inputs
    if (size < 3) {
        return 0;
    }

    // Initialize hts_idx_t object
    hts_idx_t *index = hts_idx_init(HTS_FMT_BAI, 0, 0, 0, 0);

    // Prepare file name strings
    char filename1[256];
    char filename2[256];

    // Ensure null-termination
    size_t len1 = size / 2 < 255 ? size / 2 : 255;
    size_t len2 = size - len1 < 255 ? size - len1 : 255;

    memcpy(filename1, data, len1);
    filename1[len1] = '\0';

    memcpy(filename2, data + len1, len2);
    filename2[len2] = '\0';

    // Use a non-zero integer for the flags parameter
    int flags = 1;

    // Call the function-under-test
    hts_idx_save_as(index, filename1, filename2, flags);

    // Clean up
    hts_idx_destroy(index);

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

    LLVMFuzzerTestOneInput_146(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
