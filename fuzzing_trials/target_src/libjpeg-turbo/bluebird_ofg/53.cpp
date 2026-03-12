#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
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

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of tjFree
        tjFree(NULL);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tj3Transform to tjPlaneSizeYUV
    int xvfaspvl = -1;
    tjscalingfactor* ret_tj3GetScalingFactors_cxido = tj3GetScalingFactors(&xvfaspvl);
    if (ret_tj3GetScalingFactors_cxido == NULL){
    	return 0;
    }
    int plalzfyo = 0;

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tj3GetScalingFactors to tjDecompress2
    tjhandle ret_tj3Init_auiho = tj3Init((int )jpegSize);
    void* ret_tj3Alloc_zpqkc = tj3Alloc(1);
    if (ret_tj3Alloc_zpqkc == NULL){
    	return 0;
    }
    void* ret_tj3Alloc_xyaqi = tj3Alloc(TJ_YUV);
    if (ret_tj3Alloc_xyaqi == NULL){
    	return 0;
    }
    int ret_tjDestroy_qfoyg = tjDestroy(handle);
    if (ret_tjDestroy_qfoyg < 0){
    	return 0;
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjDestroy to TJBUFSIZE


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of TJBUFSIZE
    unsigned long ret_TJBUFSIZE_ravwb = TJBUFSIZE(TJFLAG_FORCESSE3, TJXOPT_PROGRESSIVE);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_TJBUFSIZE_ravwb < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_tjDecompress2_cipre = tjDecompress2(ret_tj3Init_auiho, (const unsigned char *)ret_tj3Alloc_zpqkc, (unsigned long )result, (unsigned char *)ret_tj3Alloc_xyaqi, TJ_BGR, xvfaspvl, size, ret_tjDestroy_qfoyg, TJ_NUMXOP);
    if (ret_tjDecompress2_cipre < 0){
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