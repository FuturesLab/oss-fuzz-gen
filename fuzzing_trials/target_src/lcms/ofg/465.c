#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_465(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract the necessary parameters
    if (size < sizeof(cmsTagSignature) * 2) {
        return 0;
    }

    // Initialize a memory context
    cmsContext contextID = cmsCreateContext(NULL, NULL);

    // Create a dummy profile for fuzzing
    cmsHPROFILE hProfile = cmsCreate_sRGBProfile();

    // Extract two cmsTagSignature values from the input data
    cmsTagSignature tag1 = *(cmsTagSignature*)data;
    cmsTagSignature tag2 = *(cmsTagSignature*)(data + sizeof(cmsTagSignature));

    // Call the function under test
    cmsBool result = cmsLinkTag(hProfile, tag1, tag2);

    // Clean up
    cmsCloseProfile(hProfile);
    cmsDeleteContext(contextID);

    return 0;
}