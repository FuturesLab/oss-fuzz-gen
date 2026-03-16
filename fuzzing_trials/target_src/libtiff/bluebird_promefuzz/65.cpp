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

extern "C" int LLVMFuzzerTestOneInput_65(const uint8_t *Data, size_t Size) {
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
        TIFFSetDirectory(tif, 0);

        // 3. TIFFCurrentDirOffset
        TIFFCurrentDirOffset(tif);

        // 4. TIFFSetDirectory
        TIFFSetDirectory(tif, 0);

        // 5. TIFFForceStrileArrayWriting

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from TIFFSetDirectory to TIFFReadRGBAStrip
        int ret_TIFFRewriteDirectory_qsswx = TIFFRewriteDirectory(tif);
        if (ret_TIFFRewriteDirectory_qsswx < 0){
        	return 0;
        }

        int ret_TIFFReadRGBAStrip_hkgdo = TIFFReadRGBAStrip(tif, Size, (uint32_t *)&ret_TIFFRewriteDirectory_qsswx);
        if (ret_TIFFReadRGBAStrip_hkgdo < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        TIFFForceStrileArrayWriting(tif);

        // 6. TIFFFlushData

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function TIFFFlushData with TIFFIsMSB2LSB
        TIFFIsMSB2LSB(tif);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


    }

    TIFFClose(tif);
    return 0;
}