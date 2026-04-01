// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFWriteEncodedStrip at tif_write.c:215:10 in tiffio.h
// TIFFFlush at tif_flush.c:30:5 in tiffio.h
// TIFFGetVersion at tif_version.c:28:13 in tiffio.h
// TIFFCreateEXIFDirectory at tif_dir.c:1742:5 in tiffio.h
// TIFFCreateGPSDirectory at tif_dir.c:1752:5 in tiffio.h
// TIFFReadGPSDirectory at tif_dirread.c:5564:5 in tiffio.h
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

static TIFF* createDummyTIFF() {
    // Create a dummy TIFF file in memory
    TIFF* tif = TIFFOpen("./dummy_file", "w");
    if (!tif) {
        return nullptr;
    }

    // Set some basic fields to create a valid TIFF structure
    TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, 1);
    TIFFSetField(tif, TIFFTAG_IMAGELENGTH, 1);
    TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 1);
    TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);
    TIFFSetField(tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
    TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
    TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);

    // Write a single pixel to make it a valid TIFF
    uint8_t pixel = 0;
    TIFFWriteEncodedStrip(tif, 0, &pixel, 1);
    TIFFFlush(tif);

    return tif;
}

extern "C" int LLVMFuzzerTestOneInput_117(const uint8_t *Data, size_t Size) {
    // Prepare the environment
    TIFF* tif = createDummyTIFF();
    if (!tif) {
        return 0;
    }

    // Test TIFFGetVersion
    const char* version = TIFFGetVersion();
    if (version) {
        // Ensure version string is not empty
        if (strlen(version) == 0) {
            fprintf(stderr, "TIFFGetVersion returned an empty string.\n");
            abort();
        }
    }

    // Test TIFFCreateEXIFDirectory
    TIFFCreateEXIFDirectory(tif);

    // Test TIFFCreateGPSDirectory
    TIFFCreateGPSDirectory(tif);

    // Calculate a directory offset within the size of the data
    toff_t diroff = (Size > sizeof(toff_t)) ? *(reinterpret_cast<const toff_t*>(Data)) : 0;

    // Test TIFFReadGPSDirectory
    TIFFReadGPSDirectory(tif, diroff);

    // Test TIFFReadEXIFDirectory
    TIFFReadEXIFDirectory(tif, diroff);

    // Test TIFFFreeDirectory
    TIFFFreeDirectory(tif);

    // Cleanup
    TIFFClose(tif);

    return 0;
}