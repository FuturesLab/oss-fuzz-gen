// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFCheckpointDirectory at tif_dirwrite.c:292:5 in tiffio.h
// TIFFCreateDirectory at tif_dir.c:1699:5 in tiffio.h
// TIFFWriteDirectory at tif_dirwrite.c:238:5 in tiffio.h
// TIFFFreeDirectory at tif_dir.c:1629:6 in tiffio.h
// TIFFSetDirectory at tif_dir.c:2067:5 in tiffio.h
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
#include <cstdlib>
#include <cstring>

static TIFF* initializeTIFF(const char* filename, const char* mode) {
    TIFF* tif = TIFFOpen(filename, mode);
    if (!tif) {
        fprintf(stderr, "Could not open file %s\n", filename);
        return nullptr;
    }
    return tif;
}

static void performCleanup(TIFF* tif) {
    if (tif) {
        TIFFClose(tif);
    }
}

extern "C" int LLVMFuzzerTestOneInput_129(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file with the input data
    FILE* file = fopen("./dummy_file", "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    TIFF* tif = initializeTIFF("./dummy_file", "r+b");
    if (!tif) return 0;

    // Fuzzing TIFFCheckpointDirectory
    TIFFCheckpointDirectory(tif);

    // Fuzzing TIFFCreateDirectory
    TIFFCreateDirectory(tif);

    // Fuzzing TIFFWriteDirectory
    TIFFWriteDirectory(tif);

    // Fuzzing TIFFFreeDirectory
    TIFFFreeDirectory(tif);

    // Fuzzing TIFFSetDirectory with a random directory number
    tdir_t dirNum = static_cast<tdir_t>(Data[0]); // Use the first byte for directory number
    TIFFSetDirectory(tif, dirNum);

    // Cleanup
    performCleanup(tif);
    return 0;
}