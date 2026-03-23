#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "../src/turbojpeg.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <setjmp.h>

static tjhandle createDecompressor() {

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function tjInitDecompress with tjInitTransform
    return tjInitTransform();
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


}

static tjhandle createCompressor() {
    return tjInitCompress();
}

static void destroyHandle(tjhandle handle) {
    if (handle) {
        tjDestroy(handle);
    }
}

extern "C" int LLVMFuzzerTestOneInput_58(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Initialize a TurboJPEG decompressor handle
    tjhandle decompressor = createDecompressor();
    if (!decompressor) {
        return 0;
    }

    // Initialize a TurboJPEG compressor handle
    tjhandle compressor = createCompressor();
    if (!compressor) {
        destroyHandle(decompressor);
        return 0;
    }

    // Prepare buffers and variables for tjTransform
    unsigned char *dstBufs[1] = {nullptr};
    unsigned long dstSizes[1] = {0};
    tjtransform transforms[1] = {0};
    int n = 1;
    int flags = 0;

    // Fuzz tjTransform
    tjTransform(decompressor, Data, Size, n, dstBufs, dstSizes, transforms, flags);

    // Clean up buffers
    for (int i = 0; i < n; i++) {
        if (dstBufs[i]) {
            tjFree(dstBufs[i]);
        }
    }

    // Fuzz tj3GetErrorCode
    tj3GetErrorCode(decompressor);

    // Prepare variables for tjDecompressHeader2
    int width = 0, height = 0, jpegSubsamp = 0;

    // Fuzz tjDecompressHeader2
    tjDecompressHeader2(decompressor, const_cast<unsigned char *>(Data), Size, &width, &height, &jpegSubsamp);

    // Prepare variables for tjCompress
    unsigned char *srcBuf = (unsigned char *)malloc(width * height * 3);
    unsigned char *compressedBuf = nullptr;
    unsigned long compressedSize = 0;
    int pixelSize = 3;
    int jpegQual = 75;

    // Fuzz tjCompress
    if (srcBuf) {
        memset(srcBuf, 0, width * height * pixelSize);
        tjCompress(compressor, srcBuf, width, width * pixelSize, height, pixelSize, compressedBuf, &compressedSize, jpegSubsamp, jpegQual, flags);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjCompress to tj3YUVPlaneSize
        int aauzihlt = 64;
        tjscalingfactor* ret_tj3GetScalingFactors_cejmy = tj3GetScalingFactors(&aauzihlt);
        if (ret_tj3GetScalingFactors_cejmy == NULL){
        	return 0;
        }

        size_t ret_tj3YUVPlaneSize_ooemi = tj3YUVPlaneSize(aauzihlt, TJXOPT_TRIM, (int )compressedSize, (int )compressedSize, TJ_NUMERR);
        if (ret_tj3YUVPlaneSize_ooemi < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        tjFree(compressedBuf);
        free(srcBuf);
    }

    // Prepare variables for tjDecompressToYUV2
    unsigned char *yuvBuf = (unsigned char *)malloc(width * height * 3 / 2);

    // Fuzz tjDecompressToYUV2
    if (yuvBuf) {

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of tjDecompressToYUV2
        tjDecompressToYUV2(decompressor, (const unsigned char *)"r", Size, yuvBuf, width, 4, height, flags);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


        free(yuvBuf);
    }

    // Prepare variables for tjDecompress2
    unsigned char *decompressedBuf = (unsigned char *)malloc(width * height * pixelSize);

    // Fuzz tjDecompress2
    if (decompressedBuf) {
        tjDecompress2(decompressor, Data, Size, decompressedBuf, width, width * pixelSize, height, TJPF_RGB, flags);
        free(decompressedBuf);
    }

    // Clean up handles
    destroyHandle(decompressor);
    destroyHandle(compressor);

    return 0;
}