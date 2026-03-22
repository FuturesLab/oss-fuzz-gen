#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
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
    tjDecompressToYUV2(handle, jpegBuf, jpegSize, yuvBuf, width, 4, height, flags);

    // Cleanup

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjDecompressToYUV2 to tj3DecompressToYUVPlanes8
    tjhandle ret_tj3Init_hduhh = tj3Init(TJXOPT_NOOUTPUT);

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of tjAlloc
    unsigned char* ret_tjAlloc_uloid = tjAlloc(TJ_NUMINIT);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_tjAlloc_uloid == NULL){
    	return 0;
    }
    int ltabktjq = size;
    tjscalingfactor* ret_tjGetScalingFactors_dhfnl = tjGetScalingFactors(&ltabktjq);
    if (ret_tjGetScalingFactors_dhfnl == NULL){
    	return 0;
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjGetScalingFactors to tjEncodeYUV
    tjhandle ret_tj3Init_jcqsb = tj3Init(64);
    unsigned char* ret_tjAlloc_rxgyd = tjAlloc(TJ_NUMXOP);
    if (ret_tjAlloc_rxgyd == NULL){
    	return 0;
    }
    tjFree(ret_tjAlloc_uloid);

    int ret_tjEncodeYUV_stuac = tjEncodeYUV(ret_tj3Init_jcqsb, ret_tjAlloc_rxgyd, TJ_NUMCS, ltabktjq, TJXOPT_ARITHMETIC, TJFLAG_NOREALLOC, ret_tjAlloc_uloid, 0, TJFLAG_BOTTOMUP);
    if (ret_tjEncodeYUV_stuac < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_tj3DecompressToYUVPlanes8_ugjbo = tj3DecompressToYUVPlanes8(ret_tj3Init_hduhh, yuvBuf, TJFLAG_NOREALLOC, &ret_tjAlloc_uloid, &ltabktjq);
    if (ret_tj3DecompressToYUVPlanes8_ugjbo < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    free(yuvBuf);
    tjDestroy(handle);

    return 0;
}