// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjInitDecompress at turbojpeg.c:1808:20 in turbojpeg.h
// tj3DecompressHeader at turbojpeg.c:1815:15 in turbojpeg.h
// tj3GetICCProfile at turbojpeg.c:1926:15 in turbojpeg.h
// tj3Free at turbojpeg.c:890:16 in turbojpeg.h
// tjDecompressHeader3 at turbojpeg.c:1874:15 in turbojpeg.h
// tj3GetErrorCode at turbojpeg.c:643:15 in turbojpeg.h
// tjDecompressHeader2 at turbojpeg.c:1903:15 in turbojpeg.h
// tjDecompressHeader at turbojpeg.c:1914:15 in turbojpeg.h
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
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstdio>

extern "C" int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Early exit if no data is provided

    tjhandle handle = tjInitDecompress();
    if (!handle) return 0; // Failed to initialize TurboJPEG handle

    // Variables to store image properties
    int width, height, jpegSubsamp, jpegColorspace;
    unsigned char *iccBuf = nullptr;
    size_t iccSize = 0;

    // Call tj3DecompressHeader
    tj3DecompressHeader(handle, Data, Size);

    // Call tj3GetICCProfile
    tj3GetICCProfile(handle, &iccBuf, &iccSize);
    if (iccBuf) tj3Free(iccBuf); // Free ICC buffer if allocated

    // Call tjDecompressHeader3
    tjDecompressHeader3(handle, Data, Size, &width, &height, &jpegSubsamp, &jpegColorspace);

    // Call tj3GetErrorCode
    int errorCode = tj3GetErrorCode(handle);

    // Call tjDecompressHeader2
    tjDecompressHeader2(handle, const_cast<unsigned char*>(Data), Size, &width, &height, &jpegSubsamp);

    // Call tjDecompressHeader
    tjDecompressHeader(handle, const_cast<unsigned char*>(Data), Size, &width, &height);

    // Cleanup
    tjDestroy(handle);

    return 0;
}