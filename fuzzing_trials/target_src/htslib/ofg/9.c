#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
    // Initialize the sam_hdr_t structure
    sam_hdr_t *header = sam_hdr_init();
    if (header == NULL) {
        return 0;
    }

    // Ensure the data is large enough to split into two non-NULL strings
    if (size < 2) {
        sam_hdr_destroy(header);
        return 0;
    }

    // Split the data into two strings
    size_t mid = size / 2;
    char *str1 = (char *)malloc(mid + 1);
    char *str2 = (char *)malloc(size - mid + 1);

    if (str1 == NULL || str2 == NULL) {
        free(str1);
        free(str2);
        sam_hdr_destroy(header);
        return 0;
    }

    memcpy(str1, data, mid);
    str1[mid] = '\0';
    memcpy(str2, data + mid, size - mid);
    str2[size - mid] = '\0';

    // Call the function-under-test
    sam_hdr_change_HD(header, str1, str2);

    // Clean up
    free(str1);
    free(str2);
    sam_hdr_destroy(header);

    return 0;
}