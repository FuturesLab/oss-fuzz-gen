// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFCreateEXIFDirectory at tif_dir.c:1742:5 in tiffio.h
// TIFFAccessTagMethods at tif_extension.c:58:17 in tiffio.h
// TIFFReadEXIFDirectory at tif_dirread.c:5556:5 in tiffio.h
// TIFFReadDirectory at tif_dirread.c:4323:5 in tiffio.h
// TIFFReadCustomDirectory at tif_dirread.c:5372:5 in tiffio.h
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

static TIFF* initializeTIFF(const uint8_t *Data, size_t Size) {
    // Write data to a dummy file
    FILE *file = std::fopen("./dummy_file", "wb");
    if (!file) return nullptr;
    std::fwrite(Data, 1, Size, file);
    std::fclose(file);

    // Open the TIFF file
    TIFF *tif = TIFFOpen("./dummy_file", "r+");
    return tif;
}

extern "C" int LLVMFuzzerTestOneInput_143(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0; // Not enough data
    }

    TIFF *tif = initializeTIFF(Data, Size);
    if (!tif) {
        return 0;
    }

    // Test TIFFCreateEXIFDirectory
    TIFFCreateEXIFDirectory(tif);

    // Test TIFFAccessTagMethods
    TIFFTagMethods *tagMethods = TIFFAccessTagMethods(tif);

    // Test TIFFReadEXIFDirectory
    if (Size >= sizeof(toff_t)) {
        toff_t offset;
        std::memcpy(&offset, Data, sizeof(toff_t));
        TIFFReadEXIFDirectory(tif, offset);
    }

    // Test TIFFReadDirectory
    TIFFReadDirectory(tif);

    // Test TIFFReadCustomDirectory
    if (Size >= sizeof(toff_t)) {
        toff_t customOffset;
        std::memcpy(&customOffset, Data, sizeof(toff_t));
        TIFFReadCustomDirectory(tif, customOffset, nullptr);
    }

    // Clean up
    TIFFFreeDirectory(tif);
    TIFFClose(tif);

    return 0;
}