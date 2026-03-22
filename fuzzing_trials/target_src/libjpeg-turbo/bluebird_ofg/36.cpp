#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

extern "C" {
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjDecompressHeader2 to tjEncodeYUVPlanes
    char* ret_tjGetErrorStr2_dyvlf = tjGetErrorStr2(handle);
    if (ret_tjGetErrorStr2_dyvlf == NULL){
    	return 0;
    }
    int whqatsdl = 1;

    int ret_tjEncodeYUVPlanes_kfkwq = tjEncodeYUVPlanes(handle, (const unsigned char *)"r", TJFLAG_STOPONWARNING, size, width, TJFLAG_STOPONWARNING, (unsigned char **)&ret_tjGetErrorStr2_dyvlf, &whqatsdl, TJ_NUMINIT, TJ_NUMCS);
    if (ret_tjEncodeYUVPlanes_kfkwq < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tjhandle ret_tj3Init_vyoau = tj3Init(TJ_NUMERR);
    void* ret_tj3Alloc_iolaj = tj3Alloc(TJXOPT_ARITHMETIC);
    if (ret_tj3Alloc_iolaj == NULL){
    	return 0;
    }
    tjscalingfactor* ret_tjGetScalingFactors_ywhjr = tjGetScalingFactors(&width);
    if (ret_tjGetScalingFactors_ywhjr == NULL){
    	return 0;
    }
    tjscalingfactor* ret_tj3GetScalingFactors_srtye = tj3GetScalingFactors(&width);
    if (ret_tj3GetScalingFactors_srtye == NULL){
    	return 0;
    }
    char* ret_tj3GetErrorStr_rduat = tj3GetErrorStr(0);
    if (ret_tj3GetErrorStr_rduat == NULL){
    	return 0;
    }
    int yerxdsop = 1;
    tjscalingfactor* ret_tjGetScalingFactors_pcwym = tjGetScalingFactors(&yerxdsop);
    if (ret_tjGetScalingFactors_pcwym == NULL){
    	return 0;
    }

    int ret_tjCompressFromYUVPlanes_wqxli = tjCompressFromYUVPlanes(ret_tj3Init_vyoau, (const unsigned char **)&ret_tj3Alloc_iolaj, width, &width, width, TJ_ALPHAFIRST, (unsigned char **)&ret_tj3GetErrorStr_rduat, (unsigned long *)&yerxdsop, TJXOPT_COPYNONE, TJXOPT_CROP);
    if (ret_tjCompressFromYUVPlanes_wqxli < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tjDestroy(handle);
    return 0;
}