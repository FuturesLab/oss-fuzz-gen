#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    // Initialize variables for the function-under-test
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0; // If initialization fails, exit early
    }

    // Define dimensions and subsampling for the output YUV image
    int width = 640;
    int height = 480;
    int subsamp = TJSAMP_420; // Common subsampling format
    int flags = 0;

    // Calculate the buffer size for the YUV image
    int align = 4; // Alignment parameter for tjBufSizeYUV2
    unsigned long yuvSize = tjBufSizeYUV2(width, align, height, subsamp);

    // Allocate memory for the YUV buffer
    unsigned char *yuvBuffer = (unsigned char *)malloc(yuvSize);
    if (yuvBuffer == nullptr) {
        tjDestroy(handle);
        return 0; // If allocation fails, exit early
    }

    // Call the function-under-test
    int result = tjDecompressToYUV2(handle, data, size, yuvBuffer, width, align, height, flags);

    // Clean up resources

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjDecompressToYUV2 to tjDecompressToYUV
    tjhandle ret_tj3Init_nmrmj = tj3Init(TJ_NUMERR);
    tjscalingfactor* ret_tj3GetScalingFactors_hbbob = tj3GetScalingFactors(&result);
    if (ret_tj3GetScalingFactors_hbbob == NULL){
    	return 0;
    }
    void* ret_tj3Alloc_msxnw = tj3Alloc(TJFLAG_FASTUPSAMPLE);
    if (ret_tj3Alloc_msxnw == NULL){
    	return 0;
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tj3Alloc to tjDecompressToYUV
    tjhandle ret_tj3Init_rwadt = tj3Init(TJ_NUMERR);
    char* ret_tjGetErrorStr_cnevd = tjGetErrorStr();
    if (ret_tjGetErrorStr_cnevd == NULL){
    	return 0;
    }

    int ret_tjDecompressToYUV_ufsck = tjDecompressToYUV(ret_tj3Init_rwadt, (unsigned char *)ret_tjGetErrorStr_cnevd, TJFLAG_BOTTOMUP, (unsigned char *)ret_tj3Alloc_msxnw, TJ_ALPHAFIRST);
    if (ret_tjDecompressToYUV_ufsck < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_tjDecompressToYUV_xznst = tjDecompressToYUV(ret_tj3Init_nmrmj, NULL, (unsigned long )result, (unsigned char *)ret_tj3Alloc_msxnw, result);
    if (ret_tjDecompressToYUV_xznst < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    free(yuvBuffer);
    tjDestroy(handle);

    return 0;
}