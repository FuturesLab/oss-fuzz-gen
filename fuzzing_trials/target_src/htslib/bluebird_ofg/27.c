#include <stdint.h>
#include <stdlib.h>
#include "htslib/sam.h"
#include <string.h>

int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    // Initialize variables
    samFile *file = sam_open("/dev/null", "w"); // Open a dummy file for writing
    sam_hdr_t *header = sam_hdr_init();         // Initialize a SAM header

    // Ensure that the header is not NULL
    if (header == NULL) {
        sam_close(file);
        return 0;
    }

    // Allocate a buffer and copy the input data, appending a null terminator
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        sam_hdr_destroy(header);
        sam_close(file);
        return 0;
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Attempt to parse the null-terminated input data as a SAM header
    sam_hdr_t *parsed_header = sam_hdr_parse(size, null_terminated_data);
    if (parsed_header == NULL) {
        free(null_terminated_data);
        sam_hdr_destroy(header);
        sam_close(file);
        return 0;
    }

    // Write the header to the file
    if (sam_hdr_write(file, parsed_header) < 0) {
        sam_hdr_destroy(parsed_header);
        free(null_terminated_data);
        sam_close(file);
        return 0;
    }

    // Clean up
    sam_hdr_destroy(parsed_header);
    free(null_terminated_data);
    sam_hdr_destroy(header);
    sam_close(file);

    return 0;
}