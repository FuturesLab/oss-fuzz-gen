#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "/src/htslib/htslib/sam.h" // Correct path for sam_hdr_t type and function

int LLVMFuzzerTestOneInput_110(const uint8_t *data, size_t size) {
    // Initialize a SAM header with mock data
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0;
    }

    // Add a mock sequence to the header
    if (sam_hdr_add_line(hdr, "SQ", "SN:mock_seq", "LN:1000", NULL) < 0) {
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Allocate memory for the name, ensuring it is null-terminated
    char *name = (char *)malloc(size + 1);
    if (name == NULL) {
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Copy data to name and ensure it is null-terminated
    memcpy(name, data, size);
    name[size] = '\0';

    // Call the function-under-test
    int result = sam_hdr_name2tid(hdr, name);

    // Clean up
    sam_hdr_destroy(hdr);
    free(name);

    return 0;
}