// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFSetSubDirectory at tif_dir.c:2163:5 in tiffio.h
// TIFFReadDirectory at tif_dirread.c:4323:5 in tiffio.h
// TIFFSetDirectory at tif_dir.c:2067:5 in tiffio.h
// TIFFSetSubDirectory at tif_dir.c:2163:5 in tiffio.h
// TIFFReadDirectory at tif_dirread.c:4323:5 in tiffio.h
// TIFFSetDirectory at tif_dir.c:2067:5 in tiffio.h
// TIFFReadDirectory at tif_dirread.c:4323:5 in tiffio.h
// TIFFCurrentDirectory at tif_open.c:874:8 in tiffio.h
// TIFFSetSubDirectory at tif_dir.c:2163:5 in tiffio.h
// TIFFNumberOfDirectories at tif_dir.c:2042:8 in tiffio.h
// TIFFCreateDirectory at tif_dir.c:1699:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFWriteDirectory at tif_dirwrite.c:238:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFCheckpointDirectory at tif_dirwrite.c:292:5 in tiffio.h
// TIFFWriteDirectory at tif_dirwrite.c:238:5 in tiffio.h
// TIFFCheckpointDirectory at tif_dirwrite.c:292:5 in tiffio.h
// TIFFWriteDirectory at tif_dirwrite.c:238:5 in tiffio.h
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
extern "C" {
#include <tiffio.h>
}

#include <cstdint>
#include <cstdarg>
#include <cstdio>

static void writeDummyFile(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    writeDummyFile(Data, Size);

    TIFF *tif = TIFFOpen("./dummy_file", "r+");
    if (!tif) return 0;

    uint32_t tag = 0;
    TIFFGetField(tif, tag);

    uint64_t subdirOffset = 0;
    TIFFSetSubDirectory(tif, subdirOffset);

    TIFFReadDirectory(tif);

    tdir_t dirn = 0;
    TIFFSetDirectory(tif, dirn);

    TIFFSetSubDirectory(tif, subdirOffset);

    TIFFReadDirectory(tif);

    TIFFSetDirectory(tif, dirn);

    TIFFReadDirectory(tif);

    TIFFCurrentDirectory(tif);

    TIFFSetSubDirectory(tif, subdirOffset);

    TIFFNumberOfDirectories(tif);

    TIFFCreateDirectory(tif);

    TIFFSetField(tif, tag);

    TIFFWriteDirectory(tif);

    TIFFSetField(tif, tag);

    TIFFCheckpointDirectory(tif);

    TIFFWriteDirectory(tif);

    TIFFCheckpointDirectory(tif);

    TIFFWriteDirectory(tif);

    TIFFClose(tif);

    return 0;
}