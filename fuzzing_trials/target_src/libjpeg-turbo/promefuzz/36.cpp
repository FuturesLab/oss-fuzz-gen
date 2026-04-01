// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjInitCompress at turbojpeg.c:1157:20 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjCompress2 at turbojpeg.c:1204:15 in turbojpeg.h
// tjGetErrorCode at turbojpeg.c:652:15 in turbojpeg.h
// tjFree at turbojpeg.c:896:16 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjInitCompress at turbojpeg.c:1157:20 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjCompressFromYUVPlanes at turbojpeg.c:1394:15 in turbojpeg.h
// tj3GetErrorCode at turbojpeg.c:643:15 in turbojpeg.h
// tjFree at turbojpeg.c:896:16 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <turbojpeg.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize tjhandle
    tjhandle handle = tjInitCompress();
    if (!handle) return 0;

    // Prepare dummy image data for compression
    int width = 100;
    int height = 100;
    int pixelFormat = TJPF_RGB;
    int jpegQual = 75;
    int jpegSubsamp = TJSAMP_444;
    int flags = 0;
    unsigned long jpegSize = 0;
    unsigned char *jpegBuf = nullptr;

    // Prepare a dummy source buffer
    unsigned char *srcBuf = (unsigned char *)malloc(width * height * tjPixelSize[pixelFormat]);
    if (!srcBuf) {
        tjDestroy(handle);
        return 0;
    }
    memset(srcBuf, 0, width * height * tjPixelSize[pixelFormat]);

    // Attempt to compress the data
    tjCompress2(handle, srcBuf, width, 0, height, pixelFormat, &jpegBuf, &jpegSize, jpegSubsamp, jpegQual, flags);

    // Retrieve the error code
    int errorCode = tjGetErrorCode(handle);
    std::cout << "Error Code: " << errorCode << std::endl;

    // Free the JPEG buffer if it was allocated
    if (jpegBuf) {
        tjFree(jpegBuf);
        jpegBuf = nullptr;
    }

    // Cleanup
    free(srcBuf);
    tjDestroy(handle);

    // Initialize another tjhandle for YUV compression
    handle = tjInitCompress();
    if (!handle) return 0;

    // Ensure the input data is large enough for YUV planes
    if (Size < width * height * 3 / 2) {
        tjDestroy(handle);
        return 0;
    }

    // Prepare dummy YUV planes
    const unsigned char *srcPlanes[3];
    int strides[3] = { width, width / 2, width / 2 };
    srcPlanes[0] = Data;
    srcPlanes[1] = Data + width * height;
    srcPlanes[2] = Data + width * height + (width / 2) * (height / 2);

    // Attempt to compress from YUV planes
    tjCompressFromYUVPlanes(handle, srcPlanes, width, strides, height, jpegSubsamp, &jpegBuf, &jpegSize, jpegQual, flags);

    // Retrieve the error code
    errorCode = tj3GetErrorCode(handle);
    std::cout << "YUV Error Code: " << errorCode << std::endl;

    // Cleanup
    if (jpegBuf) {
        tjFree(jpegBuf);
        jpegBuf = nullptr;
    }
    tjDestroy(handle);

    return 0;
}