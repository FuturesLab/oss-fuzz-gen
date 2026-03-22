#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

extern "C" {
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_59(const uint8_t *data, size_t size) {
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
    tjhandle ret_tj3Init_drcyg = tj3Init(TJXOPT_OPTIMIZE);

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of tj3Alloc
    void* ret_tj3Alloc_jiszz = tj3Alloc(TJ_NUMXOP);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_tj3Alloc_jiszz == NULL){
    	return 0;
    }
    unsigned char* ret_tjAlloc_wkyvj = tjAlloc(TJ_NUMERR);
    if (ret_tjAlloc_wkyvj == NULL){
    	return 0;
    }
    int yerxdsop = 64;
    tjscalingfactor* ret_tjGetScalingFactors_pkyfj = tjGetScalingFactors(&yerxdsop);
    if (ret_tjGetScalingFactors_pkyfj == NULL){
    	return 0;
    }
    int oogmukuk = -1;

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjGetScalingFactors to tj3DecompressToYUV8
    tjhandle ret_tjInitTransform_rdeha = tjInitTransform();
    unsigned char* ret_tjAlloc_qahky = tjAlloc(TJFLAG_FORCEMMX);
    if (ret_tjAlloc_qahky == NULL){
    	return 0;
    }

    int ret_tj3DecompressToYUV8_cobdw = tj3DecompressToYUV8(ret_tjInitTransform_rdeha, ret_tjAlloc_wkyvj, (size_t )yerxdsop, ret_tjAlloc_qahky, TJFLAG_LIMITSCANS);
    if (ret_tj3DecompressToYUV8_cobdw < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tjscalingfactor* ret_tjGetScalingFactors_jkhnx = tjGetScalingFactors(&oogmukuk);
    if (ret_tjGetScalingFactors_jkhnx == NULL){
    	return 0;
    }
    const int oszmkoil = size;

    int ret_tjCompressFromYUVPlanes_eaesf = tjCompressFromYUVPlanes(ret_tj3Init_drcyg, (const unsigned char **)&ret_tj3Alloc_jiszz, width, &oszmkoil, TJXOPT_GRAY, 1, &ret_tjAlloc_wkyvj, (unsigned long *)&yerxdsop, oogmukuk, 64);
    if (ret_tjCompressFromYUVPlanes_eaesf < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tjDestroy(handle);
    return 0;
}