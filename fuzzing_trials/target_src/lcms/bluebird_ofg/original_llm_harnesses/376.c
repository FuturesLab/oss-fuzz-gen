#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_376(const uint8_t *data, size_t size) {
    // Ensure that the input size is large enough to extract meaningful strings
    if (size < 4) {
        return 0;
    }

    // Initialize cmsHANDLE
    cmsHANDLE handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Extract strings from the input data
    size_t str1_len = data[0] % (size - 1) + 1; // Length of the first string
    size_t str2_len = data[1] % (size - str1_len - 1) + 1; // Length of the second string
    size_t str3_len = data[2] % (size - str1_len - str2_len - 1) + 1; // Length of the third string

    char *str1 = (char *)malloc(str1_len + 1);
    char *str2 = (char *)malloc(str2_len + 1);
    char *str3 = (char *)malloc(str3_len + 1);

    if (str1 == NULL || str2 == NULL || str3 == NULL) {
        cmsIT8Free(handle);
        free(str1);
        free(str2);
        free(str3);
        return 0;
    }

    memcpy(str1, data + 3, str1_len);
    str1[str1_len] = '\0';

    memcpy(str2, data + 3 + str1_len, str2_len);
    str2[str2_len] = '\0';

    memcpy(str3, data + 3 + str1_len + str2_len, str3_len);
    str3[str3_len] = '\0';

    // Call the function under test
    cmsBool result = cmsIT8SetPropertyMulti(handle, str1, str2, str3);

    // Clean up
    cmsIT8Free(handle);
    free(str1);
    free(str2);
    free(str3);

    return 0;
}