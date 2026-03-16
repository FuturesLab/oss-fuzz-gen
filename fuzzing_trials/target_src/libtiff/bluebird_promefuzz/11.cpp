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
#include <cstddef>
#include <cstdio>
#include <cstdarg>
#include "cstring"

static TIFF* openDummyTIFFFile(const char* mode) {
    FILE* file = fopen("./dummy_file", mode);
    if (file == nullptr) {
        return nullptr;
    }
    fclose(file);
    return TIFFOpen("./dummy_file", mode);
}

static void customErrorHandler(const char* module, const char* fmt, va_list ap) {
    vfprintf(stderr, fmt, ap);
}

static void customWarningHandler(const char* module, const char* fmt, va_list ap) {
    vfprintf(stderr, fmt, ap);
}

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t* Data, size_t Size) {
    if (Size < 1) return 0;

    TIFF* tiff = openDummyTIFFFile("r");
    if (!tiff) return 0;

    char emsg[1024];
    TIFFRGBAImageOK(tiff, emsg);

    TIFFErrorExt(nullptr, "module", "Error message: %s", "Sample error");
    TIFFWarningExtR(tiff, "module", "Warning message: %s", "Sample warning");

    TIFFErrorExtR(tiff, "module", "Error message R: %s", "Sample error R");

    TIFF* tiffExt = TIFFOpenExt("./dummy_file", "r", nullptr);
    if (tiffExt) {
        TIFFClose(tiffExt);
    }

    TIFFWriteCheck(tiff, 1, "WriteCheck");

    TIFFClose(tiff);
    return 0;
}