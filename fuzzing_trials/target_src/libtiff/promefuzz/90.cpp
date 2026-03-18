// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFReadEXIFDirectory at tif_dirread.c:5556:5 in tiffio.h
// TIFFScanlineSize at tif_strip.c:343:10 in tiffio.h
// TIFFIsBigTIFF at tif_open.c:912:5 in tiffio.h
// TIFFReadDirectory at tif_dirread.c:4323:5 in tiffio.h
// TIFFReadCustomDirectory at tif_dirread.c:5372:5 in tiffio.h
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
#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

static TIFF* openDummyTIFF(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return nullptr;

    fwrite(Data, 1, Size, file);
    fclose(file);

    return TIFFOpen("./dummy_file", "r");
}

extern "C" int LLVMFuzzerTestOneInput_90(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    TIFF *tif = openDummyTIFF(Data, Size);
    if (!tif) return 0;

    // 1. TIFFReadEXIFDirectory
    toff_t exifOffset = 0; // Example offset, adjust according to your needs
    TIFFReadEXIFDirectory(tif, exifOffset);

    // 2. TIFFReadScanline
    uint32_t row = 0; // Example row, adjust according to your needs
    uint16_t sample = 0; // Example sample, adjust according to your needs
    tsize_t scanlineSize = TIFFScanlineSize(tif);
    void *buf = malloc(scanlineSize);
    if (buf) {
        TIFFReadScanline(tif, buf, row, sample);
        free(buf);
    }

    // 3. TIFFIsBigTIFF
    TIFFIsBigTIFF(tif);

    // 4. TIFFReadDirectory
    TIFFReadDirectory(tif);

    // 5. TIFFReadCustomDirectory
    TIFFFieldArray *infoarray = nullptr; // Example, adjust according to your needs
    TIFFReadCustomDirectory(tif, exifOffset, infoarray);

    // 6. TIFFSetSubDirectory
    uint64_t subDirOffset = 0; // Example offset, adjust according to your needs
    TIFFSetSubDirectory(tif, subDirOffset);

    TIFFClose(tif);
    return 0;
}