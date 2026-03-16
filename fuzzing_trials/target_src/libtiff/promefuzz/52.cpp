// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFWriteEncodedStrip at tif_write.c:215:10 in tiffio.h
// TIFFNumberOfStrips at tif_strip.c:65:10 in tiffio.h
// TIFFSwabArrayOfLong at tif_swab.c:117:6 in tiffio.h
// TIFFStripSize at tif_strip.c:204:10 in tiffio.h
// TIFFReadEncodedStrip at tif_read.c:543:10 in tiffio.h
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
#include <cstring>
#include <cstdio>
#include <cstdlib>

static void createDummyFile(const uint8_t *data, size_t size) {
    FILE *file = std::fopen("./dummy_file", "wb");
    if (file) {
        std::fwrite(data, 1, size, file);
        std::fclose(file);
    }
}

static TIFF* openDummyTIFF() {
    return TIFFOpen("./dummy_file", "r+");
}

extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    createDummyFile(Data, Size);

    TIFF *tif = openDummyTIFF();
    if (!tif) return 0;

    // Fuzz TIFFWriteEncodedStrip
    uint32_t strip = 0;
    tmsize_t writeSize = (Size > 4) ? *(reinterpret_cast<const tmsize_t*>(Data)) : 1;
    TIFFWriteEncodedStrip(tif, strip, const_cast<uint8_t*>(Data), writeSize);

    // Fuzz TIFFNumberOfStrips
    TIFFNumberOfStrips(tif);

    // Fuzz TIFFSwabArrayOfLong
    if (Size >= sizeof(uint32_t)) {
        uint32_t *array = new uint32_t[Size / sizeof(uint32_t)];
        std::memcpy(array, Data, Size);
        TIFFSwabArrayOfLong(array, Size / sizeof(uint32_t));
        delete[] array;
    }

    // Fuzz TIFFStripSize
    TIFFStripSize(tif);

    // Fuzz TIFFReadScanline
    if (Size >= 4) {
        void *buf = std::malloc(Size);
        uint32_t row = *(reinterpret_cast<const uint32_t*>(Data));
        TIFFReadScanline(tif, buf, row, 0);
        std::free(buf);
    }

    // Fuzz TIFFReadEncodedStrip
    if (Size >= 4) {
        void *buf = std::malloc(Size);
        TIFFReadEncodedStrip(tif, strip, buf, Size);
        std::free(buf);
    }

    TIFFClose(tif);
    return 0;
}