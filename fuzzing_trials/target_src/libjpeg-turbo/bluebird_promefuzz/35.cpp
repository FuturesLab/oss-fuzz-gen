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

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjDecompressHeader to tjCompress
    tjhandle ret_tj3Init_qliuq = tj3Init(TJ_NUMINIT);
    unsigned char* ret_tjAlloc_zwhbi = tjAlloc(Size);
    if (ret_tjAlloc_zwhbi == NULL){
    	return 0;
    }
    int noajxrzs = 1;
    tjscalingfactor* ret_tjGetScalingFactors_bytbk = tjGetScalingFactors(&noajxrzs);
    if (ret_tjGetScalingFactors_bytbk == NULL){
    	return 0;
    }
    tjscalingfactor* ret_tjGetScalingFactors_qmvtj = tjGetScalingFactors(&width);
    if (ret_tjGetScalingFactors_qmvtj == NULL){
    	return 0;
    }
    unsigned char* ret_tjAlloc_rtoyr = tjAlloc(TJFLAG_PROGRESSIVE);
    if (ret_tjAlloc_rtoyr == NULL){
    	return 0;
    }
    unsigned long zydnuuvm = -1;

    int ret_tjCompress_ndpff = tjCompress(ret_tj3Init_qliuq, ret_tjAlloc_zwhbi, TJXOPT_PERFECT, noajxrzs, width, width, ret_tjAlloc_rtoyr, &zydnuuvm, TJXOPT_CROP, TJFLAG_STOPONWARNING, -1);
    if (ret_tjCompress_ndpff < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tjDestroy(handle);

    return 0;
}