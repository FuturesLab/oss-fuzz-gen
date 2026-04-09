#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_262(const uint8_t *data, size_t size) {
    sam_hdr_t *hdr = NULL;
    const char *region_str;
    int tid;
    hts_pos_t beg, end;
    int flags = 0;

    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the region string and copy data into it
    region_str = (const char *)malloc(size + 1);
    if (region_str == NULL) {
        return 0;
    }
    memcpy((char *)region_str, data, size);
    ((char *)region_str)[size] = '\0';

    // Call the function under test
    const char *result = sam_parse_region(hdr, region_str, &tid, &beg, &end, flags);

    // Free the allocated memory
    free((char *)region_str);

    return 0;
}