// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFDefaultStripSize at tif_strip.c:218:10 in tiffio.h
// TIFFCurrentStrip at tif_open.c:879:10 in tiffio.h
// TIFFNumberOfStrips at tif_strip.c:65:10 in tiffio.h
// TIFFWriteEncodedStrip at tif_write.c:215:10 in tiffio.h
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
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <tiffio.h>

static TIFF* createDummyTIFF(const uint8_t* Data, size_t Size) {
    FILE* file = fopen("./dummy_file", "wb");
    if (!file) return nullptr;
    fwrite(Data, 1, Size, file);
    fclose(file);

    return TIFFOpen("./dummy_file", "r+");
}

extern "C" int LLVMFuzzerTestOneInput_138(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t)) return 0; // Ensure there's enough data for a uint32_t

    TIFF* tif = createDummyTIFF(Data, Size);
    if (!tif) return 0;

    // Fuzz TIFFDefaultStripSize
    uint32_t request = *reinterpret_cast<const uint32_t*>(Data);
    uint32_t defaultStripSize = TIFFDefaultStripSize(tif, request);

    // Fuzz TIFFCurrentStrip
    uint32_t currentStrip = TIFFCurrentStrip(tif);

    // Fuzz TIFFNumberOfStrips
    uint32_t numberOfStrips = TIFFNumberOfStrips(tif);

    // Fuzz TIFFWriteEncodedStrip
    if (Size > sizeof(uint32_t)) {
        uint32_t stripIndex = request % numberOfStrips;
        tmsize_t writeSize = TIFFWriteEncodedStrip(tif, stripIndex, (void*)(Data + sizeof(uint32_t)), Size - sizeof(uint32_t));
    }

    // Fuzz TIFFStripSize
    tmsize_t stripSize = TIFFStripSize(tif);

    // Fuzz TIFFReadEncodedStrip
    if (Size > sizeof(uint32_t)) {
        uint32_t stripIndex = request % numberOfStrips;
        void* buffer = malloc(stripSize);
        if (buffer) {
            tmsize_t readSize = TIFFReadEncodedStrip(tif, stripIndex, buffer, stripSize);
            free(buffer);
        }
    }

    TIFFClose(tif);
    return 0;
}