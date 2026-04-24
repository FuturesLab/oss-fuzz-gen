#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "htslib/sam.h"
#include "htslib/hts.h"

int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
    // We can't use sizeof(hts_idx_t) because it's an incomplete type.
    // Instead, we assume a minimum size required for the rest of the data.
    const size_t min_size = sizeof(int) + 2 * sizeof(hts_pos_t);
    
    if (size < min_size) {
        return 0;
    }

    // Initialize the parameters for sam_itr_queryi
    // We skip the part of the data that would represent hts_idx_t
    const hts_idx_t *idx = NULL; // We cannot derive this from data directly.
    int tid = *((int *)(data));
    hts_pos_t beg = *((hts_pos_t *)(data + sizeof(int)));
    hts_pos_t end = *((hts_pos_t *)(data + sizeof(int) + sizeof(hts_pos_t)));

    // Call the function-under-test
    hts_itr_t *itr = sam_itr_queryi(idx, tid, beg, end);

    // Clean up if necessary
    if (itr != NULL) {
        hts_itr_destroy(itr);
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_52(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
