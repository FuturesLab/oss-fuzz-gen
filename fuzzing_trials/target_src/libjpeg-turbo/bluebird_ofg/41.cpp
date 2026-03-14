#include <cstdint>
#include <cstdlib>

extern "C" {
#include "/src/libjpeg-turbo.main/src/turbojpeg.h"
#include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
#include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
    // Initialize variables
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0;
    }

    // Define parameters for tjDecompressToYUV2
    const unsigned char *jpegBuf = data;
    unsigned long jpegSize = static_cast<unsigned long>(size);

    // Assuming some arbitrary dimensions for the YUV output
    int width = 128;  // Width of the image
    int height = 128; // Height of the image
    int strides = width; // Strides for YUV planes

    // Allocate memory for the YUV buffer
    unsigned char *yuvBuf = static_cast<unsigned char *>(malloc(width * height * 3));
    if (yuvBuf == nullptr) {
        tjDestroy(handle);
        return 0;
    }

    // Call the function-under-test
    int result = tjDecompressToYUV2(handle, jpegBuf, jpegSize, yuvBuf, width, strides, height, 0);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjDecompressToYUV2 to tj3Decompress12
    tjhandle ret_tj3Init_ddzny = tj3Init(TJ_NUMSAMP);
    int phoycpzm = -1;
    tjscalingfactor* ret_tj3GetScalingFactors_fmlyj = tj3GetScalingFactors(&phoycpzm);
    if (ret_tj3GetScalingFactors_fmlyj == NULL){
    	return 0;
    }

    int ret_tj3Decompress12_ufobm = tj3Decompress12(ret_tj3Init_ddzny, yuvBuf, (size_t )phoycpzm, NULL, TJ_NUMXOP, TJFLAG_STOPONWARNING);
    if (ret_tj3Decompress12_ufobm < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tj3Decompress12 to tjDecompressHeader2
    tjhandle ret_tj3Init_szrzh = tj3Init(1);
    unsigned char* ret_tjAlloc_zwacx = tjAlloc(TJXOPT_COPYNONE);
    if (ret_tjAlloc_zwacx == NULL){
    	return 0;
    }
    int ret_tj3GetErrorCode_haetg = tj3GetErrorCode(handle);
    if (ret_tj3GetErrorCode_haetg < 0){
    	return 0;
    }
    int ret_tj3GetErrorCode_tltwv = tj3GetErrorCode(0);
    if (ret_tj3GetErrorCode_tltwv < 0){
    	return 0;
    }

    int ret_tjDecompressHeader2_ipkcq = tjDecompressHeader2(ret_tj3Init_szrzh, ret_tjAlloc_zwacx, TJ_NUMPF, &ret_tj3GetErrorCode_haetg, &ret_tj3GetErrorCode_tltwv, &ret_tj3Decompress12_ufobm);
    if (ret_tjDecompressHeader2_ipkcq < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    free(yuvBuf);
    tjDestroy(handle);

    return 0;
}