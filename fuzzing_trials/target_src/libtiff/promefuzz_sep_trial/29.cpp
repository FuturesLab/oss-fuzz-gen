// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFSetErrorHandler at tif_error.c:32:18 in tiffio.h
// TIFFSetWarningHandler at tif_warning.c:32:18 in tiffio.h
// TIFFSetTagExtender at tif_dir.c:1685:16 in tiffio.h
// TIFFOpenExt at tif_unix.c:237:7 in tiffio.h
// TIFFWriteCheck at tif_write.c:605:5 in tiffio.h
// TIFFErrorExtR at tif_error.c:107:6 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdarg>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include "tiffio.h"

static TIFFErrorHandler previousErrorHandler = nullptr;
static TIFFErrorHandler previousWarningHandler = nullptr;
static TIFFExtendProc previousTagExtender = nullptr;

static void customErrorHandler(const char* module, const char* fmt, va_list ap) {
    // Avoid recursive calls to customErrorHandler
    if (previousErrorHandler && previousErrorHandler != customErrorHandler) {
        previousErrorHandler(module, fmt, ap);
    }
}

static void customWarningHandler(const char* module, const char* fmt, va_list ap) {
    // Avoid recursive calls to customWarningHandler
    if (previousWarningHandler && previousWarningHandler != customWarningHandler) {
        previousWarningHandler(module, fmt, ap);
    }
}

static void customTagExtender(TIFF* tif) {
    // Avoid recursive calls to customTagExtender
    if (previousTagExtender && previousTagExtender != customTagExtender) {
        previousTagExtender(tif);
    }
}

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Set custom handlers
    previousErrorHandler = TIFFSetErrorHandler(customErrorHandler);
    previousWarningHandler = TIFFSetWarningHandler(customWarningHandler);
    previousTagExtender = TIFFSetTagExtender(customTagExtender);

    // Prepare dummy file
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Try opening the TIFF file
    TIFF *tif = TIFFOpenExt("./dummy_file", "r", nullptr);
    if (tif) {
        // Check write capabilities
        TIFFWriteCheck(tif, 1, "fuzz_test");

        // Trigger error manually
        TIFFErrorExtR(tif, "fuzz_module", "Fuzzing error with data size %zu", Size);

        // Close TIFF
        TIFFClose(tif);
    }

    return 0;
}