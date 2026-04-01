#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    tjhandle handle = tjInitTransform();
    if (!handle) {
        return 0;
    }

    unsigned char *jpegBuf = nullptr;
    unsigned long jpegSize = 0;
    tjtransform transform;
    transform.op = TJXOP_NONE; // No transform operation
    transform.options = 0;
    transform.r = {0, 0, 0, 0}; // No cropping
    transform.customFilter = nullptr;

    int flags = 0; // No flags

    // Allocate memory for the destination buffer
    unsigned char *dstBuf = nullptr;
    unsigned long dstSize = 0;

    // Call the function-under-test
    int result = tjTransform(handle, data, (unsigned long)size, 1, &dstBuf, &dstSize, &transform, flags);

    // Clean up
    if (dstBuf) {
        tjFree(dstBuf);
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjTransform to tj3Decompress8

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjTransform to tj3SaveImage16
    tjhandle ret_tjInitTransform_acxzx = tjInitTransform();
    char* ret_tjGetErrorStr2_fdquu = tjGetErrorStr2(handle);
    if (ret_tjGetErrorStr2_fdquu == NULL){
    	return 0;
    }
    int ret_tj3GetErrorCode_sncte = tj3GetErrorCode(handle);
    if (ret_tj3GetErrorCode_sncte < 0){
    	return 0;
    }


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function tj3SaveImage16 with tj3SaveImage12
    int ret_tj3SaveImage16_bvpnt = tj3SaveImage12(ret_tjInitTransform_acxzx, ret_tjGetErrorStr2_fdquu, NULL, TJXOPT_ARITHMETIC, TJXOPT_NOOUTPUT, ret_tj3GetErrorCode_sncte, result);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_tj3SaveImage16_bvpnt < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    unsigned char* ret_tjAlloc_nxanz = tjAlloc(TJFLAG_ACCURATEDCT);
    if (ret_tjAlloc_nxanz == NULL){
    	return 0;
    }

    int ret_tj3Decompress8_bdwbh = tj3Decompress8(handle, ret_tjAlloc_nxanz, TJFLAG_FORCESSE, NULL, (int )dstSize, TJFLAG_NOREALLOC);
    if (ret_tj3Decompress8_bdwbh < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tjDestroy(handle);

    return 0;
}