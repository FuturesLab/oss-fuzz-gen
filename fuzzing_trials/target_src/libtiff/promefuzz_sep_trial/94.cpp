// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFSetErrorHandlerExt at tif_error.c:39:21 in tiffio.h
// TIFFWriteCheck at tif_write.c:605:5 in tiffio.h
// TIFFWriteDirectory at tif_dirwrite.c:238:5 in tiffio.h
// TIFFMergeFieldInfo at tif_dirinfo.c:1238:5 in tiffio.h
// TIFFFlushData at tif_flush.c:146:5 in tiffio.h
// TIFFIsBigTIFF at tif_open.c:912:5 in tiffio.h
// TIFFSetErrorHandlerExt at tif_error.c:39:21 in tiffio.h
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
#include <tiffio.h>
#include <cstdarg>

static TIFF* initializeDummyTIFF(const uint8_t *Data, size_t Size) {
    FILE *file = std::fopen("./dummy_file", "wb");
    if (!file) return nullptr;
    std::fwrite(Data, 1, Size, file);
    std::fclose(file);

    TIFF *tif = TIFFOpen("./dummy_file", "r+");
    return tif;
}

static void customErrorHandler(thandle_t, const char *module, const char *fmt, va_list ap) {
    vfprintf(stderr, fmt, ap);
}

extern "C" int LLVMFuzzerTestOneInput_94(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    TIFF *tif = initializeDummyTIFF(Data, Size);
    if (!tif) return 0;

    TIFFErrorHandlerExt originalErrorHandler = TIFFSetErrorHandlerExt(customErrorHandler);

    // Test TIFFWriteCheck
    TIFFWriteCheck(tif, 1, "TestModule");

    // Test TIFFWriteDirectory
    TIFFWriteDirectory(tif);

    // Test TIFFMergeFieldInfo
    TIFFFieldInfo fieldInfo = {0, 0, 0, TIFF_NOTYPE, 0, 0, 0, nullptr};
    TIFFMergeFieldInfo(tif, &fieldInfo, 1);

    // Test TIFFFlushData
    TIFFFlushData(tif);

    // Test TIFFIsBigTIFF
    TIFFIsBigTIFF(tif);

    // Restore original error handler
    TIFFSetErrorHandlerExt(originalErrorHandler);

    TIFFClose(tif);
    return 0;
}