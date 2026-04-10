#include <stdint.h>
#include <stdlib.h>
#include <htslib/hts.h>
#include <htslib/tbx.h> // Including additional header for hts_idx_t

int LLVMFuzzerTestOneInput_161(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract all parameters
    if (size < sizeof(int) + 2 * sizeof(hts_pos_t) + sizeof(uint64_t) + sizeof(int)) {
        return 0;
    }

    // Initialize the parameters
    int param1 = *(int *)data;
    data += sizeof(int);

    hts_pos_t param2 = *(hts_pos_t *)data;
    data += sizeof(hts_pos_t);

    hts_pos_t param3 = *(hts_pos_t *)data;
    data += sizeof(hts_pos_t);

    uint64_t param4 = *(uint64_t *)data;
    data += sizeof(uint64_t);

    int param5 = *(int *)data;
    data += sizeof(int);

    // Create a mock hts_idx_t object
    hts_idx_t *idx = hts_idx_init(0, HTS_FMT_CSI, 0, 0, 0);

    if (idx != NULL) {
        // Call the function-under-test
        hts_idx_push(idx, param1, param2, param3, param4, param5);

        // Clean up
        hts_idx_destroy(idx);
    }

    return 0;
}