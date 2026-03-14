#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
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
    int ret_tj3GetErrorCode_chccj = tj3GetErrorCode(handle);
    if (ret_tj3GetErrorCode_chccj < 0){
    	return 0;
    }
    int plalzfyo = size;

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tj3GetErrorCode to tj3CompressFromYUV8
    tjhandle ret_tj3Init_sfiri = tj3Init(ret_tj3GetErrorCode_chccj);
    unsigned char* ret_tjAlloc_bkvjp = tjAlloc(TJFLAG_FASTUPSAMPLE);
    if (ret_tjAlloc_bkvjp == NULL){
    	return 0;
    }

    int ret_tj3CompressFromYUV8_otapc = tj3CompressFromYUV8(ret_tj3Init_sfiri, ret_tjAlloc_bkvjp, TJXOPT_ARITHMETIC, 1, ret_tj3GetErrorCode_chccj, NULL, NULL);
    if (ret_tj3CompressFromYUV8_otapc < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tjscalingfactor* ret_tj3GetScalingFactors_pwwia = tj3GetScalingFactors(&plalzfyo);
    if (ret_tj3GetScalingFactors_pwwia == NULL){
    	return 0;
    }

    unsigned long ret_tjPlaneSizeYUV_uzfto = tjPlaneSizeYUV(TJXOPT_COPYNONE, TJFLAG_FORCESSE3, ret_tj3GetErrorCode_chccj, (int )jpegSize, plalzfyo);
    if (ret_tjPlaneSizeYUV_uzfto < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tjDestroy(handle);

    return 0;
}