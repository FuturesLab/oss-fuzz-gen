#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h"

int LLVMFuzzerTestOneInput_232(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to extract an integer and non-empty header
    if (size < sizeof(int) + 1) {
        return 0;
    }

    // Initialize sam_hdr_t object
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0;
    }

    // Create a temporary buffer for the header text
    char *header_text = (char *)malloc(size + 1);
    if (header_text == NULL) {
        sam_hdr_destroy(hdr);
        return 0;
    }
    memcpy(header_text, data, size);
    header_text[size] = '\0';

    // Parse the header text into the sam_hdr_t object
    if (sam_hdr_add_lines(hdr, header_text, size) != 0) {
        free(header_text);
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Ensure there is at least one reference in the header
    if (sam_hdr_nref(hdr) == 0) {
        free(header_text);
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Extract an integer from the data to use as tid
    int tid;
    memcpy(&tid, data, sizeof(int));
    tid = abs(tid) % sam_hdr_nref(hdr); // Ensure tid is within valid range

    // Call the function-under-test
    const char *name = sam_hdr_tid2name(hdr, tid);

    // Check if name is not NULL to ensure valid output
    if (name != NULL) {
        // Use the name in some way, e.g., print or log it
        // For fuzzing, we just ensure it doesn't crash
    }

    // Clean up
    free(header_text);
    sam_hdr_destroy(hdr);

    return 0;
}