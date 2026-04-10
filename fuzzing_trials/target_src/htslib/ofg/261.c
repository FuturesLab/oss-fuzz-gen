#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_261(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for meaningful parsing
    if (size < 10) {
        return 0;
    }

    // Initialize sam_hdr_t structure
    sam_hdr_t *hdr = sam_hdr_init();
    if (!hdr) {
        return 0;
    }

    // Allocate memory for region string and ensure it's null-terminated
    char *region = (char *)malloc(size + 1);
    if (!region) {
        sam_hdr_destroy(hdr);
        return 0;
    }
    memcpy(region, data, size);
    region[size] = '\0';

    // Initialize other parameters for sam_parse_region
    int tid = 0;
    hts_pos_t beg = 0, end = 0;
    int flags = 0; // Example flag value

    // Call the function-under-test
    const char *result = sam_parse_region(hdr, region, &tid, &beg, &end, flags);

    // Cleanup
    free(region);
    sam_hdr_destroy(hdr);

    return 0;
}