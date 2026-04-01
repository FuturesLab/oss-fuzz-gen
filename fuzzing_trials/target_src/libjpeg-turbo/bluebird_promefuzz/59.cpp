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
#include <iostream>
#include <fstream>

static void writeFile(const char* filename, const uint8_t* data, size_t size) {
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(data), size);
        file.close();
    }
}

extern "C" int LLVMFuzzerTestOneInput_59(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function tjInitCompress with tjInitTransform
    tjhandle handle = tjInitTransform();
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (!handle) {
        return 0;
    }

    int width = 256; // Example width
    int height = 256; // Example height
    int subsamp = TJSAMP_420; // Example subsampling
    int jpegQual = 75; // Example quality
    int flags = 0; // Example flags

    unsigned char *jpegBuf = nullptr;
    unsigned long jpegSize = 0;
    int align = 1; // Example alignment

    // Prepare a dummy YUV buffer
    size_t yuvSize = tjBufSizeYUV2(width, align, height, subsamp);
    unsigned char *yuvBuf = (unsigned char *)malloc(yuvSize);
    if (!yuvBuf) {
        tjDestroy(handle);
        return 0;
    }
    memcpy(yuvBuf, Data, std::min(Size, yuvSize));

    // Fuzz tjCompressFromYUV
    tjCompressFromYUV(handle, yuvBuf, width, align, height, subsamp, &jpegBuf, &jpegSize, jpegQual, flags);

    // Fuzz tjDecompressToYUVPlanes if jpegBuf is valid
    if (jpegBuf) {
        unsigned char *dstPlanes[3] = { nullptr, nullptr, nullptr };
        int strides[3] = { width, width / 2, width / 2 };
        for (int i = 0; i < 3; i++) {
            dstPlanes[i] = (unsigned char *)malloc(strides[i] * height / (i == 0 ? 1 : 2));
        }
        tjDecompressToYUVPlanes(handle, jpegBuf, jpegSize, dstPlanes, width, strides, height, flags);
        for (int i = 0; i < 3; i++) {
            free(dstPlanes[i]);
        }
        tjFree(jpegBuf);
    }

    // Fuzz tjEncodeYUV
    unsigned char *dstBuf = (unsigned char *)malloc(yuvSize);
    if (dstBuf) {

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 8 of tjEncodeYUV
        tjEncodeYUV(handle, yuvBuf, width, width, height, 3, dstBuf, subsamp, TJFLAG_PROGRESSIVE);
        // End mutation: Producer.REPLACE_ARG_MUTATOR



        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjEncodeYUV to tjDecodeYUVPlanes
        tjhandle ret_tj3Init_vlume = tj3Init(TJXOPT_PERFECT);
        void* ret_tj3Alloc_yldek = tj3Alloc(TJXOPT_NOOUTPUT);
        if (ret_tj3Alloc_yldek == NULL){
        	return 0;
        }
        int ret_tjGetErrorCode_ikhgd = tjGetErrorCode(0);
        if (ret_tjGetErrorCode_ikhgd < 0){
        	return 0;
        }
        int nqpcveyy = 0;
        tjscalingfactor* ret_tjGetScalingFactors_apuoz = tjGetScalingFactors(&nqpcveyy);
        if (ret_tjGetScalingFactors_apuoz == NULL){
        	return 0;
        }
        int ejrvwhij = Size;
        tjscalingfactor* ret_tj3GetScalingFactors_kvdwm = tj3GetScalingFactors(&ejrvwhij);
        if (ret_tj3GetScalingFactors_kvdwm == NULL){
        	return 0;
        }
        int anhcqgnf = -1;
        tjscalingfactor* ret_tjGetScalingFactors_aukji = tjGetScalingFactors(&anhcqgnf);
        if (ret_tjGetScalingFactors_aukji == NULL){
        	return 0;
        }

        int ret_tjDecodeYUVPlanes_eyeih = tjDecodeYUVPlanes(ret_tj3Init_vlume, (const unsigned char **)&ret_tj3Alloc_yldek, &ret_tjGetErrorCode_ikhgd, nqpcveyy, yuvBuf, TJFLAG_NOREALLOC, TJ_NUMCS, ejrvwhij, TJXOPT_CROP, anhcqgnf);
        if (ret_tjDecodeYUVPlanes_eyeih < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        free(dstBuf);
    }

    // Fuzz tjEncodeYUVPlanes
    unsigned char *dstPlanes2[3] = { nullptr, nullptr, nullptr };
    int strides2[3] = { width, width / 2, width / 2 };
    for (int i = 0; i < 3; i++) {
        dstPlanes2[i] = (unsigned char *)malloc(strides2[i] * height / (i == 0 ? 1 : 2));
    }
    tjEncodeYUVPlanes(handle, yuvBuf, width, width, height, TJPF_RGB, dstPlanes2, strides2, subsamp, flags);
    for (int i = 0; i < 3; i++) {
        free(dstPlanes2[i]);
    }

    // Fuzz tjEncodeYUV3
    dstBuf = (unsigned char *)malloc(yuvSize);
    if (dstBuf) {
        tjEncodeYUV3(handle, yuvBuf, width, width, height, TJPF_RGB, dstBuf, align, subsamp, flags);
        free(dstBuf);
    }

    // Fuzz tjCompress
    unsigned long maxCompressedSize = tjBufSize(width, height, subsamp);
    unsigned char *compressedBuf = (unsigned char *)malloc(maxCompressedSize);
    if (compressedBuf) {
        tjCompress(handle, yuvBuf, width, width, height, 3, compressedBuf, &jpegSize, subsamp, jpegQual, flags);
        free(compressedBuf);
    }

    free(yuvBuf);
    tjDestroy(handle);
    return 0;
}