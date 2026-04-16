#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_82(const uint8_t *data, size_t size) {
    sam_hdr_t *hdr = sam_hdr_init();
    if (!hdr) {
        return 0;
    }

    // Ensure the size is large enough to split into multiple strings
    if (size < 5) {
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Split the input data into multiple strings
    size_t part_size = size / 5;
    char *str1 = (char *)malloc(part_size + 1);
    char *str2 = (char *)malloc(part_size + 1);
    char *str3 = (char *)malloc(part_size + 1);
    char *str4 = (char *)malloc(part_size + 1);
    char *str5 = (char *)malloc(size - 4 * part_size + 1);

    if (!str1 || !str2 || !str3 || !str4 || !str5) {
        free(str1);
        free(str2);
        free(str3);
        free(str4);
        free(str5);
        sam_hdr_destroy(hdr);
        return 0;
    }

    memcpy(str1, data, part_size);
    str1[part_size] = '\0';
    memcpy(str2, data + part_size, part_size);
    str2[part_size] = '\0';
    memcpy(str3, data + 2 * part_size, part_size);
    str3[part_size] = '\0';
    memcpy(str4, data + 3 * part_size, part_size);
    str4[part_size] = '\0';
    memcpy(str5, data + 4 * part_size, size - 4 * part_size);
    str5[size - 4 * part_size] = '\0';

    // Call the function-under-test
    sam_hdr_remove_tag_id(hdr, str1, str2, str3, str4);

    // Clean up
    free(str1);
    free(str2);
    free(str3);
    free(str4);
    free(str5);
    sam_hdr_destroy(hdr);

    return 0;
}