// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFFreeDirectory at tif_dir.c:1629:6 in tiffio.h
// TIFFCreateEXIFDirectory at tif_dir.c:1742:5 in tiffio.h
// TIFFReadGPSDirectory at tif_dirread.c:5564:5 in tiffio.h
// TIFFGetCloseProc at tif_open.c:932:15 in tiffio.h
// TIFFCreateGPSDirectory at tif_dir.c:1752:5 in tiffio.h
// TIFFReadEXIFDirectory at tif_dirread.c:5556:5 in tiffio.h
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

extern "C" int LLVMFuzzerTestOneInput_86(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(toff_t)) {
        return 0;
    }

    TIFF *tif = TIFFOpen("./dummy_file", "w+");
    if (!tif) {
        return 0;
    }

    // Prepare a dummy file with the input data
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }

    // 1. Test TIFFFreeDirectory
    TIFFFreeDirectory(tif);

    // 2. Test TIFFCreateEXIFDirectory
    TIFFCreateEXIFDirectory(tif);

    // 3. Test TIFFReadGPSDirectory
    toff_t diroff = *reinterpret_cast<const toff_t *>(Data);
    TIFFReadGPSDirectory(tif, diroff);

    // 4. Test TIFFGetCloseProc
    TIFFCloseProc closeProc = TIFFGetCloseProc(tif);

    // 5. Test TIFFCreateGPSDirectory
    TIFFCreateGPSDirectory(tif);

    // 6. Test TIFFReadEXIFDirectory
    TIFFReadEXIFDirectory(tif, diroff);

    // Clean up
    TIFFClose(tif);
    return 0;
}