#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_441(const uint8_t *data, size_t size) {
    // Ensure the input size is large enough for our purposes
    if (size < 3) return 0;

    // Create a cmsMLU object
    cmsMLU *mlu = cmsMLUalloc(NULL, 1);

    // Extract strings from the input data
    // For simplicity, we will divide the input data into three parts
    size_t str1_len = size / 3;
    size_t str2_len = (size - str1_len) / 2;
    size_t str3_len = size - str1_len - str2_len;

    char str1[str1_len + 1];
    char str2[str2_len + 1];
    char str3[str3_len + 1];

    memcpy(str1, data, str1_len);
    str1[str1_len] = '\0';

    memcpy(str2, data + str1_len, str2_len);
    str2[str2_len] = '\0';

    memcpy(str3, data + str1_len + str2_len, str3_len);
    str3[str3_len] = '\0';

    // Call the function-under-test
    cmsMLUsetASCII(mlu, str1, str2, str3);

    // Free the cmsMLU object
    cmsMLUfree(mlu);

    return 0;
}