#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h> // Assuming the sam_hdr_t is defined in this header

int LLVMFuzzerTestOneInput_111(const uint8_t *data, size_t size) {
    sam_hdr_t *header;
    char *name;

    // Initialize sam_hdr_t object
    header = sam_hdr_init();
    if (header == NULL) {
        return 0;
    }

    // Add a dummy header line to the sam_hdr_t object to simulate a real scenario
    if (sam_hdr_add_line(header, "SQ", "SN:chr1", "LN:248956422", NULL) != 0) {
        sam_hdr_destroy(header);
        return 0;
    }

    // Ensure the data has a null-terminated string
    name = (char *)malloc(size + 1);
    if (name == NULL) {
        sam_hdr_destroy(header);
        return 0;
    }
    memcpy(name, data, size);
    name[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    int tid = sam_hdr_name2tid(header, name);

    // Clean up
    free(name);
    sam_hdr_destroy(header);

    return 0;
}