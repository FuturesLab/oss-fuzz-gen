#include <tiffio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy

extern "C" {
    TIFF *TIFFClientOpenExt(const char *, const char *, thandle_t, TIFFReadWriteProc, TIFFReadWriteProc, TIFFSeekProc, TIFFCloseProc, TIFFSizeProc, TIFFMapFileProc, TIFFUnmapFileProc, TIFFOpenOptions *);
}

// Dummy implementations for the required TIFF callback functions
tsize_t dummyReadProc(thandle_t, tdata_t, tsize_t) {
    return 0;
}

tsize_t dummyWriteProc(thandle_t, tdata_t, tsize_t) {
    return 0;
}

toff_t dummySeekProc_290(thandle_t, toff_t, int) {
    return 0;
}

int dummyCloseProc_290(thandle_t) {
    return 0;
}

toff_t dummySizeProc_290(thandle_t) {
    return 0;
}

int dummyMapFileProc_290(thandle_t, tdata_t *, toff_t *) {
    return 0;
}

void dummyUnmapFileProc_290(thandle_t, tdata_t, toff_t) {
}

extern "C" int LLVMFuzzerTestOneInput_290(const uint8_t *data, size_t size) {
    // Ensure that the data is null-terminated for safe string operations
    char *filename = (char *)malloc(size + 1);
    if (!filename) {
        return 0;
    }
    memcpy(filename, data, size);
    filename[size] = '\0';

    // Use a fixed mode for simplicity
    const char *mode = "r";

    // Dummy thandle_t and TIFFOpenOptions
    thandle_t handle = 0;
    TIFFOpenOptions *options = nullptr;

    // Call the function-under-test
    TIFF *tiff = TIFFClientOpenExt(filename, mode, handle, dummyReadProc, dummyWriteProc, dummySeekProc_290, dummyCloseProc_290, dummySizeProc_290, dummyMapFileProc_290, dummyUnmapFileProc_290, options);

    // If a TIFF object was created, close it
    if (tiff) {
        TIFFClose(tiff);
    }

    free(filename);
    return 0;
}