#include <cstdint>
#include <cstdlib>

extern "C" {
#include "/src/libjpeg-turbo.main/src/turbojpeg.h"
#include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
#include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    // Initialize variables
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0;
    }

    // Define parameters for tjDecompressToYUV2
    const unsigned char *jpegBuf = data;
    unsigned long jpegSize = static_cast<unsigned long>(size);

    // Assuming some arbitrary dimensions for the YUV output
    int width = 128;  // Width of the image
    int height = 128; // Height of the image
    int strides = width; // Strides for YUV planes

    // Allocate memory for the YUV buffer
    unsigned char *yuvBuf = static_cast<unsigned char *>(malloc(width * height * 3));
    if (yuvBuf == nullptr) {
        tjDestroy(handle);
        return 0;
    }

    // Call the function-under-test
    int result = tjDecompressToYUV2(handle, jpegBuf, jpegSize, yuvBuf, width, strides, height, 0);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjDecompressToYUV2 to tj3Decompress12
    int ret_tj3GetErrorCode_opgfx = tj3GetErrorCode(0);
    if (ret_tj3GetErrorCode_opgfx < 0){
    	return 0;
    }

    int ret_tj3Decompress12_oqezz = tj3Decompress12(0, yuvBuf, (size_t )ret_tj3GetErrorCode_opgfx, NULL, TJ_NUMCS, TJ_YUV);
    if (ret_tj3Decompress12_oqezz < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tj3Decompress12 to tj3YUVPlaneSize
    int cpxoxfqm = size;
    tjscalingfactor* ret_tj3GetScalingFactors_zrujp = tj3GetScalingFactors(&cpxoxfqm);
    if (ret_tj3GetScalingFactors_zrujp == NULL){
    	return 0;
    }

    size_t ret_tj3YUVPlaneSize_ukopq = tj3YUVPlaneSize(TJXOPT_OPTIMIZE, size, ret_tj3Decompress12_oqezz, ret_tj3GetErrorCode_opgfx, cpxoxfqm);
    if (ret_tj3YUVPlaneSize_ukopq < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    free(yuvBuf);
    tjDestroy(handle);

    return 0;
}