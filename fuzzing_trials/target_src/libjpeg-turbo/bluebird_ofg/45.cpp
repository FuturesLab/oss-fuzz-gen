#include <cstdint>
#include <cstdlib>

extern "C" {
#include "/src/libjpeg-turbo.main/src/turbojpeg.h"
#include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
#include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tj3Init to tj3SaveImage12
    void* ret_tj3Alloc_qajms = tj3Alloc(size);
    if (ret_tj3Alloc_qajms == NULL){
    	return 0;
    }
    int iufewwce = size;
    tjscalingfactor* ret_tj3GetScalingFactors_pqfqk = tj3GetScalingFactors(&iufewwce);
    if (ret_tj3GetScalingFactors_pqfqk == NULL){
    	return 0;
    }
    int ret_tj3GetErrorCode_puqno = tj3GetErrorCode(handle);
    if (ret_tj3GetErrorCode_puqno < 0){
    	return 0;
    }

    int ret_tj3SaveImage12_gadtv = tj3SaveImage12(ret_tj3Init_ddzny, (const char *)ret_tj3Alloc_qajms, NULL, TJFLAG_LIMITSCANS, TJXOPT_TRIM, iufewwce, ret_tj3GetErrorCode_puqno);
    if (ret_tj3SaveImage12_gadtv < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of tj3GetScalingFactors
    int wnzkdsnc = 64;
    tjscalingfactor* ret_tj3GetScalingFactors_fmlyj = tj3GetScalingFactors(&wnzkdsnc);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_tj3GetScalingFactors_fmlyj == NULL){
    	return 0;
    }

    int ret_tj3Decompress12_ufobm = tj3Decompress12(ret_tj3Init_ddzny, yuvBuf, (size_t )phoycpzm, NULL, TJ_NUMXOP, TJFLAG_STOPONWARNING);
    if (ret_tj3Decompress12_ufobm < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    free(yuvBuf);
    tjDestroy(handle);

    return 0;
}