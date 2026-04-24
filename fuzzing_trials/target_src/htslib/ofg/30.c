#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <htslib/hts.h>

// Replacing the non-existent htslib/hts_idx.h with the correct header file
#include "/src/htslib/htslib/hts.h"

int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract parameters
    if (size < sizeof(int) + 2 * sizeof(hts_pos_t) + sizeof(uint64_t) + sizeof(int)) {
        return 0;
    }

    // Initialize the parameters from the input data
    int param1 = *(const int *)data;
    data += sizeof(int);
    size -= sizeof(int);

    hts_pos_t param2 = *(const hts_pos_t *)data;
    data += sizeof(hts_pos_t);
    size -= sizeof(hts_pos_t);

    hts_pos_t param3 = *(const hts_pos_t *)data;
    data += sizeof(hts_pos_t);
    size -= sizeof(hts_pos_t);

    uint64_t param4 = *(const uint64_t *)data;
    data += sizeof(uint64_t);
    size -= sizeof(uint64_t);

    int param5 = *(const int *)data;
    data += sizeof(int);
    size -= sizeof(int);

    // Allocate and initialize hts_idx_t
    hts_idx_t *idx = hts_idx_init(0, HTS_FMT_CSI, 0, 0, 0);

    // Call the function-under-test
    if (idx != NULL) {
        hts_idx_push(idx, param1, param2, param3, param4, param5);
        // Clean up
        hts_idx_destroy(idx);
    }

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

    LLVMFuzzerTestOneInput_30(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
