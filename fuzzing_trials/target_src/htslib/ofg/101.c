#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_101(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Initialize the sam_hdr_t with some data
    // Assuming the data is a valid SAM header string for testing purposes
    char *header_str = (char *)malloc(size + 1);
    if (!header_str) {
        return 0;
    }
    memcpy(header_str, data, size);
    header_str[size] = '\0';

    // Parse the SAM header
    sam_hdr_t *hdr = sam_hdr_parse(size, header_str);
    if (!hdr) {
        free(header_str);
        return 0;
    }

    free(header_str);

    // Extract an integer from the data for the tid parameter
    int tid = *(int *)data;

    // Call the function-under-test
    hts_pos_t result = sam_hdr_tid2len(hdr, tid);

    // Clean up
    sam_hdr_destroy(hdr);

    return 0;
}