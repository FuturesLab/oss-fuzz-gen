#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_172(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for splitting into strings
    if (size < 2) {
        return 0;
    }

    // Initialize a cmsHANDLE object
    cmsHANDLE handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Split the input data into two strings
    size_t str1_len = size / 2;
    size_t str2_len = size - str1_len;

    char *str1 = (char *)malloc(str1_len + 1);
    char *str2 = (char *)malloc(str2_len + 1);

    if (str1 == NULL || str2 == NULL) {
        cmsIT8Free(handle);
        free(str1);
        free(str2);
        return 0;
    }

    memcpy(str1, data, str1_len);
    str1[str1_len] = '\0';

    memcpy(str2, data + str1_len, str2_len);
    str2[str2_len] = '\0';

    // Call the function-under-test
    cmsIT8SetPropertyUncooked(handle, str1, str2);

    // Clean up
    cmsIT8Free(handle);
    free(str1);
    free(str2);

    return 0;
}