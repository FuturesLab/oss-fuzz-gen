#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_65(const uint8_t *data, size_t size) {
    // Initialize variables for tjEncodeYUV2 function
    tjhandle handle = tjInitCompress();
    unsigned char *srcBuf = nullptr;
    int width = 0;
    int pitch = 0;
    int height = 0;
    int pixelFormat = TJPF_RGB;
    unsigned char *dstBuf = nullptr;
    int subsamp = TJSAMP_420;
    int flags = 0;

    // Ensure the data size is sufficient to define width and height
    if (size < 8) {
        tjDestroy(handle);
        return 0;
    }

    // Extract width and height from the data
    width = (data[0] << 8) | data[1];
    height = (data[2] << 8) | data[3];
    pitch = width * tjPixelSize[pixelFormat];

    // Allocate memory for source and destination buffers
    srcBuf = (unsigned char *)malloc(width * height * tjPixelSize[pixelFormat]);
    dstBuf = (unsigned char *)malloc(tjBufSizeYUV2(width, pitch, height, subsamp));

    // Check if memory allocation was successful
    if (srcBuf == nullptr || dstBuf == nullptr) {
        free(srcBuf);
        free(dstBuf);
        tjDestroy(handle);
        return 0;
    }

    // Copy data into srcBuf
    size_t copySize = width * height * tjPixelSize[pixelFormat];
    if (copySize > size - 4) {
        copySize = size - 4;
    }
    memcpy(srcBuf, data + 4, copySize);

    // Call the function-under-test
    tjEncodeYUV2(handle, srcBuf, width, pitch, height, pixelFormat, dstBuf, subsamp, flags);

    // Clean up
    free(srcBuf);
    free(dstBuf);
    tjDestroy(handle);

    return 0;
}