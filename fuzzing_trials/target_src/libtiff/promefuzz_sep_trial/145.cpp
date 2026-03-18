// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFRGBAImageOK at tif_getimage.c:83:5 in tiffio.h
// TIFFErrorExt at tif_error.c:63:6 in tiffio.h
// TIFFWriteCheck at tif_write.c:605:5 in tiffio.h
// TIFFErrorExtR at tif_error.c:107:6 in tiffio.h
// TIFFWarningExtR at tif_warning.c:80:6 in tiffio.h
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
#include <cstdint>
#include <cstdio>
#include <cstdarg>
#include <cstring>

static TIFF* openDummyFile() {
    FILE* file = fopen("./dummy_file", "wb");
    if (!file) return nullptr;

    const char dummyData[] = "DUMMY_TIFF_DATA";
    fwrite(dummyData, 1, sizeof(dummyData), file);
    fclose(file);

    return TIFFOpen("./dummy_file", "r");
}

static void customErrorHandler(thandle_t handle, const char* module, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}

extern "C" int LLVMFuzzerTestOneInput_145(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    TIFF* tiff = openDummyFile();
    if (!tiff) return 0;

    char emsg[1024] = {0};
    TIFFRGBAImageOK(tiff, emsg);

    TIFFErrorExt(0, "Module", "Test Error: %s", emsg);

    TIFFWriteCheck(tiff, 1, "WriteCheckModule");

    TIFFErrorExtR(tiff, "ModuleR", "Test Error R: %s", emsg);

    TIFFWarningExtR(tiff, "WarningModuleR", "Test Warning R: %s", emsg);

    TIFFClose(tiff);
    return 0;
}