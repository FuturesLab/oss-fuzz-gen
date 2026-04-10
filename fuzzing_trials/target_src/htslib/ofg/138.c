#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>
#include <htslib/kstring.h>

int LLVMFuzzerTestOneInput_138(const uint8_t *data, size_t size) {
    // Initialize the parameters for sam_hdr_find_line_id
    sam_hdr_t *hdr = sam_hdr_init();
    const char *type = "HD"; // Example type, can be varied
    const char *id = "VN";   // Example id, can be varied
    const char *val = "1.0"; // Example value, can be varied
    kstring_t ks;
    ks.l = 0;
    ks.m = size;
    ks.s = (char *)malloc(size + 1);
    
    if (ks.s == NULL) {
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Copy data into kstring_t
    memcpy(ks.s, data, size);
    ks.s[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    int result = sam_hdr_find_line_id(hdr, type, id, val, &ks);

    // Clean up
    free(ks.s);
    sam_hdr_destroy(hdr);

    return 0;
}