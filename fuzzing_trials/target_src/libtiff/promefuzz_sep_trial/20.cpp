// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFWriteDirectory at tif_dirwrite.c:238:5 in tiffio.h
// TIFFSetSubDirectory at tif_dir.c:2163:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetErrorHandler at tif_error.c:32:18 in tiffio.h
// TIFFWriteDirectory at tif_dirwrite.c:238:5 in tiffio.h
// TIFFSetErrorHandler at tif_error.c:32:18 in tiffio.h
// TIFFSetDirectory at tif_dir.c:2067:5 in tiffio.h
// TIFFCurrentDirOffset at tif_dir.c:2233:10 in tiffio.h
// TIFFSetDirectory at tif_dir.c:2067:5 in tiffio.h
// TIFFCurrentDirOffset at tif_dir.c:2233:10 in tiffio.h
// TIFFSetSubDirectory at tif_dir.c:2163:5 in tiffio.h
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
#include <cstdio>
#include <cstdint>
#include <cstdarg>
#include <tiffio.h>

static TIFFErrorHandler originalErrorHandler = nullptr;

static void dummyErrorHandler(const char* module, const char* fmt, va_list ap) {
    // Dummy error handler to suppress errors during fuzzing
}

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Ensure there's at least some data

    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    TIFF *tif = TIFFOpen("./dummy_file", "r+");
    if (!tif) return 0;

    TIFFWriteDirectory(tif);
    TIFFSetSubDirectory(tif, static_cast<uint64_t>(Data[0]));

    uint32_t tag = Data[0];
    TIFFSetField(tif, tag, Data[0]);

    originalErrorHandler = TIFFSetErrorHandler(dummyErrorHandler);
    TIFFWriteDirectory(tif);
    TIFFSetErrorHandler(originalErrorHandler);

    TIFFSetDirectory(tif, static_cast<tdir_t>(Data[0]));
    TIFFCurrentDirOffset(tif);

    TIFFSetDirectory(tif, static_cast<tdir_t>(Data[0]));
    TIFFCurrentDirOffset(tif);

    TIFFSetSubDirectory(tif, static_cast<uint64_t>(Data[0]));

    TIFFClose(tif);
    // Remove the second TIFFClose call to prevent double free

    return 0;
}