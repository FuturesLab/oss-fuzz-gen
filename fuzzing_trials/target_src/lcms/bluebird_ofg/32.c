#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    FILE *stream;
    cmsBool result;

    // Ensure data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a profile using the data
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Create a temporary file to use as the stream
    stream = tmpfile();
    if (stream == NULL) {
        cmsCloseProfile(hProfile);
        return 0;
    }

    // Call the function-under-test
    result = cmsSaveProfileToStream(hProfile, stream);

    // Since we are not sure if cmsSaveProfileToStream closes the stream,
    // we should only close it ourselves if saving fails.
    if (!result) {
        fclose(stream);
    }

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}