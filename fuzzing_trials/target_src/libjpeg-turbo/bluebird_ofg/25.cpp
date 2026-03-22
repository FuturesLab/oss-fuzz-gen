#include <stdint.h>
#include <stddef.h>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    // Initialize the TurboJPEG handle
    tjhandle handle = tjInitCompress();
    if (handle == nullptr) {
        return 0; // If initialization failed, exit early
    }

    // Ensure that the data is not null and size is greater than zero
    if (data == nullptr || size == 0) {
        tjDestroy(handle);
        return 0;
    }

    // Allocate memory for a dummy image buffer
    int width = 100, height = 100, subsamp = TJSAMP_444, jpegQual = 75;
    unsigned long jpegSize = 0;
    unsigned char *jpegBuf = nullptr;

    // Ensure the input data size is large enough for the dummy image
    if (size < static_cast<size_t>(width * height * tjPixelSize[TJPF_RGB])) {
        tjDestroy(handle);
        return 0;
    }

    // Compress the image to JPEG format
    int compressResult = tjCompress2(handle, (unsigned char *)data, width, 0, height, TJPF_RGB,
                                     &jpegBuf, &jpegSize, subsamp, jpegQual, TJFLAG_FASTDCT);
    if (compressResult == 0 && jpegBuf != nullptr) {
        // Call the function-under-test with the compressed JPEG buffer
        tj3SetICCProfile(handle, jpegBuf, jpegSize);
    }

    // Clean up the TurboJPEG handle and free the JPEG buffer
    tjDestroy(handle);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tj3SetICCProfile to tj3GetICCProfile
        tjhandle ret_tj3Init_bebgt = tj3Init(TJFLAG_FORCESSE3);
        size_t mbgmnymw = 64;

        int ret_tj3GetICCProfile_ipihz = tj3GetICCProfile(ret_tj3Init_bebgt, &jpegBuf, &mbgmnymw);
        if (ret_tj3GetICCProfile_ipihz < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

    tjFree(jpegBuf);

    return 0;
}