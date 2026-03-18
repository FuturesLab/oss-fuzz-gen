// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFWriteDirectory at tif_dirwrite.c:238:5 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFRewriteDirectory at tif_dirwrite.c:483:5 in tiffio.h
// TIFFCreateDirectory at tif_dir.c:1699:5 in tiffio.h
// TIFFWriteDirectory at tif_dirwrite.c:238:5 in tiffio.h
// TIFFNumberOfDirectories at tif_dir.c:2042:8 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFSetSubDirectory at tif_dir.c:2163:5 in tiffio.h
// TIFFWriteDirectory at tif_dirwrite.c:238:5 in tiffio.h
// TIFFNumberOfDirectories at tif_dir.c:2042:8 in tiffio.h
// TIFFUnlinkDirectory at tif_dir.c:2247:5 in tiffio.h
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

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Write input data to a dummy file
    const char *filename = "./dummy_file.tiff";
    FILE *file = fopen(filename, "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    TIFF *tif = nullptr;
    TIFF *tif2 = nullptr;
    tdir_t dirCount = 0;

    // Open TIFF file for writing
    tif = TIFFOpen(filename, "w");
    if (tif) {
        // Write directory
        TIFFWriteDirectory(tif);
        TIFFClose(tif);
    }

    // Reopen TIFF file for reading and rewriting
    tif = TIFFOpen(filename, "r+");
    if (tif) {
        TIFFRewriteDirectory(tif);
        TIFFCreateDirectory(tif);
        TIFFWriteDirectory(tif);
        dirCount = TIFFNumberOfDirectories(tif);
        TIFFClose(tif);
    }

    // Reopen TIFF file for subdirectory operations
    tif2 = TIFFOpen(filename, "r+");
    if (tif2) {
        if (dirCount > 0) {
            TIFFSetSubDirectory(tif2, 0);
        }
        TIFFWriteDirectory(tif2);
        dirCount = TIFFNumberOfDirectories(tif2);
        if (dirCount > 0) {
            TIFFUnlinkDirectory(tif2, 0);
        }
        TIFFClose(tif2);
    }

    // Final close
    if (tif) {
        TIFFClose(tif);
    }

    return 0;
}