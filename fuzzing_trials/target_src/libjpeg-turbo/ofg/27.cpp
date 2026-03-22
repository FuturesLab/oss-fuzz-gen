#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    // Initialize the TurboJPEG decompressor
    tjhandle handle = tjInitDecompress();
    
    // Check if the handle is initialized correctly
    if (handle == NULL) {
        return 0; // Initialization failed, exit early
    }

    int width, height, jpegSubsamp, jpegColorspace;

    // Attempt to decompress the JPEG image header
    if (tjDecompressHeader3(handle, data, size, &width, &height, &jpegSubsamp, &jpegColorspace) == 0) {
        // Allocate a buffer for the decompressed image
        unsigned char *buffer = (unsigned char *)malloc(width * height * tjPixelSize[TJPF_RGB]);
        
        if (buffer != NULL) {
            // Decompress the JPEG image
            tjDecompress2(handle, data, size, buffer, width, 0 /* pitch */, height, TJPF_RGB, TJFLAG_FASTDCT);
            
            // Free the buffer
            free(buffer);
        }
    }

    // Clean up the TurboJPEG handle
    tjDestroy(handle);

    return 0;
}