// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFSetDirectory at tif_dir.c:2067:5 in tiffio.h
// TIFFSetDirectory at tif_dir.c:2067:5 in tiffio.h
// TIFFCurrentDirOffset at tif_dir.c:2233:10 in tiffio.h
// TIFFGetSeekProc at tif_open.c:927:14 in tiffio.h
// TIFFIsByteSwapped at tif_open.c:889:5 in tiffio.h
// TIFFSwabLong at tif_swab.c:45:6 in tiffio.h
// TIFFGetWriteProc at tif_open.c:922:19 in tiffio.h
// TIFFNumberOfDirectories at tif_dir.c:2042:8 in tiffio.h
// TIFFSetDirectory at tif_dir.c:2067:5 in tiffio.h
// TIFFSetDirectory at tif_dir.c:2067:5 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
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

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(tdir_t) + sizeof(uint32_t)) {
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

    // Extract directory numbers and a sample uint32_t from input data
    tdir_t dir1 = *reinterpret_cast<const tdir_t*>(Data);
    tdir_t dir2 = *reinterpret_cast<const tdir_t*>(Data + sizeof(tdir_t));
    uint32_t sampleLong = *reinterpret_cast<const uint32_t*>(Data + sizeof(tdir_t) * 2);

    // Invoke TIFFSetDirectory
    TIFFSetDirectory(tif, dir1);
    TIFFSetDirectory(tif, dir2);

    // Invoke TIFFCurrentDirOffset
    uint64_t dirOffset = TIFFCurrentDirOffset(tif);

    // Invoke TIFFGetSeekProc
    TIFFSeekProc seekProc = TIFFGetSeekProc(tif);

    // Invoke TIFFIsByteSwapped
    int isByteSwapped = TIFFIsByteSwapped(tif);

    // Invoke TIFFSwabLong
    TIFFSwabLong(&sampleLong);

    // Invoke TIFFGetWriteProc
    TIFFReadWriteProc writeProc = TIFFGetWriteProc(tif);

    // Invoke TIFFNumberOfDirectories
    tdir_t numDirs = TIFFNumberOfDirectories(tif);

    // Invoke TIFFSetDirectory again
    TIFFSetDirectory(tif, dir1);
    TIFFSetDirectory(tif, dir2);

    // Close the TIFF file
    TIFFClose(tif);
    TIFFClose(tif); // Close again to test double close handling

    return 0;
}