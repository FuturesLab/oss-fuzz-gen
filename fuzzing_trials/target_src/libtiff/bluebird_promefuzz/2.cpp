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
#include "cstring"

static void customWarningHandler(const char* module, const char* fmt, va_list ap) {
    // Custom warning handler logic (could be logging, etc.)
    vfprintf(stderr, fmt, ap);
}

static void customErrorHandler(const char* module, const char* fmt, va_list ap) {
    // Custom error handler logic (could be logging, etc.)
    vfprintf(stderr, fmt, ap);
}

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    } // Not enough data

    // Setup dummy file
    const char* dummyFileName = "./dummy_file";
    FILE* file = fopen(dummyFileName, "wb");
    if (!file) {
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open TIFF file
    TIFF* tif = TIFFOpen(dummyFileName, "r+");
    if (!tif) {
        return 0;
    }

    // Set custom warning and error handlers

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from TIFFOpen to TIFFGetFieldDefaulted

    int ret_TIFFGetFieldDefaulted_kbvcc = TIFFGetFieldDefaulted(tif, UVSCALE);
    if (ret_TIFFGetFieldDefaulted_kbvcc < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    TIFFErrorHandler prevWarningHandler = TIFFSetWarningHandler(customWarningHandler);
    TIFFErrorHandler prevErrorHandler = TIFFSetErrorHandler(customErrorHandler);

    // Attempt to flush data
    TIFFFlushData(tif);

    // Attempt to checkpoint directory
    TIFFCheckpointDirectory(tif);

    // Attempt to write directory
    TIFFWriteDirectory(tif);

    // Attempt to set directory
    tdir_t dirNum = Data[0] % 256; // Use first byte as directory number
    TIFFSetDirectory(tif, dirNum);

    // Restore previous handlers
    TIFFSetWarningHandler(prevWarningHandler);
    TIFFSetErrorHandler(prevErrorHandler);

    // Cleanup
    TIFFClose(tif);
    remove(dummyFileName);

    return 0;
}