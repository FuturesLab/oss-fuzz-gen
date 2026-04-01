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
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstdio>

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    } // Early exit if no data is provided

    tjhandle handle = tjInitDecompress();
    if (!handle) {
        return 0;
    } // Failed to initialize TurboJPEG handle

    // Variables to store image properties
    int width, height, jpegSubsamp, jpegColorspace;
    unsigned char *iccBuf = nullptr;
    size_t iccSize = 0;

    // Call tj3DecompressHeader
    tj3DecompressHeader(handle, Data, Size);

    // Call tj3GetICCProfile
    tj3GetICCProfile(handle, &iccBuf, &iccSize);
    if (iccBuf) {
        tj3Free(iccBuf);
    } // Free ICC buffer if allocated

    // Call tjDecompressHeader3
    tjDecompressHeader3(handle, Data, Size, &width, &height, &jpegSubsamp, &jpegColorspace);

    // Call tj3GetErrorCode
    int errorCode = tj3GetErrorCode(handle);

    // Call tjDecompressHeader2
    tjDecompressHeader2(handle, const_cast<unsigned char*>(Data), Size, &width, &height, &jpegSubsamp);

    // Call tjDecompressHeader
    tjDecompressHeader(handle, const_cast<unsigned char*>(Data), Size, &width, &height);

    // Cleanup

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjDecompressHeader to tjTransform
    tjhandle ret_tj3Init_rwhbr = tj3Init(errorCode);
    char* ret_tjGetErrorStr_nctbt = tjGetErrorStr();
    if (ret_tjGetErrorStr_nctbt == NULL){
    	return 0;
    }
    int jofablbl = 64;
    tjscalingfactor* ret_tj3GetScalingFactors_gykrz = tj3GetScalingFactors(&jofablbl);
    if (ret_tj3GetScalingFactors_gykrz == NULL){
    	return 0;
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tj3GetScalingFactors to tj3Decompress12
    tjhandle ret_tj3Init_ivaxf = tj3Init(TJFLAG_PROGRESSIVE);
    unsigned char* ret_tjAlloc_igose = tjAlloc((int )iccSize);
    if (ret_tjAlloc_igose == NULL){
    	return 0;
    }
    int yojpvgii = Size;
    tjscalingfactor* ret_tjGetScalingFactors_midmm = tjGetScalingFactors(&yojpvgii);
    if (ret_tjGetScalingFactors_midmm == NULL){
    	return 0;
    }

    int ret_tj3Decompress12_fjsoe = tj3Decompress12(ret_tj3Init_ivaxf, ret_tjAlloc_igose, (size_t )jofablbl, NULL, yojpvgii, TJXOPT_GRAY);
    if (ret_tj3Decompress12_fjsoe < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tjFree(iccBuf);

    int ret_tjTransform_cggiq = tjTransform(ret_tj3Init_rwhbr, (const unsigned char *)ret_tjGetErrorStr_nctbt, (unsigned long )jofablbl, TJXOPT_ARITHMETIC, &iccBuf, (unsigned long *)&width, NULL, width);
    if (ret_tjTransform_cggiq < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tjDestroy(handle);

    return 0;
}