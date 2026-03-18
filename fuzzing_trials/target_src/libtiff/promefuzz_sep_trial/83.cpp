// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFAccessTagMethods at tif_extension.c:58:17 in tiffio.h
// TIFFFreeDirectory at tif_dir.c:1629:6 in tiffio.h
// TIFFCreateEXIFDirectory at tif_dir.c:1742:5 in tiffio.h
// TIFFReadDirectory at tif_dirread.c:4323:5 in tiffio.h
// TIFFCreateGPSDirectory at tif_dir.c:1752:5 in tiffio.h
// TIFFReadEXIFDirectory at tif_dirread.c:5556:5 in tiffio.h
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
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <tiffio.h>

static TIFF *createDummyTIFF(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return nullptr;
    fwrite(Data, 1, Size, file);
    fclose(file);

    TIFF *tif = TIFFOpen("./dummy_file", "r");
    return tif;
}

extern "C" int LLVMFuzzerTestOneInput_83(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint64_t)) return 0;

    TIFF *tif = createDummyTIFF(Data, Size);
    if (!tif) return 0;

    // Test TIFFAccessTagMethods
    TIFFTagMethods *tagMethods = TIFFAccessTagMethods(tif);

    // Test TIFFFreeDirectory
    TIFFFreeDirectory(tif);

    // Test TIFFCreateEXIFDirectory
    int exifDirResult = TIFFCreateEXIFDirectory(tif);

    // Test TIFFReadDirectory
    int readDirResult = TIFFReadDirectory(tif);

    // Test TIFFCreateGPSDirectory
    int gpsDirResult = TIFFCreateGPSDirectory(tif);

    // Test TIFFReadEXIFDirectory
    toff_t exifOffset = *reinterpret_cast<const toff_t*>(Data);
    int readExifResult = TIFFReadEXIFDirectory(tif, exifOffset);

    // Clean up
    TIFFClose(tif);

    return 0;
}