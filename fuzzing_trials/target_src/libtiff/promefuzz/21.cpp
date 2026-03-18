// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFWriteDirectory at tif_dirwrite.c:238:5 in tiffio.h
// TIFFSetDirectory at tif_dir.c:2067:5 in tiffio.h
// TIFFCurrentDirOffset at tif_dir.c:2233:10 in tiffio.h
// TIFFSetDirectory at tif_dir.c:2067:5 in tiffio.h
// TIFFForceStrileArrayWriting at tif_flush.c:76:5 in tiffio.h
// TIFFFlushData at tif_flush.c:146:5 in tiffio.h
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
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy TIFF file
    FILE *file = fopen("./dummy_file", "wb+");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    TIFF *tif = TIFFOpen("./dummy_file", "r+");
    if (!tif) return 0;

    // 1. TIFFWriteDirectory
    if (TIFFWriteDirectory(tif)) {
        // 2. TIFFSetDirectory
        TIFFSetDirectory(tif, 0);

        // 3. TIFFCurrentDirOffset
        TIFFCurrentDirOffset(tif);

        // 4. TIFFSetDirectory
        TIFFSetDirectory(tif, 0);

        // 5. TIFFForceStrileArrayWriting
        TIFFForceStrileArrayWriting(tif);

        // 6. TIFFFlushData
        TIFFFlushData(tif);
    }

    TIFFClose(tif);
    return 0;
}