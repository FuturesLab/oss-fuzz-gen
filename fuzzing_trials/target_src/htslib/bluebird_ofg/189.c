#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h"

int LLVMFuzzerTestOneInput_189(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to split into three non-NULL strings
    if (size < 4) {
        return 0;
    }

    // Allocate memory for sam_hdr_t
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0;
    }

    // Split the data into three parts for the three string parameters
    size_t len1 = data[0] % (size - 3);
    size_t len2 = data[1] % (size - len1 - 2);
    size_t len3 = data[2] % (size - len1 - len2 - 1);

    // Ensure that the lengths do not exceed the available data
    if (len1 + len2 + len3 + 3 > size) {
        sam_hdr_destroy(hdr);
        return 0;
    }

    const char *type = (const char *)(data + 3);
    const char *id = (const char *)(data + 3 + len1);
    const char *subtype = (const char *)(data + 3 + len1 + len2);

    // Ensure null-termination for strings
    char *type_str = (char *)malloc(len1 + 1);
    char *id_str = (char *)malloc(len2 + 1);
    char *subtype_str = (char *)malloc(len3 + 1);

    if (type_str == NULL || id_str == NULL || subtype_str == NULL) {
        free(type_str);
        free(id_str);
        free(subtype_str);
        sam_hdr_destroy(hdr);
        return 0;
    }

    memcpy(type_str, type, len1);
    type_str[len1] = '\0';

    memcpy(id_str, id, len2);
    id_str[len2] = '\0';

    memcpy(subtype_str, subtype, len3);
    subtype_str[len3] = '\0';

    // Check for valid type and id strings to prevent heap-buffer-overflow
    if (strlen(type_str) == 0 || strlen(id_str) == 0) {
        free(type_str);
        free(id_str);
        free(subtype_str);
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Call the function-under-test
    sam_hdr_remove_except(hdr, type_str, id_str, subtype_str);

    // Clean up
    free(type_str);
    free(id_str);
    free(subtype_str);
    sam_hdr_destroy(hdr);

    return 0;
}