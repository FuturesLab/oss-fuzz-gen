// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFWriteDirectory at tif_dirwrite.c:238:5 in tiffio.h
// TIFFCheckpointDirectory at tif_dirwrite.c:292:5 in tiffio.h
// TIFFGetTagListCount at tif_extension.c:34:5 in tiffio.h
// TIFFCreateDirectory at tif_dir.c:1699:5 in tiffio.h
// TIFFIsUpSampled at tif_open.c:894:5 in tiffio.h
// TIFFFreeDirectory at tif_dir.c:1629:6 in tiffio.h
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
#include <cstring>
#include <cstdio>

static TIFF* initializeDummyTIFF(const uint8_t *Data, size_t Size) {
    FILE* file = fopen("./dummy_file", "wb");
    if (!file) return nullptr;
    fwrite(Data, 1, Size, file);
    fclose(file);

    TIFF* tiff = TIFFOpen("./dummy_file", "r+");
    return tiff;
}

extern "C" int LLVMFuzzerTestOneInput_73(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    TIFF* tiff = initializeDummyTIFF(Data, Size);
    if (!tiff) return 0;

    // Fuzz TIFFWriteDirectory
    int writeDirResult = TIFFWriteDirectory(tiff);

    // Fuzz TIFFCheckpointDirectory
    int checkpointDirResult = TIFFCheckpointDirectory(tiff);

    // Fuzz TIFFGetTagListCount
    int tagListCount = TIFFGetTagListCount(tiff);

    // Fuzz TIFFCreateDirectory
    int createDirResult = TIFFCreateDirectory(tiff);

    // Fuzz TIFFIsUpSampled
    int isUpSampled = TIFFIsUpSampled(tiff);

    // Cleanup
    TIFFFreeDirectory(tiff);
    TIFFClose(tiff);

    return 0;
}