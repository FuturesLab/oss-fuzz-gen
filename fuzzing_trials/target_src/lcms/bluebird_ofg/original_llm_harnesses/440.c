#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_440(const uint8_t *data, size_t size) {
    // Ensure the input size is large enough to split into meaningful parts
    if (size < 4) {
        return 0;
    }

    // Initialize variables
    cmsMLU *mlu = cmsMLUalloc(NULL, 1);
    const char *language = "en";
    const char *country = "US";

    // Split the input data into two parts for the ASCII string
    size_t ascii_len = size / 2;
    char *ascii_str1 = (char *)malloc(ascii_len + 1);
    char *ascii_str2 = (char *)malloc(ascii_len + 1);

    if (ascii_str1 == NULL || ascii_str2 == NULL) {
        cmsMLUfree(mlu);
        free(ascii_str1);
        free(ascii_str2);
        return 0;
    }

    memcpy(ascii_str1, data, ascii_len);
    ascii_str1[ascii_len] = '\0';

    memcpy(ascii_str2, data + ascii_len, ascii_len);
    ascii_str2[ascii_len] = '\0';

    // Call the function-under-test
    cmsMLUsetASCII(mlu, language, country, ascii_str1);
    cmsMLUsetASCII(mlu, language, country, ascii_str2);

    // Clean up
    cmsMLUfree(mlu);
    free(ascii_str1);
    free(ascii_str2);

    return 0;
}