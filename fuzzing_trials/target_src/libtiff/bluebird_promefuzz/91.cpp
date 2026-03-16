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
#include <cstdarg>
#include "cstring"
#include "tiffio.h"

static TIFF *openDummyTIFF() {
    TIFF *tif = TIFFOpenExt("./dummy_file", "w", nullptr);
    if (!tif) {

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function TIFFErrorExtR with TIFFWarningExtR
        TIFFWarningExtR(NULL, "openDummyTIFF", "Failed to open dummy TIFF file.");
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


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

extern "C" int LLVMFuzzerTestOneInput_91(const uint8_t *Data, size_t Size) {
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

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of TIFFWriteCheck
    TIFFWriteCheck(tif, TIFF_VARIABLE, "TestWriteCheck");
    // End mutation: Producer.REPLACE_ARG_MUTATOR




    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from TIFFWriteCheck to TIFFClientdata

    thandle_t ret_TIFFClientdata_iilin = TIFFClientdata(tif);

    // End mutation: Producer.APPEND_MUTATOR

    TIFFClose(tif);
    return 0;
}