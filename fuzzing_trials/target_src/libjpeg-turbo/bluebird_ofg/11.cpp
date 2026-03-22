#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    if (size < 12) {
        // Need at least 12 bytes for width, height, subsamp, and quality
        return 0;
    }

    // Extract width, height, subsamp, and quality from the input data
    int width = (data[0] << 8) | data[1];
    int height = (data[2] << 8) | data[3];
    int subsamp = data[4] % 5; // Using % 5 to ensure a valid subsampling option
    int quality = data[5] % 101; // Quality should be between 0 and 100

    // Ensure width and height are non-zero
    width = width == 0 ? 1 : width;
    height = height == 0 ? 1 : height;

    // Calculate the minimum YUV buffer size
    int yuvSize = tjBufSizeYUV2(width, 4, height, subsamp);
    if (size < 12 + yuvSize) {
        return 0;
    }

    // Point to the YUV image data
    const unsigned char *yuvImage = data + 12;

    // Allocate memory for the compressed JPEG image
    unsigned char *jpegBuf = nullptr;
    unsigned long jpegSize = 0;

    // Create a TurboJPEG compressor handle
    tjhandle handle = tjInitCompress();
    if (handle == nullptr) {
        return 0;
    }

    // Call the function-under-test
    tjCompressFromYUV(handle, yuvImage, width, 4, height, subsamp, &jpegBuf, &jpegSize, quality, 0);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjCompressFromYUV to TJBUFSIZEYUV
    int tejgrvte = 0;
    tjscalingfactor* ret_tjGetScalingFactors_bscru = tjGetScalingFactors(&tejgrvte);
    if (ret_tjGetScalingFactors_bscru == NULL){
    	return 0;
    }

    unsigned long ret_TJBUFSIZEYUV_eycib = TJBUFSIZEYUV((int )jpegSize, tejgrvte, TJXOPT_COPYNONE);
    if (ret_TJBUFSIZEYUV_eycib < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tjDestroy(handle);
    tjFree(jpegBuf);

    return 0;
}