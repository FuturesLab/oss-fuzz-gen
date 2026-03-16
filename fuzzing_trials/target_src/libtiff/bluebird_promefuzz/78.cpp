#include <iostream>
#include "sstream"
#include <string>
#include <vector>
#include "cstring"
#include "cstdlib"
#include <cstdio>
#include "cstdint"
#include <cstddef>
#include "cstdint"
#include <cstdio>
#include "tiffio.h"

extern "C" int LLVMFuzzerTestOneInput_78(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Create a dummy TIFF file
    FILE *file = fopen("./dummy_file", "wb+");
    if (!file) {
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    TIFF *tif = TIFFOpen("./dummy_file", "r+");
    if (!tif) {
        return 0;
    }

    // 1. TIFFWriteDirectory
    if (TIFFWriteDirectory(tif)) {
        // 2. TIFFSetDirectory

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function TIFFSetDirectory with TIFFUnlinkDirectory
        TIFFUnlinkDirectory(tif, 0);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR



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