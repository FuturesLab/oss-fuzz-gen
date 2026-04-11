#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_83(const uint8_t *data, size_t size) {
    // Initialize the sam_hdr_t structure
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0; // Return if initialization fails
    }

    // Ensure there is enough data to create non-null strings
    if (size < 5) {
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Split the input data into parts for the strings
    size_t part_size = size / 5;
    const char *str1 = (const char *)data;
    const char *str2 = (const char *)(data + part_size);
    const char *str3 = (const char *)(data + 2 * part_size);
    const char *str4 = (const char *)(data + 3 * part_size);
    const char *str5 = (const char *)(data + 4 * part_size);

    // Ensure null-termination of strings
    char *s1 = (char *)malloc(part_size + 1);
    char *s2 = (char *)malloc(part_size + 1);
    char *s3 = (char *)malloc(part_size + 1);
    char *s4 = (char *)malloc(part_size + 1);
    char *s5 = (char *)malloc(part_size + 1);

    if (!s1 || !s2 || !s3 || !s4 || !s5) {
        free(s1);
        free(s2);
        free(s3);
        free(s4);
        free(s5);
        sam_hdr_destroy(hdr);
        return 0;
    }

    memcpy(s1, str1, part_size);
    s1[part_size] = '\0';
    memcpy(s2, str2, part_size);
    s2[part_size] = '\0';
    memcpy(s3, str3, part_size);
    s3[part_size] = '\0';
    memcpy(s4, str4, part_size);
    s4[part_size] = '\0';
    memcpy(s5, str5, part_size);
    s5[part_size] = '\0';

    // Call the function-under-test
    sam_hdr_remove_tag_id(hdr, s1, s2, s3, s4);

    // Clean up
    free(s1);
    free(s2);
    free(s3);
    free(s4);
    free(s5);
    sam_hdr_destroy(hdr);

    return 0;
}