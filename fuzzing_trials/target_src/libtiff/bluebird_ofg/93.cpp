#include "tiffio.h"
#include "cstdint"
#include "cstdlib"
#include <cstdio>
#include <unistd.h>  // Include for the 'close' function

extern "C" {
    #include "tiffio.h"  // Ensure all C headers are wrapped in extern "C"
}

extern "C" int LLVMFuzzerTestOneInput_93(const uint8_t *data, size_t size) {
    // Ensure we have enough data for the parameters
    if (size < sizeof(uint32_t) + sizeof(uint16_t)) {
        return 0;
    }

    // Create a temporary TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0;
    }

    // Extract parameters from the data

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from TIFFOpen to TIFFVTileSize
    uint64_t ret_TIFFStripSize64_bmzmw = TIFFStripSize64(tiff);
    if (ret_TIFFStripSize64_bmzmw < 0){
    	return 0;
    }

    tmsize_t ret_TIFFVTileSize_nckym = TIFFVTileSize(tiff, (uint32_t )ret_TIFFStripSize64_bmzmw);

    // End mutation: Producer.APPEND_MUTATOR

    uint32_t row = *(reinterpret_cast<const uint32_t *>(data));
    uint16_t sample = *(reinterpret_cast<const uint16_t *>(data + sizeof(uint32_t)));

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of TIFFComputeStrip
    uint32_t strip = TIFFComputeStrip(tiff, row, UVSCALE);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from TIFFComputeStrip to TIFFGetStrileByteCount
    int ret_TIFFRewriteDirectory_jsxob = TIFFRewriteDirectory(tiff);
    if (ret_TIFFRewriteDirectory_jsxob < 0){
    	return 0;
    }

    uint64_t ret_TIFFGetStrileByteCount_guwgx = TIFFGetStrileByteCount(tiff, strip);
    if (ret_TIFFGetStrileByteCount_guwgx < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}