#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_119(const uint8_t *data, size_t size) {
    cmsContext context = cmsCreateContext(NULL, NULL);
    if (context == NULL) {
        return 0;
    }

    // Ensure the data is null-terminated to be used as a string
    char *cubeFilePath = (char *)malloc(size + 1);
    if (cubeFilePath == NULL) {
        cmsDeleteContext(context);
        return 0;
    }
    memcpy(cubeFilePath, data, size);
    cubeFilePath[size] = '\0';

    // Call the function-under-test
    cmsHPROFILE profile = cmsCreateDeviceLinkFromCubeFileTHR(context, cubeFilePath);

    // Clean up
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }
    free(cubeFilePath);
    cmsDeleteContext(context);

    return 0;
}