#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_39(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for creating a string and an integer
    if (size < 5) {
        return 0;
    }

    // Initialize sam_hdr_t
    sam_hdr_t *hdr = sam_hdr_init();
    if (!hdr) {
        return 0;
    }

    // Create a null-terminated string from the data
    size_t str_len = size - 4; // Reserve space for integer
    char *key = (char *)malloc(str_len + 1);
    if (!key) {
        sam_hdr_destroy(hdr);
        return 0;
    }
    memcpy(key, data, str_len);
    key[str_len] = '\0';

    // Extract an integer from the remaining data
    int pos = *(int *)(data + str_len);

    // Call the function-under-test
    int result = sam_hdr_remove_line_pos(hdr, key, pos);

    // Clean up
    free(key);
    sam_hdr_destroy(hdr);

    return 0;
}