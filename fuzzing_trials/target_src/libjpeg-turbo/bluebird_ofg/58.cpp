#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    // Initialize variables for tjDecompressToYUV2
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0;
    }

    const unsigned char *jpegBuf = data;
    unsigned long jpegSize = (unsigned long)size;

    // Allocate memory for the YUV buffer
    int width = 640;  // Example width
    int height = 480; // Example height
    int subsamp = TJSAMP_420; // Example subsampling
    int flags = 0; // No flags

    unsigned char *yuvBuf = (unsigned char *)malloc(tjBufSizeYUV2(width, 4, height, subsamp));
    if (yuvBuf == nullptr) {
        tjDestroy(handle);
        return 0;
    }

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 6 of tjDecompressToYUV2
    tjDecompressToYUV2(handle, jpegBuf, jpegSize, yuvBuf, width, 4, TJ_YUV, flags);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Cleanup

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjDecompressToYUV2 to tjLoadImage
    int ret_tj3GetErrorCode_yxzvg = tj3GetErrorCode(0);
    if (ret_tj3GetErrorCode_yxzvg < 0){
    	return 0;
    }
    int hoqhqtma = 0;
    tjscalingfactor* ret_tjGetScalingFactors_mskii = tjGetScalingFactors(&hoqhqtma);
    if (ret_tjGetScalingFactors_mskii == NULL){
    	return 0;
    }
    int rojbnsml = 1;
    tjscalingfactor* ret_tj3GetScalingFactors_khphn = tj3GetScalingFactors(&rojbnsml);
    if (ret_tj3GetScalingFactors_khphn == NULL){
    	return 0;
    }
    int ret_tjDestroy_kdtat = tjDestroy(handle);
    if (ret_tjDestroy_kdtat < 0){
    	return 0;
    }

    unsigned char* ret_tjLoadImage_jxumo = tjLoadImage((const char *)yuvBuf, &ret_tj3GetErrorCode_yxzvg, TJ_BGR, &hoqhqtma, &rojbnsml, ret_tjDestroy_kdtat);
    if (ret_tjLoadImage_jxumo == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    free(yuvBuf);
    tjDestroy(handle);

    return 0;
}