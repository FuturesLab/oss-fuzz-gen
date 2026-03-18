// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3Init at turbojpeg.c:538:20 in turbojpeg.h
// tj3Init at turbojpeg.c:538:20 in turbojpeg.h
// tj3Destroy at turbojpeg.c:580:16 in turbojpeg.h
// tj3Destroy at turbojpeg.c:580:16 in turbojpeg.h
// tj3Set at turbojpeg.c:671:15 in turbojpeg.h
// tj3Set at turbojpeg.c:671:15 in turbojpeg.h
// tj3Get at turbojpeg.c:807:15 in turbojpeg.h
// tj3Get at turbojpeg.c:807:15 in turbojpeg.h
// tj3SetICCProfile at turbojpeg.c:1164:15 in turbojpeg.h
// tj3DecompressHeader at turbojpeg.c:1815:15 in turbojpeg.h
// tj3GetICCProfile at turbojpeg.c:1926:15 in turbojpeg.h
// tj3Free at turbojpeg.c:890:16 in turbojpeg.h
// tj3Destroy at turbojpeg.c:580:16 in turbojpeg.h
// tj3Destroy at turbojpeg.c:580:16 in turbojpeg.h
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
#include <cstdio>

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize a TurboJPEG instance for both compression and decompression
    tjhandle compressHandle = tj3Init(TJINIT_COMPRESS);
    tjhandle decompressHandle = tj3Init(TJINIT_DECOMPRESS);

    if (!compressHandle || !decompressHandle) {
        if (compressHandle) tj3Destroy(compressHandle);
        if (decompressHandle) tj3Destroy(decompressHandle);
        return 0;
    }

    // Fuzz tj3Set with random parameters and values from the input data
    int param = Data[0];
    int value = (Size > 1) ? Data[1] : 0;
    tj3Set(compressHandle, param, value);
    tj3Set(decompressHandle, param, value);

    // Fuzz tj3Get with random parameters
    tj3Get(compressHandle, param);
    tj3Get(decompressHandle, param);

    // Fuzz tj3SetICCProfile with a portion of the input data
    if (Size > 2) {
        unsigned char *iccBuf = (unsigned char *)malloc(Size - 2);
        if (iccBuf) {
            memcpy(iccBuf, Data + 2, Size - 2);
            tj3SetICCProfile(compressHandle, iccBuf, Size - 2);
            free(iccBuf);
        }
    }

    // Fuzz tj3DecompressHeader with the input data
    tj3DecompressHeader(decompressHandle, Data, Size);

    // Fuzz tj3GetICCProfile to retrieve potential ICC profile
    unsigned char *iccBuf = nullptr;
    size_t iccSize = 0;
    tj3GetICCProfile(decompressHandle, &iccBuf, &iccSize);
    if (iccBuf) tj3Free(iccBuf);

    // Clean up and destroy TurboJPEG instances
    tj3Destroy(compressHandle);
    tj3Destroy(decompressHandle);

    return 0;
}