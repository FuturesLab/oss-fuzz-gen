#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include the string.h library for memcpy

extern "C" {
    #include <tiffio.h>
    #include <tiff.h> // Include the internal header to access the definition of TIFFField

    int TIFFFieldReadCount(const TIFFField *);
    const TIFFField *TIFFFindField(TIFF *tif, uint32_t tag, TIFFDataType dt);
}

extern "C" int LLVMFuzzerTestOneInput_294(const uint8_t *data, size_t size) {
    // Create a TIFF memory stream from the input data
    TIFF *tif = TIFFClientOpen("MemTIFF", "r", (thandle_t)data,
                               [](thandle_t fd, tdata_t buf, tsize_t size) -> tsize_t {
                                   memcpy(buf, (void*)fd, size);
                                   return size;
                               },
                               [](thandle_t, tdata_t, tsize_t) -> tsize_t { return 0; },
                               [](thandle_t, toff_t, int) -> toff_t { return 0; },
                               [](thandle_t) -> int { return 0; },
                               [](thandle_t) -> toff_t { return 0; },
                               [](thandle_t, tdata_t*, toff_t*) -> int { return 0; }, // Add missing TIFFMapFileProc
                               [](thandle_t, tdata_t, toff_t) -> void { }); // Add missing TIFFUnmapFileProc

    if (!tif) {
        return 0;
    }

    // Find a field in the TIFF structure to pass to TIFFFieldReadCount
    const TIFFField *field = TIFFFindField(tif, 0, TIFF_NOTYPE);
    if (field) {
        // Call the function-under-test
        int readCount = TIFFFieldReadCount(field);

        // Use the result to avoid compiler optimizations removing the call
        volatile int result = readCount;
        (void)result;
    }

    // Close the TIFF stream
    TIFFClose(tif);

    return 0;
}