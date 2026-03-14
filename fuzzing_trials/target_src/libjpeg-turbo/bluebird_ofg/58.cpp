#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    tjhandle handle = tjInitTransform();
    if (handle == nullptr) {
        return 0; // Handle initialization failure
    }

    unsigned char *jpegBuf = nullptr; // This will be allocated by tj3Transform
    size_t jpegSize = 0;
    int n = 1; // Number of transforms
    tjtransform transform;
    memset(&transform, 0, sizeof(tjtransform)); // Initialize transform with zeros

    // Call the function-under-test
    int result = tj3Transform(handle, data, size, n, &jpegBuf, &jpegSize, &transform);

    // Clean up
    if (jpegBuf != nullptr) {
        tjFree(jpegBuf);
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tj3Transform to tjPlaneWidth
    int ljoekamx = -1;

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tj3Transform to tj3SetICCProfile
    tjhandle ret_tjInitDecompress_nxtzs = tjInitDecompress();

    int ret_tj3SetICCProfile_fspui = tj3SetICCProfile(ret_tjInitDecompress_nxtzs, jpegBuf, (size_t )result);
    if (ret_tj3SetICCProfile_fspui < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tjscalingfactor* ret_tj3GetScalingFactors_snelr = tj3GetScalingFactors(&ljoekamx);
    if (ret_tj3GetScalingFactors_snelr == NULL){
    	return 0;
    }

    int ret_tjPlaneWidth_oxzec = tjPlaneWidth(result, ljoekamx, TJXOPT_ARITHMETIC);
    if (ret_tjPlaneWidth_oxzec < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tjDestroy(handle);

    return 0;
}