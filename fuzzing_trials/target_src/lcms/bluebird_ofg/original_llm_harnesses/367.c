#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_367(const uint8_t *data, size_t size) {
    cmsContext context = cmsCreateContext(NULL, NULL);
    if (context == NULL) {
        return 0;
    }

    // Ensure the input data is null-terminated for string usage
    char *filename = (char *)malloc(size + 1);
    if (filename == NULL) {
        cmsDeleteContext(context);
        return 0;
    }
    memcpy(filename, data, size);
    filename[size] = '\0';

    // Use a constant mode for simplicity
    const char *mode = "r";

    // Call the function-under-test
    cmsHPROFILE profile = cmsOpenProfileFromFileTHR(context, filename, mode);

    // Clean up
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }
    free(filename);
    cmsDeleteContext(context);

    return 0;
}