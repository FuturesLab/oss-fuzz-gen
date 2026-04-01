#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
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
    int result = tjTransform(handle, data, (unsigned long)size, 1, &dstBuf, &dstSize, &transform, size);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up
    if (dstBuf) {
        tjFree(dstBuf);
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjTransform to tj3Decompress8
    tjhandle ret_tj3Init_cycpy = tj3Init(TJ_ALPHAFIRST);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tj3Init to tj3DecompressToYUVPlanes8
    char* ret_tj3GetErrorStr_ociou = tj3GetErrorStr(ret_tj3Init_cycpy);
    if (ret_tj3GetErrorStr_ociou == NULL){
    	return 0;
    }
    unsigned char* ret_tjAlloc_sebiz = tjAlloc(TJXOPT_GRAY);
    if (ret_tjAlloc_sebiz == NULL){
    	return 0;
    }
    int ret_tjDestroy_dmwlx = tjDestroy(0);
    if (ret_tjDestroy_dmwlx < 0){
    	return 0;
    }

    int ret_tj3DecompressToYUVPlanes8_mpmkl = tj3DecompressToYUVPlanes8(ret_tj3Init_cycpy, (const unsigned char *)ret_tj3GetErrorStr_ociou, TJ_NUMCS, &ret_tjAlloc_sebiz, &ret_tjDestroy_dmwlx);
    if (ret_tj3DecompressToYUVPlanes8_mpmkl < 0){
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