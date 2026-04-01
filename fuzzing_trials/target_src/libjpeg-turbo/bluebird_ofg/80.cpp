#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
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
    unsigned char* ret_tjAlloc_isirt = tjAlloc(TJXOPT_NOOUTPUT);
    if (ret_tjAlloc_isirt == NULL){
    	return 0;
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjAlloc to tj3Compress12
    tjhandle ret_tjInitDecompress_kfice = tjInitDecompress();
    int qzpaexst = size;
    tjscalingfactor* ret_tjGetScalingFactors_vmurm = tjGetScalingFactors(&qzpaexst);
    if (ret_tjGetScalingFactors_vmurm == NULL){
    	return 0;
    }
    int pypdvmhf = size;
    tjscalingfactor* ret_tj3GetScalingFactors_oucjr = tj3GetScalingFactors(&pypdvmhf);
    if (ret_tj3GetScalingFactors_oucjr == NULL){
    	return 0;
    }

    int ret_tj3Compress12_jicro = tj3Compress12(ret_tjInitDecompress_kfice, NULL, TJFLAG_STOPONWARNING, qzpaexst, TJ_BGR, size, &ret_tjAlloc_isirt, (size_t *)&pypdvmhf);
    if (ret_tj3Compress12_jicro < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_tj3Decompress8_cwjxf = tj3Decompress8(ret_tj3Init_cycpy, ret_tjAlloc_isirt, 0, NULL, TJFLAG_PROGRESSIVE, (int )dstSize);
    if (ret_tj3Decompress8_cwjxf < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tjDestroy(handle);

    return 0;
}