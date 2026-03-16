#include <iostream>
#include "sstream"
#include <string>
#include <vector>
#include "cstring"
#include "cstdlib"
#include <cstdio>
#include "cstdint"
#include <cstddef>
#include "tiffio.h"
#include "cstdint"
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>

static int customErrorHandler(TIFF* tif, void* user_data, const char* module, const char* fmt, va_list ap) {
    // Custom error handler that does nothing
    return 0;
}

extern "C" int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare dummy file
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the file descriptor
    int fd = open("./dummy_file", O_RDONLY);
    if (fd < 0) return 0;

    // 1. Test TIFFFdOpen
    TIFF *tiff1 = TIFFFdOpen(fd, "dummy_file", "r");
    if (tiff1) {
        TIFFClose(tiff1);
    }

    // 2. Test TIFFOpenOptionsAlloc
    TIFFOpenOptions *opts = TIFFOpenOptionsAlloc();
    if (opts) {
        // 3. Test TIFFOpenOptionsSetErrorHandlerExtR
        TIFFOpenOptionsSetErrorHandlerExtR(opts, customErrorHandler, nullptr);

        // 4. Test TIFFFdOpenExt
        TIFF *tiff2 = TIFFFdOpenExt(fd, "dummy_file", "r", opts);
        if (tiff2) {
            TIFFClose(tiff2);
        }

        // 5. Test TIFFOpenExt
        TIFF *tiff3 = TIFFOpenExt("dummy_file", "r", opts);
        if (tiff3) {
            TIFFClose(tiff3);
        }

        TIFFOpenOptionsFree(opts);
    }

    // Close the file descriptor
    close(fd);

    // 6. Test TIFFClientOpenExt with dummy callbacks
    TIFF *tiff4 = TIFFClientOpenExt(
        "dummy_file", "r", (thandle_t)fd,
        [](thandle_t, void*, tmsize_t) -> tmsize_t { return 0; }, // Read
        [](thandle_t, void*, tmsize_t) -> tmsize_t { return 0; }, // Write
        [](thandle_t, toff_t, int) -> toff_t { return 0; },       // Seek
        [](thandle_t) -> int { return 0; },                       // Close
        [](thandle_t) -> toff_t { return 0; },                    // Size
        nullptr,                                                  // Map
        nullptr,                                                  // Unmap
        nullptr                                                   // Options
    );
    if (tiff4) {
        TIFFClose(tiff4);
    }

    return 0;
}