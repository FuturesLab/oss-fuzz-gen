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
#include <cstdio>
#include "cstdint"
#include <cstddef>
#include <fcntl.h>
#include <unistd.h>

static void writeDummyFile(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

extern "C" int LLVMFuzzerTestOneInput_80(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Step 1: Write data to a dummy file
    writeDummyFile(Data, Size);

    // Step 2: Open the dummy file
    int fd = open("./dummy_file", O_RDWR);
    if (fd < 0) {
        return 0;
    }

    // Step 3: Use TIFFFdOpen to open the TIFF file
    TIFF *tif = TIFFFdOpen(fd, "./dummy_file", "r+");
    if (!tif) {
        close(fd);
        return 0;
    }

    // Step 4: Invoke TIFFFileno
    int fileno = TIFFFileno(tif);

    // Step 5: Read directory using TIFFReadDirectory
    int readDirResult = TIFFReadDirectory(tif);

    // Step 6: Flush data using TIFFFlush
    int flushResult = TIFFFlush(tif);

    // Step 7: Attempt to unlink a directory

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from TIFFFlush to _TIFFmemcmp
    const char* ret_TIFFFileName_cawuh = TIFFFileName(tif);
    if (ret_TIFFFileName_cawuh == NULL){
    	return 0;
    }

    int ret__TIFFmemcmp_aelck = _TIFFmemcmp((const void *)tif, (const void *)tif, 0);
    if (ret__TIFFmemcmp_aelck < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    TIFFUnlinkDirectory(tif, 1);

    // Step 8: Clean up
    TIFFClose(tif);
    close(fd);

    return 0;
}