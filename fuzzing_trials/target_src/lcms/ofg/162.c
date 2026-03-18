#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_162(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to be used as a string
    char *filePath = (char *)malloc(size + 1);
    if (filePath == NULL) {
        return 0;
    }
    memcpy(filePath, data, size);
    filePath[size] = '\0';

    // Call the function-under-test
    cmsHPROFILE profile = cmsCreateDeviceLinkFromCubeFile(filePath);

    // Clean up
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }
    free(filePath);

    return 0;
}