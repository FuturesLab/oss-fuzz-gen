// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpenOptionsAlloc at tif_open.c:80:18 in tiffio.h
// TIFFOpenOptionsSetErrorHandlerExtR at tif_open.c:121:6 in tiffio.h
// TIFFOpenOptionsSetWarningHandlerExtR at tif_open.c:129:6 in tiffio.h
// TIFFOpenExt at tif_unix.c:237:7 in tiffio.h
// TIFFErrorExtR at tif_error.c:107:6 in tiffio.h
// TIFFWarningExtR at tif_warning.c:80:6 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFOpenOptionsFree at tif_open.c:87:6 in tiffio.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <tiffio.h>
#include <cstdarg>
#include <cstdio>
#include <cstring>

static int CustomErrorHandler(TIFF*, void*, const char* module, const char* fmt, va_list ap) {
    if (module) {
        fprintf(stderr, "%s: ", module);
    }
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    return 0;
}

static int CustomWarningHandler(TIFF*, void*, const char* module, const char* fmt, va_list ap) {
    if (module) {
        fprintf(stderr, "%s: ", module);
    }
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    return 0;
}

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Prepare dummy file
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    TIFFOpenOptions *opts = TIFFOpenOptionsAlloc();
    if (!opts) {
        return 0;
    }

    TIFFOpenOptionsSetErrorHandlerExtR(opts, CustomErrorHandler, nullptr);
    TIFFOpenOptionsSetWarningHandlerExtR(opts, CustomWarningHandler, nullptr);

    TIFF *tif = TIFFOpenExt("./dummy_file", "r", opts);
    if (tif) {
        TIFFErrorExtR(tif, "CustomModule", "This is a test error: %s", "Error details");
        TIFFWarningExtR(tif, "CustomModule", "This is a test warning: %s", "Warning details");
        TIFFClose(tif);
    }

    TIFFOpenOptionsFree(opts);

    return 0;
}