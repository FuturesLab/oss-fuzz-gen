#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function tjInitDecompress with tjInitTransform
    tjhandle handle = tjInitTransform();
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (handle == NULL) {
        return 0;
    }

    const unsigned char *jpegBuf = data;
    unsigned long jpegSize = size;

    int width = 100;  // Example width, should be set according to actual needs
    int height = 100; // Example height, should be set according to actual needs
    int pixelFormat = TJPF_RGB; // Example pixel format
    int flags = 0; // Example flags
    int pitch = 0; // Example pitch, can be set to 0 for default

    // Allocate buffer for decompressed image
    unsigned char *dstBuf = (unsigned char *)malloc(width * height * tjPixelSize[pixelFormat]);
    if (dstBuf == NULL) {
        tjDestroy(handle);
        return 0;
    }

    // Fuzz the function tjDecompress2

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 5 of tjDecompress2
    tjDecompress2(handle, jpegBuf, jpegSize, dstBuf, width, TJFLAG_FASTUPSAMPLE, height, pixelFormat, flags);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjDecompress2 to tj3SaveImage12
    tjhandle ret_tj3Init_hyfgx = tj3Init(TJXOPT_TRIM);
    int yysnmlem = 1;

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tj3Init to tjDecodeYUV
    unsigned char* ret_tjAlloc_osoer = tjAlloc(TJXOPT_ARITHMETIC);
    if (ret_tjAlloc_osoer == NULL){
    	return 0;
    }
    int ret_tjGetErrorCode_tamvy = tjGetErrorCode(ret_tj3Init_hyfgx);
    if (ret_tjGetErrorCode_tamvy < 0){
    	return 0;
    }
    unsigned char* ret_tjAlloc_avjxm = tjAlloc(TJ_NUMXOP);
    if (ret_tjAlloc_avjxm == NULL){
    	return 0;
    }
    int ret_tjGetErrorCode_iujdf = tjGetErrorCode(ret_tj3Init_hyfgx);
    if (ret_tjGetErrorCode_iujdf < 0){
    	return 0;
    }
    int ret_tj3GetErrorCode_fbcgq = tj3GetErrorCode(handle);
    if (ret_tj3GetErrorCode_fbcgq < 0){
    	return 0;
    }
    int ret_tj3GetErrorCode_pknke = tj3GetErrorCode(ret_tj3Init_hyfgx);
    if (ret_tj3GetErrorCode_pknke < 0){
    	return 0;
    }


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 8 of tjDecodeYUV
    int ret_tjDecodeYUV_fqjgl = tjDecodeYUV(ret_tj3Init_hyfgx, ret_tjAlloc_osoer, ret_tjGetErrorCode_tamvy, TJ_BGR, ret_tjAlloc_avjxm, ret_tjGetErrorCode_iujdf, ret_tj3GetErrorCode_fbcgq, ret_tj3GetErrorCode_pknke, TJXOPT_CROP, TJ_BGR);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_tjDecodeYUV_fqjgl < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tjscalingfactor* ret_tj3GetScalingFactors_dfmip = tj3GetScalingFactors(&yysnmlem);
    if (ret_tj3GetScalingFactors_dfmip == NULL){
    	return 0;
    }
    int ret_tjGetErrorCode_hwtob = tjGetErrorCode(0);
    if (ret_tjGetErrorCode_hwtob < 0){
    	return 0;
    }
    int awswyqxv = 64;
    tjscalingfactor* ret_tj3GetScalingFactors_amtpu = tj3GetScalingFactors(&awswyqxv);
    if (ret_tj3GetScalingFactors_amtpu == NULL){
    	return 0;
    }

    int ret_tj3SaveImage12_qpjkv = tj3SaveImage12(ret_tj3Init_hyfgx, (const char *)dstBuf, NULL, 64, yysnmlem, ret_tjGetErrorCode_hwtob, awswyqxv);
    if (ret_tj3SaveImage12_qpjkv < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    free(dstBuf);
    tjDestroy(handle);

    return 0;
}