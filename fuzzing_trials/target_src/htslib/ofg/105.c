#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient to create a null-terminated string
    if (size == 0) {
        return 0;
    }

    // Create a sam_hdr_t object
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0;
    }

    // Create a null-terminated string from the data
    char *line = (char *)malloc(size + 1);
    if (line == NULL) {
        sam_hdr_destroy(hdr);
        return 0;
    }
    memcpy(line, data, size);
    line[size] = '\0';

    // Call the function-under-test
    sam_hdr_add_line(hdr, line, NULL);

    // Clean up
    free(line);
    sam_hdr_destroy(hdr);

    return 0;
}