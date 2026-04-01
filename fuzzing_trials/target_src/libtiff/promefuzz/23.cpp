// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// _TIFFmemcmp at tif_unix.c:360:5 in tiffio.h
// _TIFFmemcmp at tif_unix.c:360:5 in tiffio.h
// _TIFFmemcmp at tif_unix.c:360:5 in tiffio.h
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
#include <cstddef>
#include <cstdio>
#include <cstring>

static const char *dummyFileName = "./dummy_file";
static const char *dummyMode = "r";

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    // Step 1: Prepare environment
    FILE *file = fopen(dummyFileName, "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    TIFF *tif = TIFFOpen(dummyFileName, dummyMode);
    if (!tif) return 0;

    // Step 2: Invoke TIFFGetField
    uint32_t tag = 0;
    int status = TIFFGetField(tif, tag, nullptr);

    // Step 3: Use _TIFFmemcmp
    if (Size > 1) {
        _TIFFmemcmp(Data, Data + 1, Size - 1);
    }
    if (Size > 2) {
        _TIFFmemcmp(Data, Data + 2, Size - 2);
    }
    if (Size > 3) {
        _TIFFmemcmp(Data, Data + 3, Size - 3);
    }

    // Step 4: Clean up
    TIFFClose(tif);

    return 0;
}