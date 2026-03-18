// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFCreateEXIFDirectory at tif_dir.c:1742:5 in tiffio.h
// TIFFCreateGPSDirectory at tif_dir.c:1752:5 in tiffio.h
// TIFFReadEXIFDirectory at tif_dirread.c:5556:5 in tiffio.h
// TIFFReadGPSDirectory at tif_dirread.c:5564:5 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
#include <iostream>
#include <tiffio.h>

static TIFF* createDummyTIFF() {
    FILE* file = fopen("./dummy_file", "wb+");
    if (!file) return nullptr;
    fclose(file);

    TIFF* tif = TIFFOpen("./dummy_file", "r+");
    return tif;
}

extern "C" int LLVMFuzzerTestOneInput_47(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(toff_t)) return 0;

    TIFF* tif = createDummyTIFF();
    if (!tif) return 0;

    // Fuzz TIFFCreateEXIFDirectory
    TIFFCreateEXIFDirectory(tif);

    // Fuzz TIFFCreateCustomDirectory
    // Since we don't have a complete definition for TIFFFieldArray, we skip this

    // Fuzz TIFFCreateGPSDirectory
    TIFFCreateGPSDirectory(tif);

    // Fuzz TIFFReadEXIFDirectory
    toff_t diroff = *reinterpret_cast<const toff_t*>(Data);
    TIFFReadEXIFDirectory(tif, diroff);

    // Fuzz TIFFReadCustomDirectory
    // Since we don't have a complete definition for TIFFFieldArray, we skip this

    // Fuzz TIFFReadGPSDirectory
    TIFFReadGPSDirectory(tif, diroff);

    TIFFClose(tif);
    return 0;
}