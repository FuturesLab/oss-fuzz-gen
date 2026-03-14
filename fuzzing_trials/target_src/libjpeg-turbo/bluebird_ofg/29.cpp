#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
    // Initialize variables for the function-under-test
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0; // If initialization fails, exit early
    }

    // Define dimensions and subsampling for the output YUV image
    int width = 640;
    int height = 480;
    int subsamp = TJSAMP_420; // Common subsampling format
    int flags = 0;

    // Calculate the buffer size for the YUV image
    int align = 4; // Alignment parameter for tjBufSizeYUV2
    unsigned long yuvSize = tjBufSizeYUV2(width, align, height, subsamp);

    // Allocate memory for the YUV buffer
    unsigned char *yuvBuffer = (unsigned char *)malloc(yuvSize);
    if (yuvBuffer == nullptr) {
        tjDestroy(handle);
        return 0; // If allocation fails, exit early
    }

    // Call the function-under-test
    int result = tjDecompressToYUV2(handle, data, size, yuvBuffer, width, align, height, flags);

    // Clean up resources

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjDecompressToYUV2 to tj3GetICCProfile
    tjhandle ret_tj3Init_gkvfr = tj3Init(TJFLAG_BOTTOMUP);
    size_t smwrlayt = 1;

    int ret_tj3GetICCProfile_vvcpc = tj3GetICCProfile(ret_tj3Init_gkvfr, &yuvBuffer, &smwrlayt);
    if (ret_tj3GetICCProfile_vvcpc < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    free(yuvBuffer);
    tjDestroy(handle);

    return 0;
}