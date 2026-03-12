#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include "../src/turbojpeg.h"
#include <cstdint>
#include <cstring>

static tjhandle initializeHandle() {

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function tjInitCompress with tjInitTransform
    tjhandle handle = tjInitTransform();
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (!handle) {
        fprintf(stderr, "Error initializing TurboJPEG compressor: %s\n", tjGetErrorStr());
        return nullptr;
    }
    return handle;
}

static void cleanupHandle(tjhandle handle) {
    if (handle) {
        tjDestroy(handle);
    }
}

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    } // Ensure there's at least some data

    tjhandle handle = initializeHandle();
    if (!handle) {
        return 0;
    }

    // Prepare dummy data for fuzzing
    int width = 256, height = 256, pitch = width * 3;
    int pixelFormat = TJPF_RGB;
    int subsamp = TJSAMP_420;
    int flags = 0;
    unsigned char *srcBuf = new unsigned char[pitch * height];
    unsigned char *dstBuf = new unsigned char[tjBufSizeYUV2(width, 4, height, subsamp)];
    unsigned char *dstPlanes[3] = { dstBuf, dstBuf + (width * height), dstBuf + (width * height * 5 / 4) };
    int strides[3] = { width, width / 2, width / 2 };

    // Fill srcBuf with fuzz data
    memcpy(srcBuf, Data, Size < pitch * height ? Size : pitch * height);

    // Fuzz tjEncodeYUVPlanes
    tjEncodeYUVPlanes(handle, srcBuf, width, pitch, height, pixelFormat, dstPlanes, strides, subsamp, flags);

    // Fuzz tj3CompressFromYUVPlanes8
    unsigned char *jpegBuf = nullptr;
    size_t jpegSize = 0;
    tj3CompressFromYUVPlanes8(handle, (const unsigned char * const *)dstPlanes, width, strides, height, &jpegBuf, &jpegSize);

    // Fuzz tjCompressFromYUVPlanes
    unsigned long jpegSizeLong = 0;
    tjCompressFromYUVPlanes(handle, (const unsigned char **)dstPlanes, width, strides, height, subsamp, &jpegBuf, &jpegSizeLong, 75, flags);

    // Fuzz tj3EncodeYUV8
    int align = 4;

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 5 of tj3EncodeYUV8
    tj3EncodeYUV8(handle, srcBuf, width, pitch, height, TJXOPT_CROP, dstBuf, align);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Fuzz tjEncodeYUV3
    tjEncodeYUV3(handle, srcBuf, width, pitch, height, pixelFormat, dstBuf, align, subsamp, flags);

    // Fuzz tj3DecodeYUVPlanes8
    unsigned char *decodedBuf = new unsigned char[pitch * height];

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 7 of tj3DecodeYUVPlanes8
    tj3DecodeYUVPlanes8(handle, (const unsigned char * const *)dstPlanes, strides, decodedBuf, width, pitch, height, 1);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Cleanup
    delete[] srcBuf;
    delete[] dstBuf;
    delete[] decodedBuf;
    tjFree(jpegBuf);
    cleanupHandle(handle);

    return 0;
}