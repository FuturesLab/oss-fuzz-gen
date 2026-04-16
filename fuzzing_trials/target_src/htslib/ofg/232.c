#include <stdint.h>
#include <stdlib.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_232(const uint8_t *data, size_t size) {
    // Ensure there is enough data to proceed
    if (size < sizeof(int) + sizeof(hts_pos_t) + sizeof(int)) {
        return 0;
    }

    // Initialize variables
    bam_mplp_t mplp = (bam_mplp_t)data;  // Assuming data can be cast to bam_mplp_t
    int n_plp;
    hts_pos_t pos;
    int tid;
    const bam_pileup1_t *plp;

    // Extract values from data
    n_plp = *(int *)data;
    data += sizeof(int);
    size -= sizeof(int);

    pos = *(hts_pos_t *)data;
    data += sizeof(hts_pos_t);
    size -= sizeof(hts_pos_t);

    tid = *(int *)data;
    data += sizeof(int);
    size -= sizeof(int);

    // Call the function-under-test
    int result = bam_mplp64_auto(mplp, &tid, &pos, &n_plp, &plp);

    // Return zero to indicate successful execution
    return 0;
}