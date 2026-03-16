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

static TIFF* createDummyTIFF() {
    FILE* dummyFile = fopen("./dummy_file", "w+b");
    if (!dummyFile) return nullptr;
    fclose(dummyFile);
    return TIFFOpen("./dummy_file", "w+");
}

extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    TIFF *tif = createDummyTIFF();
    if (!tif) return 0;

    // Prepare buffer for TIFFWriteBufferSetup and TIFFReadBufferSetup
    void *buffer = nullptr;
    tmsize_t bufferSize = static_cast<tmsize_t>(Size);

    // 1. Test TIFFWriteBufferSetup
    TIFFWriteBufferSetup(tif, buffer, bufferSize);

    // 2. Test TIFFCheckpointDirectory
    TIFFCheckpointDirectory(tif);

    // 3. Test TIFFSetMode
    int mode = Data[0] % 3; // Assuming 3 modes for simplicity
    TIFFSetMode(tif, mode);

    // 4. Test TIFFFlush
    TIFFFlush(tif);

    // 5. Test TIFFReadBufferSetup
    TIFFReadBufferSetup(tif, buffer, bufferSize);

    // 6. Test TIFFDeferStrileArrayWriting
    TIFFDeferStrileArrayWriting(tif);

    TIFFClose(tif);
    return 0;
}