// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClientOpen at tif_open.c:289:7 in tiffio.h
// TIFFCreateEXIFDirectory at tif_dir.c:1742:5 in tiffio.h
// TIFFCreateGPSDirectory at tif_dir.c:1752:5 in tiffio.h
// TIFFReadEXIFDirectory at tif_dirread.c:5556:5 in tiffio.h
// TIFFGetVersion at tif_version.c:28:13 in tiffio.h
// TIFFReadGPSDirectory at tif_dirread.c:5564:5 in tiffio.h
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
#include <cstring>

static TIFF* initializeTIFF() {
    FILE* file = fopen("./dummy_file", "wb+");
    if (!file) return nullptr;
    TIFF* tiff = TIFFClientOpen("dummy", "w+", file,
                                [](thandle_t fd, void* buf, tmsize_t size) -> tmsize_t { return fread(buf, 1, size, static_cast<FILE*>(fd)); },
                                [](thandle_t fd, void* buf, tmsize_t size) -> tmsize_t { return fwrite(buf, 1, size, static_cast<FILE*>(fd)); },
                                [](thandle_t fd, toff_t off, int whence) -> toff_t { return fseeko(static_cast<FILE*>(fd), off, whence); },
                                [](thandle_t fd) -> int { return fclose(static_cast<FILE*>(fd)); },
                                [](thandle_t fd) -> toff_t { fseeko(static_cast<FILE*>(fd), 0, SEEK_END); return ftello(static_cast<FILE*>(fd)); },
                                nullptr, nullptr);
    return tiff;
}

extern "C" int LLVMFuzzerTestOneInput_87(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(toff_t)) return 0;

    TIFF* tiff = initializeTIFF();
    if (!tiff) return 0;

    // Fuzz TIFFCreateEXIFDirectory
    TIFFCreateEXIFDirectory(tiff);

    // Fuzz TIFFCreateCustomDirectory
    // Since we can't instantiate TIFFFieldArray directly due to incomplete type, we skip this part

    // Fuzz TIFFCreateGPSDirectory
    TIFFCreateGPSDirectory(tiff);

    // Fuzz TIFFReadEXIFDirectory
    toff_t exifOffset = *reinterpret_cast<const toff_t*>(Data);
    TIFFReadEXIFDirectory(tiff, exifOffset);

    // Fuzz TIFFGetVersion
    const char* version = TIFFGetVersion();
    if (version) {
        // Simulate use of version string
        printf("TIFF Version: %s\n", version);
    }

    // Fuzz TIFFReadGPSDirectory
    toff_t gpsOffset = *reinterpret_cast<const toff_t*>(Data + sizeof(toff_t));
    TIFFReadGPSDirectory(tiff, gpsOffset);

    // Cleanup
    TIFFClose(tiff);

    return 0;
}