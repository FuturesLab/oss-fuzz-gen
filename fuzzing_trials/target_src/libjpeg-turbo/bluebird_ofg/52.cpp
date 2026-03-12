#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    tjhandle handle = tjInitTransform();
    if (handle == nullptr) {
        return 0; // Handle initialization failure
    }

    unsigned char *jpegBuf = nullptr; // This will be allocated by tj3Transform
    size_t jpegSize = 0;
    int n = 1; // Number of transforms
    tjtransform transform;
    memset(&transform, 0, sizeof(tjtransform)); // Initialize transform with zeros

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of tj3Transform
    int result = tj3Transform(handle, (const unsigned char *)data, size, n, &jpegBuf, &jpegSize, &transform);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up
    if (jpegBuf != nullptr) {
        tjFree(jpegBuf);
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tj3Transform to tjPlaneSizeYUV
    int xvfaspvl = -1;
    tjscalingfactor* ret_tj3GetScalingFactors_cxido = tj3GetScalingFactors(&xvfaspvl);
    if (ret_tj3GetScalingFactors_cxido == NULL){
    	return 0;
    }
    int plalzfyo = 0;

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tj3GetScalingFactors to tj3EncodeYUVPlanes8
    tjhandle ret_tj3Init_zecsk = tj3Init(TJFLAG_FORCESSE3);
    unsigned char* ret_tjAlloc_ezmmo = tjAlloc(TJFLAG_FASTDCT);
    if (ret_tjAlloc_ezmmo == NULL){
    	return 0;
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjAlloc to tj3DecompressToYUV8
    tjhandle ret_tj3Init_tbkad = tj3Init(TJFLAG_BOTTOMUP);
    void* ret_tj3Alloc_uiwgb = tj3Alloc(TJFLAG_FORCESSE2);
    if (ret_tj3Alloc_uiwgb == NULL){
    	return 0;
    }

    int ret_tj3DecompressToYUV8_wrqmk = tj3DecompressToYUV8(ret_tj3Init_tbkad, ret_tjAlloc_ezmmo, TJXOPT_CROP, (unsigned char *)ret_tj3Alloc_uiwgb, TJFLAG_LIMITSCANS);
    if (ret_tj3DecompressToYUV8_wrqmk < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tjscalingfactor* ret_tjGetScalingFactors_gnzkt = tjGetScalingFactors(&xvfaspvl);
    if (ret_tjGetScalingFactors_gnzkt == NULL){
    	return 0;
    }
    unsigned char* ret_tjAlloc_ynhkx = tjAlloc(TJ_YUV);
    if (ret_tjAlloc_ynhkx == NULL){
    	return 0;
    }

    int ret_tj3EncodeYUVPlanes8_yjpex = tj3EncodeYUVPlanes8(ret_tj3Init_zecsk, ret_tjAlloc_ezmmo, xvfaspvl, TJXOPT_COPYNONE, TJFLAG_BOTTOMUP, TJFLAG_STOPONWARNING, &ret_tjAlloc_ynhkx, &xvfaspvl);
    if (ret_tj3EncodeYUVPlanes8_yjpex < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tjscalingfactor* ret_tj3GetScalingFactors_pxltf = tj3GetScalingFactors(&plalzfyo);
    if (ret_tj3GetScalingFactors_pxltf == NULL){
    	return 0;
    }

    unsigned long ret_tjPlaneSizeYUV_ogmhr = tjPlaneSizeYUV(xvfaspvl, TJ_NUMINIT, 1, result, plalzfyo);
    if (ret_tjPlaneSizeYUV_ogmhr < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tjDestroy(handle);

    return 0;
}