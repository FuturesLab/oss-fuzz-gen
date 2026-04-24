#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_164(const uint8_t *data, size_t size) {
    // Declare variables
    hts_idx_t *index = NULL;
    sam_hdr_t *header = NULL;
    char **regions = NULL;
    unsigned int n = 1; // Number of regions

    // Initialize regions with a non-NULL value
    regions = (char **)malloc(n * sizeof(char *));
    if (regions == NULL) {
        return 0;
    }
    regions[0] = (char *)malloc(size + 1);
    if (regions[0] == NULL) {
        free(regions);
        return 0;
    }
    memcpy(regions[0], data, size);
    regions[0][size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    hts_itr_t *itr = sam_itr_regarray(index, header, regions, n);

    // Clean up
    if (itr != NULL) {
        hts_itr_destroy(itr);
    }
    free(regions[0]);
    free(regions);

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

    LLVMFuzzerTestOneInput_164(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
