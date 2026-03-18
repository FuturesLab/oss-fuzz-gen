// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpenExt at tif_unix.c:237:7 in tiffio.h
// TIFFErrorExtR at tif_error.c:107:6 in tiffio.h
// TIFFMergeFieldInfo at tif_dirinfo.c:1238:5 in tiffio.h
// TIFFFlushData at tif_flush.c:146:5 in tiffio.h
// TIFFIsBigTIFF at tif_open.c:912:5 in tiffio.h
// TIFFErrorExtR at tif_error.c:107:6 in tiffio.h
// TIFFWriteCheck at tif_write.c:605:5 in tiffio.h
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
#include <cstdarg>
#include <cstring>
#include <tiffio.h>

static TIFF *openDummyTIFF() {
    TIFF *tif = TIFFOpenExt("./dummy_file", "w", nullptr);
    if (!tif) {
        TIFFErrorExtR(nullptr, "openDummyTIFF", "Failed to open dummy TIFF file.");
    }
    return tif;
}

static void writeDummyDataToFile(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

extern "C" int LLVMFuzzerTestOneInput_57(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(TIFFFieldInfo)) {
        return 0;
    }

    writeDummyDataToFile(Data, Size);

    TIFF *tif = openDummyTIFF();
    if (!tif) {
        return 0;
    }

    TIFFFieldInfo fieldInfo;
    memcpy(&fieldInfo, Data, sizeof(TIFFFieldInfo));

    // Test TIFFMergeFieldInfo
    TIFFMergeFieldInfo(tif, &fieldInfo, 1);

    // Test TIFFFlushData
    TIFFFlushData(tif);

    // Test TIFFIsBigTIFF
    TIFFIsBigTIFF(tif);

    // Test TIFFErrorExtR
    TIFFErrorExtR(tif, "Module", "Test error with value: %d", fieldInfo.field_tag);

    // Test TIFFWriteCheck
    TIFFWriteCheck(tif, 1, "TestWriteCheck");

    TIFFClose(tif);
    return 0;
}