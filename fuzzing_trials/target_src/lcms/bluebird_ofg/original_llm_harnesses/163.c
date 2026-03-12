#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // Include for malloc and free
#include <string.h>  // Include for memcpy
#include <lcms2.h>

int LLVMFuzzerTestOneInput_163(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated and non-empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the file path and ensure it's null-terminated
    char *filePath = (char *)malloc(size + 1);
    if (filePath == NULL) {
        return 0;
    }

    // Copy data to filePath and null-terminate it
    memcpy(filePath, data, size);
    filePath[size] = '\0';

    // Call the function-under-test
    cmsHPROFILE profile = cmsCreateDeviceLinkFromCubeFile(filePath);

    // Clean up
    free(filePath);

    // If a profile was created, close it
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }

    return 0;
}