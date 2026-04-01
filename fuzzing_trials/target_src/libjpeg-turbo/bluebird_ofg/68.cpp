#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_68(const uint8_t *data, size_t size) {
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
    tjhandle ret_tj3Init_qmago = tj3Init(TJFLAG_NOREALLOC);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tj3Init to tj3DecompressHeader
    int clwwsjoo = 1;
    tjscalingfactor* ret_tj3GetScalingFactors_xvkia = tj3GetScalingFactors(&clwwsjoo);
    if (ret_tj3GetScalingFactors_xvkia == NULL){
    	return 0;
    }

    int ret_tj3DecompressHeader_kspkz = tj3DecompressHeader(ret_tj3Init_qmago, (const unsigned char *)data, (size_t )clwwsjoo);
    if (ret_tj3DecompressHeader_kspkz < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tj3DecompressHeader to tjDecompressHeader
    tjhandle ret_tj3Init_vgwxb = tj3Init(TJFLAG_FORCESSE2);
    void* ret_tj3Alloc_gltwv = tj3Alloc(TJ_BGR);
    if (ret_tj3Alloc_gltwv == NULL){
    	return 0;
    }
    int ret_tjDestroy_bafna = tjDestroy(ret_tj3Init_qmago);
    if (ret_tjDestroy_bafna < 0){
    	return 0;
    }
    int ret_tjDestroy_ddvug = tjDestroy(ret_tj3Init_qmago);
    if (ret_tjDestroy_ddvug < 0){
    	return 0;
    }

    int ret_tjDecompressHeader_osewx = tjDecompressHeader(ret_tj3Init_vgwxb, (unsigned char *)ret_tj3Alloc_gltwv, (unsigned long )ret_tj3DecompressHeader_kspkz, &ret_tjDestroy_bafna, &ret_tjDestroy_ddvug);
    if (ret_tjDecompressHeader_osewx < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    unsigned char* ret_tjAlloc_gpltq = tjAlloc(TJFLAG_FASTDCT);
    if (ret_tjAlloc_gpltq == NULL){
    	return 0;
    }
    int hguubqjt = size;
    tjscalingfactor* ret_tj3GetScalingFactors_rsshh = tj3GetScalingFactors(&hguubqjt);
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