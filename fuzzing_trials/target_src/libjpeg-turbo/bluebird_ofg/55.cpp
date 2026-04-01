#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 7 of tjTransform
    int result = tjTransform(handle, data, (unsigned long)size, 1, &dstBuf, &dstSize, &transform, TJFLAG_PROGRESSIVE);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up
    if (dstBuf) {
        tjFree(dstBuf);
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjTransform to tj3Decompress8
    tjhandle ret_tj3Init_cycpy = tj3Init(TJ_ALPHAFIRST);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tj3Init to tjCompress
    void* ret_tj3Alloc_ofhvb = tj3Alloc(TJFLAG_FASTDCT);
    if (ret_tj3Alloc_ofhvb == NULL){
    	return 0;
    }
    int ret_tjDestroy_lxtpf = tjDestroy(handle);
    if (ret_tjDestroy_lxtpf < 0){
    	return 0;
    }
    int unzyhhak = 0;
    tjscalingfactor* ret_tj3GetScalingFactors_yyggz = tj3GetScalingFactors(&unzyhhak);
    if (ret_tj3GetScalingFactors_yyggz == NULL){
    	return 0;
    }
    unsigned long uhlfmdsp = -1;

    int ret_tjCompress_dvhuu = tjCompress(ret_tj3Init_cycpy, (unsigned char *)ret_tj3Alloc_ofhvb, TJFLAG_PROGRESSIVE, ret_tjDestroy_lxtpf, unzyhhak, TJFLAG_FORCEMMX, (unsigned char *)data, &uhlfmdsp, TJFLAG_NOREALLOC, 64, TJ_YUV);
    if (ret_tjCompress_dvhuu < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    unsigned char* ret_tjAlloc_isirt = tjAlloc(TJXOPT_NOOUTPUT);
    if (ret_tjAlloc_isirt == NULL){
    	return 0;
    }

    int ret_tj3Decompress8_cwjxf = tj3Decompress8(ret_tj3Init_cycpy, ret_tjAlloc_isirt, 0, NULL, TJFLAG_PROGRESSIVE, (int )dstSize);
    if (ret_tj3Decompress8_cwjxf < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tjDestroy(handle);

    return 0;
}