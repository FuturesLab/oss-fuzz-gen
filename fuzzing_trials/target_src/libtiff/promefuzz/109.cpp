// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFCreateEXIFDirectory at tif_dir.c:1742:5 in tiffio.h
// TIFFFileName at tif_open.c:803:13 in tiffio.h
// TIFFGetCloseProc at tif_open.c:932:15 in tiffio.h
// TIFFCreateGPSDirectory at tif_dir.c:1752:5 in tiffio.h
// TIFFReadEXIFDirectory at tif_dirread.c:5556:5 in tiffio.h
// TIFFFreeDirectory at tif_dir.c:1629:6 in tiffio.h
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
#include <cstdlib>
#include <cstring>

static TIFF* createDummyTIFF(const char* filename) {
    TIFF* tiff = TIFFOpen(filename, "w");
    if (!tiff) {
        fprintf(stderr, "Failed to open TIFF file for writing.\n");
        return nullptr;
    }
    return tiff;
}

extern "C" int LLVMFuzzerTestOneInput_109(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint64_t)) {
        return 0;
    }

    // Write dummy data to a file to simulate a TIFF file
    const char* dummyFilename = "./dummy_file";
    FILE* file = fopen(dummyFilename, "wb");
    if (!file) {
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the dummy TIFF file
    TIFF* tiff = createDummyTIFF(dummyFilename);
    if (!tiff) {
        return 0;
    }

    // Call TIFFCreateEXIFDirectory
    TIFFCreateEXIFDirectory(tiff);

    // Call TIFFFileName
    const char* filename = TIFFFileName(tiff);
    if (filename) {
        printf("TIFF file name: %s\n", filename);
    }

    // Call TIFFGetCloseProc
    TIFFCloseProc closeProc = TIFFGetCloseProc(tiff);
    if (closeProc) {
        printf("TIFF close procedure is set.\n");
    }

    // Call TIFFCreateGPSDirectory
    TIFFCreateGPSDirectory(tiff);

    // Use the first 8 bytes of Data as the offset for TIFFReadEXIFDirectory
    toff_t offset = *((const uint64_t*)Data);
    TIFFReadEXIFDirectory(tiff, offset);

    // Clean up
    TIFFFreeDirectory(tiff);
    TIFFClose(tiff);

    return 0;
}