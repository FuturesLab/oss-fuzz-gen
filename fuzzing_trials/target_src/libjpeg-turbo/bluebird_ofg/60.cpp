#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    if (size < 10) {
        return 0; // Not enough data to proceed
    }

    // Initialize variables
    tjhandle handle = tjInitCompress();
    if (handle == nullptr) {
        return 0; // Initialization failed
    }

    // Extract parameters from the input data
    int width = (data[0] << 8) + data[1];
    int height = (data[2] << 8) + data[3];
    int subsamp = data[4] % 4; // Limit subsampling to valid values [0, 3]
    int flags = data[5] % 2;   // Limit flags to valid values [0, 1]

    // Ensure width and height are positive
    width = width > 0 ? width : 1;
    height = height > 0 ? height : 1;

    // Calculate the YUV buffer size
    int yuvSize = tjBufSizeYUV2(width, 4, height, subsamp);
    if (yuvSize <= 0 || yuvSize > static_cast<int>(size - 6)) {
        tjDestroy(handle);
        return 0; // Invalid YUV buffer size
    }

    // Create a YUV buffer and copy data into it
    const unsigned char *yuvBuffer = data + 6;

    // Allocate output buffer
    unsigned char *jpegBuf = nullptr;
    unsigned long jpegSize = 0;

    // Call the function under test
    int result = tjCompressFromYUV(handle, yuvBuffer, width, 4, height, subsamp, &jpegBuf, &jpegSize, 80, flags);

    // Clean up
    if (jpegBuf != nullptr) {
        tjFree(jpegBuf);
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjCompressFromYUV to tjEncodeYUV
    tjhandle ret_tj3Init_fctyo = tj3Init(TJFLAG_BOTTOMUP);
    int podavttr = 64;
    tjscalingfactor* ret_tjGetScalingFactors_crrdb = tjGetScalingFactors(&podavttr);
    if (ret_tjGetScalingFactors_crrdb == NULL){
    	return 0;
    }
    int ret_tj3GetErrorCode_wfjhd = tj3GetErrorCode(0);
    if (ret_tj3GetErrorCode_wfjhd < 0){
    	return 0;
    }
    int ret_tjGetErrorCode_fhwlg = tjGetErrorCode(handle);
    if (ret_tjGetErrorCode_fhwlg < 0){
    	return 0;
    }
    tjscalingfactor* ret_tj3GetScalingFactors_jqhfh = tj3GetScalingFactors(&result);
    if (ret_tj3GetScalingFactors_jqhfh == NULL){
    	return 0;
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tj3GetScalingFactors to tj3CompressFromYUVPlanes8
    tjhandle ret_tjInitDecompress_oqvdf = tjInitDecompress();
    unsigned char* ret_tjAlloc_khkji = tjAlloc(TJXOPT_ARITHMETIC);
    if (ret_tjAlloc_khkji == NULL){
    	return 0;
    }
    char* ret_tjGetErrorStr2_iqffx = tjGetErrorStr2(0);
    if (ret_tjGetErrorStr2_iqffx == NULL){
    	return 0;
    }
    size_t qvoyqiaz = -1;

    int ret_tj3CompressFromYUVPlanes8_mkeyg = tj3CompressFromYUVPlanes8(ret_tjInitDecompress_oqvdf, &ret_tjAlloc_khkji, TJ_NUMCS, &result, podavttr, (unsigned char **)&ret_tjGetErrorStr2_iqffx, &qvoyqiaz);
    if (ret_tj3CompressFromYUVPlanes8_mkeyg < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_tjEncodeYUV_mguay = tjEncodeYUV(ret_tj3Init_fctyo, jpegBuf, podavttr, TJXOPT_OPTIMIZE, ret_tj3GetErrorCode_wfjhd, TJXOPT_COPYNONE, (unsigned char *)data, ret_tjGetErrorCode_fhwlg, result);
    if (ret_tjEncodeYUV_mguay < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tjDestroy(handle);

    return result;
}