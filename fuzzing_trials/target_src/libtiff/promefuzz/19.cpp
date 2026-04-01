// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFFindField at tif_dirinfo.c:878:18 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFScanlineSize at tif_strip.c:343:10 in tiffio.h
// TIFFWriteDirectory at tif_dirwrite.c:238:5 in tiffio.h
// TIFFCreateGPSDirectory at tif_dir.c:1752:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFWriteCustomDirectory at tif_dirwrite.c:303:5 in tiffio.h
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
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t) * 50) {
        return 0;
    }

    // Create a dummy TIFF file
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    TIFF *tif = TIFFOpen("./dummy_file", "r+");
    if (!tif) {
        return 0;
    }

    // Prepare variables for the fuzzing
    uint32_t tags[50];
    memcpy(tags, Data, sizeof(tags));

    // Invoke TIFFSetField multiple times
    for (int i = 0; i < 20; ++i) {
        TIFFSetField(tif, tags[i], tags[i + 1]);
    }

    // Use TIFFFindField
    const TIFFField *field = TIFFFindField(tif, tags[20], TIFF_NOTYPE);

    // Continue invoking TIFFSetField
    for (int i = 21; i < 30; ++i) {
        TIFFSetField(tif, tags[i], tags[i + 1]);
    }

    // Prepare a buffer for TIFFWriteScanline
    void *buf = malloc(TIFFScanlineSize(tif));
    if (buf) {
        TIFFWriteScanline(tif, buf, tags[30], 0);
        free(buf);
    }

    // Write the directory
    TIFFWriteDirectory(tif);

    // Create a GPS directory
    TIFFCreateGPSDirectory(tif);

    // Continue invoking TIFFSetField
    for (int i = 31; i < 40; ++i) {
        TIFFSetField(tif, tags[i], tags[i + 1]);
    }

    // Write a custom directory
    uint64_t offset;
    TIFFWriteCustomDirectory(tif, &offset);

    TIFFClose(tif);
    return 0;
}