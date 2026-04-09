#include <stdint.h>
#include <stddef.h>
#include <htslib/hts.h>
#include <htslib/tbx.h> // Include this for hts_idx_t and related functions

int LLVMFuzzerTestOneInput_162(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract multiple values
    if (size < sizeof(int) + 2 * sizeof(hts_pos_t) + sizeof(uint64_t) + sizeof(int)) {
        return 0;
    }

    // Initialize variables
    hts_idx_t *idx = hts_idx_init(0, HTS_FMT_CSI, 0, 0, 0); // Initialize with some default values
    if (!idx) {
        return 0; // Ensure idx is not NULL
    }

    int tid = *(int *)data;
    hts_pos_t beg = *(hts_pos_t *)(data + sizeof(int));
    hts_pos_t end = *(hts_pos_t *)(data + sizeof(int) + sizeof(hts_pos_t));
    uint64_t offset = *(uint64_t *)(data + sizeof(int) + 2 * sizeof(hts_pos_t));
    int is_mapped = *(int *)(data + sizeof(int) + 2 * sizeof(hts_pos_t) + sizeof(uint64_t));

    // Call the function-under-test
    int result = hts_idx_push(idx, tid, beg, end, offset, is_mapped);

    // Clean up
    hts_idx_destroy(idx);

    return 0;
}