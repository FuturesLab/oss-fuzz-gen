#include <iostream>
#include "sstream"
#include <string>
#include <vector>
#include "cstring"
#include "cstdlib"
#include <cstdio>
#include "cstdint"
#include <cstddef>
#include "tiffio.h"
#include "cstdint"
#include <cstdio>
#include "cstdlib"
#include "cstring"

extern "C" int LLVMFuzzerTestOneInput_72(const uint8_t *Data, size_t Size) {
    // Write input data to a dummy file
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        return 0;
    }

    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the dummy file with libtiff
    TIFF *tifFile = TIFFOpen("./dummy_file", "r+");
    if (!tifFile) {
        return 0;
    }

    // Fuzz TIFFIsTiled
    int isTiled = TIFFIsTiled(tifFile);

    // Fuzz TIFFGetStrileOffsetWithErr
    uint32_t strile = 0;
    int err = 0;

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function TIFFGetStrileOffsetWithErr with TIFFGetStrileByteCountWithErr
    uint64_t offset = TIFFGetStrileByteCountWithErr(tifFile, strile, &err);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Fuzz TIFFForceStrileArrayWriting
    int forceWrite = TIFFForceStrileArrayWriting(tifFile);

    // Fuzz TIFFSetWriteOffset
    TIFFSetWriteOffset(tifFile, static_cast<toff_t>(offset));

    // Fuzz TIFFDeferStrileArrayWriting
    int deferWrite = TIFFDeferStrileArrayWriting(tifFile);

    // Fuzz TIFFWriteCheck
    int writeCheck = TIFFWriteCheck(tifFile, isTiled, "dummy_tag");

    // Cleanup
    TIFFClose(tifFile);

    return 0;
}