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

static TIFF* createDummyTIFF() {
    FILE* file = fopen("./dummy_file", "wb+");
    if (!file) return nullptr;

    TIFF* tiff = TIFFClientOpen("dummy", "w+", (thandle_t)file,
                                [](thandle_t fd, void* buf, tmsize_t size) -> tmsize_t { return fread(buf, 1, size, (FILE*)fd); },
                                [](thandle_t fd, void* buf, tmsize_t size) -> tmsize_t { return fwrite(buf, 1, size, (FILE*)fd); },
                                [](thandle_t fd, toff_t off, int whence) -> toff_t { return fseek((FILE*)fd, off, whence); },
                                [](thandle_t fd) -> int { return fclose((FILE*)fd); },
                                [](thandle_t fd) -> toff_t { fseek((FILE*)fd, 0, SEEK_END); return ftell((FILE*)fd); },
                                nullptr, nullptr);

    if (!tiff) fclose(file);
    return tiff;
}

extern "C" int LLVMFuzzerTestOneInput_68(const uint8_t* Data, size_t Size) {
    if (Size < sizeof(toff_t)) return 0;

    TIFF* tiff = createDummyTIFF();
    if (!tiff) return 0;

    // Fuzz TIFFCreateEXIFDirectory
    TIFFCreateEXIFDirectory(tiff);

    // Fuzz TIFFCreateGPSDirectory
    TIFFCreateGPSDirectory(tiff);

    // Fuzz TIFFReadEXIFDirectory
    toff_t exifOffset;
    memcpy(&exifOffset, Data, sizeof(toff_t));
    TIFFReadEXIFDirectory(tiff, exifOffset);

    // Fuzz TIFFGetVersion
    const char* version = TIFFGetVersion();
    (void)version;  // Suppress unused variable warning

    // Fuzz TIFFReadGPSDirectory
    toff_t gpsOffset;
    memcpy(&gpsOffset, Data, sizeof(toff_t));
    TIFFReadGPSDirectory(tiff, gpsOffset);

    TIFFClose(tiff);
    return 0;
}