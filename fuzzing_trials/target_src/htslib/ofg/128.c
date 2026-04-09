#include <stdint.h>
#include <stddef.h>
#include <htslib/sam.h>
#include <htslib/hts.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_128(const uint8_t *data, size_t size) {
    // Ensure there's enough data to work with
    if (size < 4) return 0;

    // Initialize htsFile
    htsFile *file = hts_open("/dev/null", "wb");
    if (!file) return 0;

    // Create a sam_hdr_t object
    sam_hdr_t *header = sam_hdr_init();
    if (!header) {
        hts_close(file);
        return 0;
    }

    // Set a simple header text
    if (sam_hdr_add_line(header, "HD", "VN", "1.0", NULL) < 0) {
        sam_hdr_destroy(header);
        hts_close(file);
        return 0;
    }

    // Use the first byte of data as the integer option
    int option = data[0];

    // Use the remaining data as a string for the filename
    char *filename = (char *)malloc(size);
    if (!filename) {
        sam_hdr_destroy(header);
        hts_close(file);
        return 0;
    }
    memcpy(filename, data + 1, size - 1);
    filename[size - 1] = '\0';  // Ensure null-termination

    // Call the function-under-test
    sam_idx_init(file, header, option, filename);

    // Clean up
    free(filename);
    sam_hdr_destroy(header);
    hts_close(file);

    return 0;
}