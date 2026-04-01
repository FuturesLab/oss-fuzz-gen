#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
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
    tjhandle ret_tjInitCompress_cdxup = tjInitCompress();
    void* ret_tj3Alloc_garfq = tj3Alloc(TJXOPT_ARITHMETIC);
    if (ret_tj3Alloc_garfq == NULL){
    	return 0;
    }
    int ret_tjGetErrorCode_szgsq = tjGetErrorCode(0);
    if (ret_tjGetErrorCode_szgsq < 0){
    	return 0;
    }
    int hguubqjt = 1;

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of tj3GetScalingFactors
    int evhfuwhg = 0;
    tjscalingfactor* ret_tj3GetScalingFactors_sokrk = tj3GetScalingFactors(&evhfuwhg);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_tj3GetScalingFactors_sokrk == NULL){
    	return 0;
    }

    int ret_tj3DecompressToYUVPlanes8_vvyqg = tj3DecompressToYUVPlanes8(ret_tjInitCompress_cdxup, (const unsigned char *)ret_tj3Alloc_garfq, (size_t )ret_tjGetErrorCode_szgsq, &yuvBuf, &hguubqjt);
    if (ret_tj3DecompressToYUVPlanes8_vvyqg < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    free(yuvBuf);
    tjDestroy(handle);

    return 0;
}