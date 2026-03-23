#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include "../src/turbojpeg.h"

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Prepare dummy file
    const char *filename = "./dummy_file";
    FILE *file = fopen(filename, "wb");
    if (!file) {
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Variables for image dimensions and pixel format
    int width = 0, height = 0, pixelFormat = TJPF_RGB, pitch = 0;
    int flags = 0, align = 1;

    // Allocate memory for tjLoadImage
    unsigned char *imgBuffer = tjLoadImage(filename, &width, align, &height, &pixelFormat, flags);
    if (imgBuffer) {
        // Test tjSaveImage
        tjSaveImage(filename, imgBuffer, width, pitch, height, pixelFormat, flags);
        tjFree(imgBuffer);
    }

    // Create a TurboJPEG instance handle

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function tjInitDecompress with tjInitCompress

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjLoadImage to tjPlaneSizeYUV
    tjscalingfactor* ret_tj3GetScalingFactors_xxirj = tj3GetScalingFactors(&width);
    if (ret_tj3GetScalingFactors_xxirj == NULL){
    	return 0;
    }

    unsigned long ret_tjPlaneSizeYUV_hugjl = tjPlaneSizeYUV(width, pixelFormat, TJ_NUMINIT, 64, TJFLAG_NOREALLOC);
    if (ret_tjPlaneSizeYUV_hugjl < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function tjInitCompress with tjInitTransform
    tjhandle handle = tjInitTransform();
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (handle) {
        // Test tjDecompress2
        unsigned char *dstBuf = (unsigned char *)malloc(width * height * tjPixelSize[pixelFormat]);
        if (dstBuf) {
            tjDecompress2(handle, Data, Size, dstBuf, width, pitch, height, pixelFormat, flags);
            free(dstBuf);
        }
        tjDestroy(handle);
    }

    // Re-create a TurboJPEG instance handle for tj3LoadImage16 and tj3SaveImage16
    handle = tj3Init(TJINIT_COMPRESS);
    if (handle) {
        // Allocate memory for tj3LoadImage16
        int width16 = 0, height16 = 0, pixelFormat16 = TJPF_RGB;
        unsigned short *imgBuffer16 = tj3LoadImage16(handle, filename, &width16, align, &height16, &pixelFormat16);
        if (imgBuffer16) {
            // Test tj3SaveImage16
            tj3SaveImage16(handle, filename, imgBuffer16, width16, pitch, height16, pixelFormat16);
            tj3Free(imgBuffer16);
        }

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjFree to tj3DecompressToYUVPlanes8
        tjhandle ret_tj3Init_rvnyz = tj3Init(TJFLAG_BOTTOMUP);
        char* ret_tj3GetErrorStr_wxpun = tj3GetErrorStr(0);
        if (ret_tj3GetErrorStr_wxpun == NULL){
        	return 0;
        }
        int ret_tj3GetErrorCode_nxvlp = tj3GetErrorCode(0);
        if (ret_tj3GetErrorCode_nxvlp < 0){
        	return 0;
        }

        int ret_tj3DecompressToYUVPlanes8_dtttg = tj3DecompressToYUVPlanes8(ret_tj3Init_rvnyz, (const unsigned char *)ret_tj3GetErrorStr_wxpun, TJ_NUMINIT, &imgBuffer, &ret_tj3GetErrorCode_nxvlp);
        if (ret_tj3DecompressToYUVPlanes8_dtttg < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        tj3Destroy(handle);
    }

    return 0;
}