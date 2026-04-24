#include <stdint.h>
#include <stdlib.h>
#include <htslib/hts.h>
#include <htslib/hts_defs.h>
#include <htslib/tbx.h>
#include "/src/htslib/htslib/tbx.h"  // Use this path for hts_itr_query

int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for our needs
    if (size < sizeof(int) + 2 * sizeof(hts_pos_t)) {
        return 0;
    }

    // Initialize variables
    const hts_idx_t *idx = NULL;  // Initialize as NULL, as we can't directly cast from data
    int tid = *(const int *)(data);
    hts_pos_t beg = *(const hts_pos_t *)(data + sizeof(int));
    hts_pos_t end = *(const hts_pos_t *)(data + sizeof(int) + sizeof(hts_pos_t));
    hts_readrec_func *readrec_func = NULL;  // Assuming a NULL function pointer for fuzzing

    // Call the function-under-test
    hts_itr_t *itr = hts_itr_query(idx, tid, beg, end, readrec_func);

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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_20(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
