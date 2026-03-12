#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_311(const uint8_t *data, size_t size) {
    // Ensure that the input data is large enough to extract strings
    if (size < 4) {
        return 0;
    }

    // Allocate a cmsMLU structure
    cmsMLU *mlu = cmsMLUalloc(NULL, 1);

    // Extract strings from the data
    size_t str1_len = data[0] % (size - 1) + 1; // Ensure non-zero length
    size_t str2_len = data[1] % (size - str1_len - 1) + 1;
    size_t str3_len = data[2] % (size - str1_len - str2_len - 1) + 1;

    // Ensure that the lengths do not exceed the buffer size
    if (str1_len + str2_len + str3_len > size - 3) {
        cmsMLUfree(mlu);
        return 0;
    }

    // Allocate and copy strings
    char *str1 = (char *)malloc(str1_len + 1);
    char *str2 = (char *)malloc(str2_len + 1);
    char *str3 = (char *)malloc(str3_len + 1);

    memcpy(str1, data + 3, str1_len);
    memcpy(str2, data + 3 + str1_len, str2_len);
    memcpy(str3, data + 3 + str1_len + str2_len, str3_len);

    str1[str1_len] = '\0';
    str2[str2_len] = '\0';
    str3[str3_len] = '\0';

    // Call the function under test
    cmsMLUsetUTF8(mlu, str1, str2, str3);

    // Clean up
    free(str1);
    free(str2);
    free(str3);
    cmsMLUfree(mlu);

    return 0;
}