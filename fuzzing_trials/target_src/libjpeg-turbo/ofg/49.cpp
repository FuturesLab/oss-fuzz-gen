#include <stdint.h>
#include <stddef.h>
#include <cstring> // Include for memcpy
#include <cstdlib> // Include for malloc and free

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"

    // Function-under-test
    size_t tj3TransformBufSize(tjhandle handle, const tjtransform *transform);
}

extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    // Initialize tjhandle and tjtransform
    tjhandle handle = tjInitTransform();
    if (handle == NULL) {
        return 0;
    }

    tjtransform transform;
    transform.op = TJXOP_NONE;  // No transformation

    // Use input data to set options and region of interest
    if (size >= sizeof(int)) {
        transform.options = *((int*)data); // Set options using input data
        data += sizeof(int);
        size -= sizeof(int);
    } else {
        transform.options = 0; // Default to no options if not enough data
    }

    if (size >= sizeof(tjregion)) {
        memcpy(&transform.r, data, sizeof(tjregion)); // Set region of interest using input data
        data += sizeof(tjregion);
        size -= sizeof(tjregion);
    } else {
        transform.r.x = 0;          // Default region of interest x-coordinate
        transform.r.y = 0;          // Default region of interest y-coordinate
        transform.r.w = 1;          // Default region of interest width
        transform.r.h = 1;          // Default region of interest height
    }
    transform.customFilter = NULL; // No custom filter

    // Ensure we have some data left to simulate a JPEG buffer
    if (size > 0) {
        // Simulate a JPEG buffer with the remaining data
        unsigned char *jpegBuf = (unsigned char *)malloc(size);
        if (jpegBuf == NULL) {
            tjDestroy(handle);
            return 0;
        }
        memcpy(jpegBuf, data, size);

        // Call the function-under-test
        size_t bufSize = tj3TransformBufSize(handle, &transform);
        
        // Use the buffer size to ensure the function is effectively tested
        if (bufSize > 0) {
            unsigned char *dstBuf = (unsigned char *)malloc(bufSize);
            if (dstBuf != NULL) {
                // Perform a transformation to ensure the function is utilized
                unsigned char *dstBufs[1] = { dstBuf };
                size_t dstSizes[1] = { bufSize };
                tjtransform transforms[1] = { transform };

                int result = tj3Transform(handle, jpegBuf, size, 1, dstBufs, dstSizes, transforms);
                if (result == 0) {
                    // Transformation succeeded
                }
                free(dstBuf);
            }
        }

        // Free the simulated JPEG buffer
        free(jpegBuf);
    }

    // Clean up
    tjDestroy(handle);

    return 0;
}