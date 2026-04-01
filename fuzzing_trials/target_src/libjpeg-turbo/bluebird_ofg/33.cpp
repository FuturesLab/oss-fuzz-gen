#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

extern "C" {
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0; // Not enough data to be a valid JPEG
    }

    tjhandle handle = tjInitDecompress();
    if (handle == NULL) {
        return 0; // Initialization failed
    }

    int width, height, jpegSubsamp, jpegColorspace;
    // Cast away constness for the tjDecompressHeader2 function call
    if (tjDecompressHeader2(handle, const_cast<unsigned char*>(data), size, &width, &height, &jpegSubsamp) == 0) {
        // Allocate buffer for decompressed image
        unsigned char *buffer = (unsigned char *)malloc(width * height * tjPixelSize[TJPF_RGB]);
        if (buffer != NULL) {
            // Attempt to decompress the image
            tjDecompress2(handle, const_cast<unsigned char*>(data), size, buffer, width, 0, height, TJPF_RGB, TJFLAG_FASTDCT);
            free(buffer);
        }
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjDecompressHeader2 to tjCompressFromYUVPlanes
    tjhandle ret_tj3Init_ilsxf = tj3Init(TJXOPT_PROGRESSIVE);

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of tj3Alloc
    void* ret_tj3Alloc_rcjmn = tj3Alloc(TJXOPT_NOOUTPUT);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_tj3Alloc_rcjmn == NULL){
    	return 0;
    }
    int ret_tjGetErrorCode_kaail = tjGetErrorCode(0);
    if (ret_tjGetErrorCode_kaail < 0){
    	return 0;
    }
    int dixhvkkg = -1;
    tjscalingfactor* ret_tj3GetScalingFactors_qxiei = tj3GetScalingFactors(&dixhvkkg);
    if (ret_tj3GetScalingFactors_qxiei == NULL){
    	return 0;
    }
    const int oszmkoil = 64;

    int ret_tjCompressFromYUVPlanes_wokyi = tjCompressFromYUVPlanes(ret_tj3Init_ilsxf, (const unsigned char **)&ret_tj3Alloc_rcjmn, ret_tjGetErrorCode_kaail, &oszmkoil, TJFLAG_STOPONWARNING, dixhvkkg, (unsigned char **)"w", (unsigned long *)&width, TJ_YUV, TJFLAG_FORCESSE3);
    if (ret_tjCompressFromYUVPlanes_wokyi < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tjDestroy(handle);
    return 0;
}