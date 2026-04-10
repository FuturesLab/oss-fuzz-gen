#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "htslib/sam.h"  // Assuming sam_hdr_t is defined in this header

int LLVMFuzzerTestOneInput_239(const uint8_t *data, size_t size) {
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0;
    }

    // Ensure the size is sufficient to create a string
    if (size < 1) {
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Create a null-terminated string from the input data
    char *pg_data = (char *)malloc(size + 1);
    if (pg_data == NULL) {
        sam_hdr_destroy(hdr);
        return 0;
    }
    memcpy(pg_data, data, size);
    pg_data[size] = '\0';

    // Call the function under test
    sam_hdr_add_pg(hdr, pg_data, NULL);

    // Clean up
    free(pg_data);
    sam_hdr_destroy(hdr);

    return 0;
}