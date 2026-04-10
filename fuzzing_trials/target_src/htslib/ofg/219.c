#include <stdint.h>
#include <stdlib.h>
#include <htslib/sam.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_219(const uint8_t *data, size_t size) {
    // Check if the input size is sufficient for our needs
    if (size < sizeof(int) + 2 * sizeof(hts_pos_t)) {
        return 0;
    }

    // Initialize variables for the function parameters
    const hts_idx_t *idx = NULL; // We cannot assume data contains a valid hts_idx_t structure
    int tid = *(const int *)data;
    hts_pos_t beg = *(const hts_pos_t *)(data + sizeof(int));
    hts_pos_t end = *(const hts_pos_t *)(data + sizeof(int) + sizeof(hts_pos_t));

    // Call the function-under-test
    hts_itr_t *itr = sam_itr_queryi(idx, tid, beg, end);

    // Clean up if necessary
    if (itr != NULL) {
        hts_itr_destroy(itr);
    }

    return 0;
}