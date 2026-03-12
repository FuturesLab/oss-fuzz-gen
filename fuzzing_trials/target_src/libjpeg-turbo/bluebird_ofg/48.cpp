#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of tj3Transform
    int result = tj3Transform(handle, (const unsigned char *)data, size, n, &jpegBuf, &jpegSize, &transform);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up
    if (jpegBuf != nullptr) {
        tjFree(jpegBuf);
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tj3Transform to tjPlaneSizeYUV
    int xvfaspvl = -1;
    tjscalingfactor* ret_tj3GetScalingFactors_cxido = tj3GetScalingFactors(&xvfaspvl);
    if (ret_tj3GetScalingFactors_cxido == NULL){
    	return 0;
    }
    int plalzfyo = 0;

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tj3GetScalingFactors to tjDecompress2
    tjhandle ret_tjInitTransform_zwrgn = tjInitTransform();
    void* ret_tj3Alloc_cuhda = tj3Alloc(TJFLAG_FORCESSE3);
    if (ret_tj3Alloc_cuhda == NULL){
    	return 0;
    }
    int ret_tj3GetErrorCode_lxtdu = tj3GetErrorCode(0);
    if (ret_tj3GetErrorCode_lxtdu < 0){
    	return 0;
    }

    int ret_tjDecompress2_jmald = tjDecompress2(ret_tjInitTransform_zwrgn, (const unsigned char *)ret_tj3Alloc_cuhda, TJXOPT_CROP, (unsigned char *)data, TJFLAG_NOREALLOC, xvfaspvl, TJFLAG_LIMITSCANS, size, ret_tj3GetErrorCode_lxtdu);
    if (ret_tjDecompress2_jmald < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tjscalingfactor* ret_tj3GetScalingFactors_pxltf = tj3GetScalingFactors(&plalzfyo);
    if (ret_tj3GetScalingFactors_pxltf == NULL){
    	return 0;
    }

    unsigned long ret_tjPlaneSizeYUV_ogmhr = tjPlaneSizeYUV(xvfaspvl, TJ_NUMINIT, 1, result, plalzfyo);
    if (ret_tjPlaneSizeYUV_ogmhr < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tjDestroy(handle);

    return 0;
}