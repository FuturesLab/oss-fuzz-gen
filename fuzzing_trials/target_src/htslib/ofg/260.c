#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>
#include <htslib/hts.h>
#include <htslib/bgzf.h> // Include necessary for hts_idx_load and sam_hdr_read

int LLVMFuzzerTestOneInput_260(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for creating a non-empty string
    if (size < 2) return 0;

    // Create a null-terminated string from the input data
    size_t str_size = size - 1;
    char *region = (char *)malloc(str_size + 1);
    if (region == NULL) {
        return 0;
    }
    memcpy(region, data, str_size);
    region[str_size] = '\0';

    // Create an array of strings
    char *regions[] = {region};

    // Open a dummy BGZF file to create a valid htsFile pointer
    BGZF *bgzf = bgzf_open("/dev/null", "r");
    if (bgzf == NULL) {
        free(region);
        return 0;
    }

    // Load a dummy index and header
    hts_idx_t *idx = hts_idx_load("/dev/null", HTS_FMT_BAI);
    sam_hdr_t *hdr = sam_hdr_read(bgzf);

    if (idx == NULL || hdr == NULL) {
        free(region);
        if (idx) hts_idx_destroy(idx);
        if (hdr) sam_hdr_destroy(hdr);
        bgzf_close(bgzf);
        return 0;
    }

    // Call the function-under-test
    hts_itr_t *itr = sam_itr_regarray(idx, hdr, regions, 1);

    // Clean up
    free(region);
    hts_idx_destroy(idx);
    sam_hdr_destroy(hdr);
    bgzf_close(bgzf);
    if (itr != NULL) {
        hts_itr_destroy(itr);
    }

    return 0;
}