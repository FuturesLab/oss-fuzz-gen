#include <stdint.h>
#include <stdlib.h>
#include <htslib/hts.h>
#include <htslib/hts_defs.h>
#include <htslib/vcf.h>
#include <htslib/tbx.h> // Include necessary library for hts_idx_t

// Define a dummy hts_id2name_f function outside of LLVMFuzzerTestOneInput
const char *dummy_id2name(void *data, int tid) {
    return "dummy_seqname";
}

int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
    // Initialize necessary variables
    tbx_t *tbx = tbx_index_load2("dummy.vcf", NULL); // Correctly use tbx_t type for tbx_index_load2
    if (!tbx) {
        return 0; // Return if index loading fails
    }
    int num_seqnames = 0;
    void *usr_data = (void *)data;

    hts_id2name_f id2name_func = dummy_id2name;

    // Call the function under test
    const char **seqnames = tbx_seqnames(tbx, &num_seqnames); // Use tbx_seqnames for tbx_t type

    // Clean up
    tbx_destroy(tbx); // Use appropriate function to free tbx_t

    return 0;
}