// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFCurrentDirOffset at tif_dir.c:2233:10 in tiffio.h
// TIFFSetDirectory at tif_dir.c:2067:5 in tiffio.h
// TIFFCurrentDirOffset at tif_dir.c:2233:10 in tiffio.h
// TIFFReadDirectory at tif_dirread.c:4323:5 in tiffio.h
// TIFFCurrentDirOffset at tif_dir.c:2233:10 in tiffio.h
// TIFFSetDirectory at tif_dir.c:2067:5 in tiffio.h
// TIFFSetDirectory at tif_dir.c:2067:5 in tiffio.h
// TIFFSetDirectory at tif_dir.c:2067:5 in tiffio.h
// TIFFSetSubDirectory at tif_dir.c:2163:5 in tiffio.h
// TIFFSetSubDirectory at tif_dir.c:2163:5 in tiffio.h
// TIFFSetSubDirectory at tif_dir.c:2163:5 in tiffio.h
// TIFFSetSubDirectory at tif_dir.c:2163:5 in tiffio.h
// TIFFIsBigEndian at tif_open.c:904:5 in tiffio.h
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

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy TIFF file
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tif = TIFFOpen("./dummy_file", "r");
    if (!tif) return 0;

    // Fuzzing the sequence of API calls
    uint64_t offset = TIFFCurrentDirOffset(tif);
    TIFFSetDirectory(tif, static_cast<tdir_t>(Data[0] % 256));
    offset = TIFFCurrentDirOffset(tif);
    TIFFReadDirectory(tif);
    offset = TIFFCurrentDirOffset(tif);
    TIFFSetDirectory(tif, static_cast<tdir_t>(Data[0] % 256));
    TIFFSetDirectory(tif, static_cast<tdir_t>((Data[0] + 1) % 256));
    TIFFSetDirectory(tif, static_cast<tdir_t>((Data[0] + 2) % 256));
    TIFFSetSubDirectory(tif, offset);
    TIFFSetSubDirectory(tif, offset + 1);
    TIFFSetSubDirectory(tif, offset + 2);
    TIFFSetSubDirectory(tif, offset + 3);
    int isBigEndian = TIFFIsBigEndian(tif);

    // Cleanup
    TIFFClose(tif);
    return 0;
}