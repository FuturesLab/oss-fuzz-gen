// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFFdOpen at tif_unix.c:209:7 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
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
#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_136(const uint8_t *Data, size_t Size) {
    // Create a dummy file to act as a TIFF source
    FILE* dummyFile = fopen("./dummy_file", "wb+");
    if (!dummyFile) {
        return 0; // Failed to create a dummy file
    }
    fwrite(Data, 1, Size, dummyFile);
    rewind(dummyFile);

    // Open the dummy file as a TIFF file
    TIFF* tif = TIFFFdOpen(fileno(dummyFile), "./dummy_file", "r+");
    if (!tif) {
        fclose(dummyFile);
        return 0; // Failed to open TIFF
    }

    // Prepare a buffer for reading/writing strips
    void* buffer = malloc(Size);
    if (!buffer) {
        TIFFClose(tif);
        fclose(dummyFile);
        return 0; // Failed to allocate buffer
    }
    memcpy(buffer, Data, Size);

    // Fuzz TIFFDefaultStripSize
    uint32_t stripSize = TIFFDefaultStripSize(tif, static_cast<uint32_t>(Size));

    // Fuzz TIFFCurrentStrip
    uint32_t currentStrip = TIFFCurrentStrip(tif);

    // Fuzz TIFFNumberOfStrips
    uint32_t numberOfStrips = TIFFNumberOfStrips(tif);

    // Fuzz TIFFWriteEncodedStrip
    tmsize_t writeResult = TIFFWriteEncodedStrip(tif, currentStrip, buffer, static_cast<tmsize_t>(Size));

    // Fuzz TIFFStripSize
    tmsize_t stripSizeResult = TIFFStripSize(tif);

    // Fuzz TIFFReadEncodedStrip
    tmsize_t readResult = TIFFReadEncodedStrip(tif, currentStrip, buffer, static_cast<tmsize_t>(Size));

    // Cleanup
    free(buffer);
    TIFFClose(tif);
    fclose(dummyFile);

    return 0;
}