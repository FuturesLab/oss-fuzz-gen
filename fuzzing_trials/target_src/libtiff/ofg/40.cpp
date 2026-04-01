#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstring>

// Define dummy callback functions for the TIFFClientOpen function
tsize_t dummyReadWriteProc(thandle_t, tdata_t, tsize_t) {
    return 0;
}

toff_t dummySeekProc(thandle_t, toff_t, int) {
    return 0;
}

int dummyCloseProc(thandle_t) {
    return 0;
}

toff_t dummySizeProc(thandle_t) {
    return 0;
}

int dummyMapFileProc(thandle_t, tdata_t *, toff_t *) {
    return 0;
}

void dummyUnmapFileProc(thandle_t, tdata_t, toff_t) {
}

// Fuzzing harness
extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    // Ensure data is large enough to create a valid string
    if (size < 2) {
        return 0;
    }

    // Create input strings for TIFFClientOpen
    char filename[256];
    char mode[4];

    // Copy data into filename and mode, ensuring null termination
    size_t filename_len = (size - 1 < 255) ? size - 1 : 255;
    memcpy(filename, data, filename_len);
    filename[filename_len] = '\0';

    memcpy(mode, data + filename_len, 3);
    mode[3] = '\0';

    // Call TIFFClientOpen with dummy functions
    TIFF *tiff = TIFFClientOpen(
        filename,
        mode,
        nullptr,
        dummyReadWriteProc,
        dummyReadWriteProc,
        dummySeekProc,
        dummyCloseProc,
        dummySizeProc,
        dummyMapFileProc,
        dummyUnmapFileProc
    );

    if (tiff) {
        TIFFClose(tiff);
    }

    return 0;
}