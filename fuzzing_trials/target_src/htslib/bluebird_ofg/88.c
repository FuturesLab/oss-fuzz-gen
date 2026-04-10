#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h"  // Include the appropriate header for sam_hdr_t

int LLVMFuzzerTestOneInput_88(const uint8_t *data, size_t size) {
    sam_hdr_t *hdr = NULL;
    char *id = NULL;

    if (size < 1) {
        return 0;
    }

    // Initialize a sam_hdr_t structure
    hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0;
    }

    // Ensure that the data is null-terminated to be used as a string
    id = (char *)malloc(size + 1);
    if (id == NULL) {
        sam_hdr_destroy(hdr);
        return 0;
    }
    memcpy(id, data, size);
    id[size] = '\0';

    // Add a dummy program header to the sam_hdr_t structure to make the test meaningful
    if (sam_hdr_add_line(hdr, "PG", "ID", "test", "PN", "fuzz", NULL) < 0) {
        free(id);
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Call the function-under-test
    const char *result = sam_hdr_pg_id(hdr, id);

    // Clean up
    free(id);
    sam_hdr_destroy(hdr);

    return 0;
}