#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
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
    int xvfaspvl = 64;
    tjscalingfactor* ret_tj3GetScalingFactors_wldvq = tj3GetScalingFactors(&xvfaspvl);
    if (ret_tj3GetScalingFactors_wldvq == NULL){
    	return 0;
    }
    tjscalingfactor* ret_tjGetScalingFactors_ufcvy = tjGetScalingFactors(&result);
    if (ret_tjGetScalingFactors_ufcvy == NULL){
    	return 0;
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjGetScalingFactors to tjDecodeYUVPlanes
    char* ret_tj3GetErrorStr_vrjeg = tj3GetErrorStr(handle);
    if (ret_tj3GetErrorStr_vrjeg == NULL){
    	return 0;
    }
    int mdlkfhuj = 1;
    tjscalingfactor* ret_tj3GetScalingFactors_milqd = tj3GetScalingFactors(&mdlkfhuj);
    if (ret_tj3GetScalingFactors_milqd == NULL){
    	return 0;
    }
    unsigned char* ret_tjAlloc_mpjpj = tjAlloc(TJFLAG_FORCESSE3);
    if (ret_tjAlloc_mpjpj == NULL){
    	return 0;
    }

    int ret_tjDecodeYUVPlanes_jyaxk = tjDecodeYUVPlanes(handle, (const unsigned char **)&ret_tj3GetErrorStr_vrjeg, &result, mdlkfhuj, ret_tjAlloc_mpjpj, TJFLAG_LIMITSCANS, TJFLAG_PROGRESSIVE, TJXOPT_OPTIMIZE, TJXOPT_COPYNONE, TJFLAG_FORCESSE3);
    if (ret_tjDecodeYUVPlanes_jyaxk < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    unsigned long ret_tjPlaneSizeYUV_gnzuh = tjPlaneSizeYUV(xvfaspvl, result, 64, 0, result);
    if (ret_tjPlaneSizeYUV_gnzuh < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tjDestroy(handle);

    return 0;
}