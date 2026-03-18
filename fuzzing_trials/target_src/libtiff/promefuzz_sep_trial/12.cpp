// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFReadGPSDirectory at tif_dirread.c:5564:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFSetDirectory at tif_dir.c:2067:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFReadEXIFDirectory at tif_dirread.c:5556:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFFindField at tif_dirinfo.c:878:18 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
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
#include <cstdarg>

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        return 0;
    }

    fwrite(Data, 1, Size, file);
    fclose(file);

    TIFF *tif = TIFFOpen("./dummy_file", "r");
    if (!tif) {
        return 0;
    }

    uint32_t tag = 0;
    tdir_t dir = 0;
    toff_t offset = 0;
    TIFFDataType dataType = TIFF_NOTYPE;

    TIFFGetField(tif, tag, nullptr);
    TIFFGetField(tif, tag, nullptr);
    TIFFGetField(tif, tag, nullptr);
    TIFFGetField(tif, tag, nullptr);
    TIFFGetField(tif, tag, nullptr);
    TIFFGetField(tif, tag, nullptr);
    TIFFGetField(tif, tag, nullptr);
    TIFFGetField(tif, tag, nullptr);
    TIFFGetField(tif, tag, nullptr);
    TIFFGetField(tif, tag, nullptr);

    TIFFReadGPSDirectory(tif, offset);

    TIFFGetField(tif, tag, nullptr);
    TIFFGetField(tif, tag, nullptr);
    TIFFGetField(tif, tag, nullptr);
    TIFFGetField(tif, tag, nullptr);
    TIFFGetField(tif, tag, nullptr);
    TIFFGetField(tif, tag, nullptr);
    TIFFGetField(tif, tag, nullptr);
    TIFFGetField(tif, tag, nullptr);
    TIFFGetField(tif, tag, nullptr);
    TIFFGetField(tif, tag, nullptr);

    TIFFSetDirectory(tif, dir);

    TIFFGetField(tif, tag, nullptr);
    
    TIFFReadEXIFDirectory(tif, offset);

    TIFFGetField(tif, tag, nullptr);

    TIFFFindField(tif, tag, dataType);

    TIFFGetField(tif, tag, nullptr);
    TIFFGetField(tif, tag, nullptr);
    TIFFGetField(tif, tag, nullptr);
    TIFFGetField(tif, tag, nullptr);
    TIFFGetField(tif, tag, nullptr);
    TIFFGetField(tif, tag, nullptr);
    TIFFGetField(tif, tag, nullptr);
    TIFFGetField(tif, tag, nullptr);
    TIFFGetField(tif, tag, nullptr);
    TIFFGetField(tif, tag, nullptr);

    TIFFClose(tif);
    TIFFClose(tif);

    return 0;
}