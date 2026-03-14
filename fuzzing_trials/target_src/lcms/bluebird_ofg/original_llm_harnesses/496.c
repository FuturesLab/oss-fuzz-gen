#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_496(const uint8_t *data, size_t size) {
    cmsContext context = NULL;
    cmsUInt32Number nColors = 10; // Arbitrary non-zero number of colors
    cmsUInt32Number flags = 0; // Using 0 as a default flag value

    // Ensure the size is sufficient for at least two strings
    if (size < 2) {
        return 0;
    }

    // Split the input data into two strings
    size_t str1_len = data[0] % (size - 1);
    size_t str2_len = size - 1 - str1_len;

    char str1[str1_len + 1];
    char str2[str2_len + 1];

    memcpy(str1, data + 1, str1_len);
    str1[str1_len] = '\0';

    memcpy(str2, data + 1 + str1_len, str2_len);
    str2[str2_len] = '\0';

    // Call the function under test
    cmsNAMEDCOLORLIST *namedColorList = cmsAllocNamedColorList(context, nColors, flags, str1, str2);

    // Clean up if necessary
    if (namedColorList != NULL) {
        cmsFreeNamedColorList(namedColorList);
    }

    return 0;
}