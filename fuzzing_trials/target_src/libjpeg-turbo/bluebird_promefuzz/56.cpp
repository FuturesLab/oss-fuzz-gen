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

extern "C" int LLVMFuzzerTestOneInput_56(const uint8_t *Data, size_t Size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjDecompressHeader2 to tjDecodeYUV
    tjhandle ret_tj3Init_yapgy = tj3Init((int )*dstSizes);
    char* ret_tjGetErrorStr2_jmezz = tjGetErrorStr2(0);
    if (ret_tjGetErrorStr2_jmezz == NULL){
    	return 0;
    }
    unsigned char* ret_tjAlloc_znfre = tjAlloc(TJXOPT_PROGRESSIVE);
    if (ret_tjAlloc_znfre == NULL){
    	return 0;
    }
    int atskqsyu = 64;
    tjscalingfactor* ret_tjGetScalingFactors_arpqu = tjGetScalingFactors(&atskqsyu);
    if (ret_tjGetScalingFactors_arpqu == NULL){
    	return 0;
    }

    int ret_tjDecodeYUV_xaznn = tjDecodeYUV(ret_tj3Init_yapgy, (const unsigned char *)ret_tjGetErrorStr2_jmezz, TJFLAG_FORCESSE2, height, ret_tjAlloc_znfre, atskqsyu, TJFLAG_LIMITSCANS, TJFLAG_FORCESSE2, TJFLAG_FASTUPSAMPLE, TJ_YUV);
    if (ret_tjDecodeYUV_xaznn < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

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
        tjDecompressToYUV2(decompressor, Data, Size, yuvBuf, width, 4, height, flags);
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