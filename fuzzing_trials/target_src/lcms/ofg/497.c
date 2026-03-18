#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_497(const uint8_t *data, size_t size) {
    cmsContext context = NULL; // Assuming a NULL context for simplicity
    cmsUInt32Number nColors = 10; // Arbitrary non-zero number of colors
    cmsUInt32Number nChannels = 3; // Arbitrary non-zero number of channels

    // Ensure the size is sufficient to extract strings
    if (size < 3) { // Need at least 3 bytes to extract two non-empty strings
        return 0;
    }

    // Extract two strings from the input data
    size_t str1_len = data[0] % (size - 2);
    size_t str2_len = data[1] % (size - str1_len - 2);

    char *prefix = (char *)malloc(str1_len + 1);
    char *suffix = (char *)malloc(str2_len + 1);

    if (prefix == NULL || suffix == NULL) {
        free(prefix);
        free(suffix);
        return 0;
    }

    memcpy(prefix, data + 2, str1_len);
    prefix[str1_len] = '\0';

    memcpy(suffix, data + 2 + str1_len, str2_len);
    suffix[str2_len] = '\0';

    // Call the function-under-test
    cmsNAMEDCOLORLIST *namedColorList = cmsAllocNamedColorList(context, nColors, nChannels, prefix, suffix);

    // Clean up
    if (namedColorList != NULL) {
        cmsFreeNamedColorList(namedColorList);
    }
    free(prefix);
    free(suffix);

    return 0;
}