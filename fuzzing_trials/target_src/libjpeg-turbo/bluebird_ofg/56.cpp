#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of tj3Init
    tjhandle ret_tj3Init_qmago = tj3Init(1);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    unsigned char* ret_tjAlloc_gpltq = tjAlloc(TJFLAG_FASTDCT);
    if (ret_tjAlloc_gpltq == NULL){
    	return 0;
    }
    int hguubqjt = size;

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of tj3GetScalingFactors
    int tdenndwe = 64;
    tjscalingfactor* ret_tj3GetScalingFactors_rsshh = tj3GetScalingFactors(&tdenndwe);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_tj3GetScalingFactors_rsshh == NULL){
    	return 0;
    }

    int ret_tj3DecompressToYUVPlanes8_gexau = tj3DecompressToYUVPlanes8(ret_tj3Init_qmago, yuvBuf, TJ_NUMINIT, &ret_tjAlloc_gpltq, &hguubqjt);
    if (ret_tj3DecompressToYUVPlanes8_gexau < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    free(yuvBuf);
    tjDestroy(handle);

    return 0;
}