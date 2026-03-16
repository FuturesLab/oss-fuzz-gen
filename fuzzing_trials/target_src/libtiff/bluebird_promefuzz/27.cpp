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

static int CustomErrorHandler(TIFF* tif, void* user_data, const char* module, const char* fmt, va_list ap) {
    vfprintf(stderr, fmt, ap);
    return 0;
}

static int CustomWarningHandler(TIFF* tif, void* user_data, const char* module, const char* fmt, va_list ap) {
    vfprintf(stderr, fmt, ap);
    return 0;
}

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Prepare a dummy file for TIFFOpenExt
    FILE* file = fopen("./dummy_file", "wb");
    if (!file) {
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    TIFFOpenOptions* opts = TIFFOpenOptionsAlloc();
    if (!opts) {
        return 0;
    }

    TIFFOpenOptionsSetErrorHandlerExtR(opts, CustomErrorHandler, nullptr);
    TIFFOpenOptionsSetWarningHandlerExtR(opts, CustomWarningHandler, nullptr);

    TIFF* tiff = TIFFOpenExt("./dummy_file", "r", opts);
    TIFFOpenOptionsFree(opts);

    if (tiff) {
        TIFFErrorExtR(tiff, "FuzzModule", "Error occurred during fuzzing");

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function TIFFWarningExtR with TIFFErrorExtR
        TIFFErrorExtR(tiff, "FuzzModule", "Warning occurred during fuzzing");
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        TIFFClose(tiff);
        tiff = nullptr;
    }
    return 0;
}