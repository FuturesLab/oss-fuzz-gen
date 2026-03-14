#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_290(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsMLU *mlu = cmsMLUalloc(NULL, 1);
    const char *language = "en";
    const char *country = "US";
    char buffer1[256];
    char buffer2[256];

    // Ensure data is not NULL and has a minimum size
    if (size < 1) {
        cmsMLUfree(mlu);
        return 0;
    }

    // Copy data into buffer1 and buffer2 ensuring null-termination
    size_t copy_size = size < 255 ? size : 255;
    memcpy(buffer1, data, copy_size);
    buffer1[copy_size] = '\0';
    memcpy(buffer2, data, copy_size);
    buffer2[copy_size] = '\0';

    // Set some initial data in the MLU object
    cmsMLUsetWide(mlu, language, country, L"Sample Text");

    // Call the function-under-test
    cmsBool result = cmsMLUgetTranslation(mlu, language, country, buffer1, buffer2);

    // Clean up
    cmsMLUfree(mlu);

    return 0;
}