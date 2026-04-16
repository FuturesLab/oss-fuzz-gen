#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h"

int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for splitting into multiple strings
    if (size < 4) return 0;

    // Initialize sam_hdr_t structure
    sam_hdr_t *hdr = sam_hdr_init();
    if (!hdr) return 0;

    // Split the input data into four parts for the strings
    size_t part_size = size / 4;
    const char *type = (const char *)data;
    const char *id = (const char *)(data + part_size);
    const char *key = (const char *)(data + 2 * part_size);
    void *value = (void *)(data + 3 * part_size);

    // Ensure null-termination of strings
    char *type_str = strndup(type, part_size);
    char *id_str = strndup(id, part_size);
    char *key_str = strndup(key, part_size);

    // Call the function-under-test
    sam_hdr_update_line(hdr, type_str, id_str, key_str, value);

    // Free allocated memory
    free(type_str);
    free(id_str);
    free(key_str);
    sam_hdr_destroy(hdr);

    return 0;
}