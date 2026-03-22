#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size) {
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
    char* ret_tj3GetErrorStr_mhsla = tj3GetErrorStr(handle);
    if (ret_tj3GetErrorStr_mhsla == NULL){
    	return 0;
    }
    int glwxuofx = 1;
    tjscalingfactor* ret_tj3GetScalingFactors_zoanm = tj3GetScalingFactors(&glwxuofx);
    if (ret_tj3GetScalingFactors_zoanm == NULL){
    	return 0;
    }
    int unzyhhak = 0;

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tj3GetScalingFactors to tjDecompressToYUVPlanes
    tjhandle ret_tj3Init_czelw = tj3Init(TJFLAG_BOTTOMUP);
    unsigned char* ret_tjAlloc_wqqzt = tjAlloc(64);
    if (ret_tjAlloc_wqqzt == NULL){
    	return 0;
    }
    int ret_tjGetErrorCode_qqafn = tjGetErrorCode(ret_tj3Init_cycpy);
    if (ret_tjGetErrorCode_qqafn < 0){
    	return 0;
    }
    tjscalingfactor* ret_tjGetScalingFactors_gcsnf = tjGetScalingFactors(&result);
    if (ret_tjGetScalingFactors_gcsnf == NULL){
    	return 0;
    }
    int cfzzdemb = 64;

    int ret_tjDecompressToYUVPlanes_ahmun = tjDecompressToYUVPlanes(ret_tj3Init_czelw, ret_tjAlloc_wqqzt, (unsigned long )ret_tjGetErrorCode_qqafn, (unsigned char **)"r", TJ_YUV, &cfzzdemb, result, glwxuofx);
    if (ret_tjDecompressToYUVPlanes_ahmun < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tjscalingfactor* ret_tj3GetScalingFactors_yyggz = tj3GetScalingFactors(&unzyhhak);
    if (ret_tj3GetScalingFactors_yyggz == NULL){
    	return 0;
    }
    char* ret_tjGetErrorStr_exmen = tjGetErrorStr();
    if (ret_tjGetErrorStr_exmen == NULL){
    	return 0;
    }
    int ret_tjGetErrorCode_evzoh = tjGetErrorCode(handle);
    if (ret_tjGetErrorCode_evzoh < 0){
    	return 0;
    }
    unsigned long uhlfmdsp = 64;

    int ret_tjCompress_zxbwu = tjCompress(ret_tj3Init_cycpy, (unsigned char *)ret_tj3GetErrorStr_mhsla, TJXOPT_NOOUTPUT, glwxuofx, unzyhhak, TJ_NUMCS, (unsigned char *)ret_tjGetErrorStr_exmen, &uhlfmdsp, result, ret_tjGetErrorCode_evzoh, TJ_NUMINIT);
    if (ret_tjCompress_zxbwu < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of tjAlloc
    unsigned char* ret_tjAlloc_isirt = tjAlloc(TJXOPT_TRIM);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


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