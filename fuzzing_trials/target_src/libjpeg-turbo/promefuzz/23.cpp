// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjInitDecompress at turbojpeg.c:1808:20 in turbojpeg.h
// tjGetErrorStr at turbojpeg.c:636:17 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tj3GetErrorCode at turbojpeg.c:643:15 in turbojpeg.h
// tj3DecompressHeader at turbojpeg.c:1815:15 in turbojpeg.h
// tj3GetICCProfile at turbojpeg.c:1926:15 in turbojpeg.h
// tj3Free at turbojpeg.c:890:16 in turbojpeg.h
// tjDecompressHeader3 at turbojpeg.c:1874:15 in turbojpeg.h
// tjDecompressHeader2 at turbojpeg.c:1903:15 in turbojpeg.h
// tjDecompressHeader at turbojpeg.c:1914:15 in turbojpeg.h
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
#include <cstdio>
#include <cstring>

static tjhandle initializeTurboJPEG() {
    tjhandle handle = tjInitDecompress();
    if (!handle) {
        fprintf(stderr, "Failed to initialize TurboJPEG: %s\n", tjGetErrorStr());
    }
    return handle;
}

static void cleanupTurboJPEG(tjhandle handle) {
    if (handle) {
        tjDestroy(handle);
    }
}

static void handleError(tjhandle handle) {
    int errorCode = tj3GetErrorCode(handle);
    if (errorCode != 0) {
        fprintf(stderr, "TurboJPEG error code: %d\n", errorCode);
    }
}

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    tjhandle handle = initializeTurboJPEG();
    if (!handle) return 0;

    int width, height, subsamp, colorspace;
    unsigned char *iccBuf = nullptr;
    size_t iccSize = 0;

    // Test tj3DecompressHeader
    int result = tj3DecompressHeader(handle, Data, Size);
    if (result == 0) {
        // Test tj3GetICCProfile
        result = tj3GetICCProfile(handle, &iccBuf, &iccSize);
        if (result == 0 && iccBuf) {
            tj3Free(iccBuf);
        }
    }

    // Test tjDecompressHeader3
    result = tjDecompressHeader3(handle, Data, Size, &width, &height, &subsamp, &colorspace);
    if (result != 0) {
        handleError(handle);
    }

    // Test tjDecompressHeader2
    result = tjDecompressHeader2(handle, const_cast<unsigned char*>(Data), Size, &width, &height, &subsamp);
    if (result != 0) {
        handleError(handle);
    }

    // Test tjDecompressHeader
    result = tjDecompressHeader(handle, const_cast<unsigned char*>(Data), Size, &width, &height);
    if (result != 0) {
        handleError(handle);
    }

    cleanupTurboJPEG(handle);
    return 0;
}