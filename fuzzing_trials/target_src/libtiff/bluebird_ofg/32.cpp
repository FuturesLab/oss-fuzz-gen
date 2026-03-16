#include "tiffio.h"
#include "cstdint"
#include "cstdlib"
#include <cstdio>
#include <unistd.h>  // Include for the 'close' function

extern "C" {
    #include "tiffio.h"  // Ensure all C headers are wrapped in extern "C"
}

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from TIFFOpen to TIFFReadRGBAImage
    int ret_TIFFIsCODECConfigured_azamr = TIFFIsCODECConfigured(TIFF_VARIABLE2);
    if (ret_TIFFIsCODECConfigured_azamr < 0){
    	return 0;
    }
    uint64_t ret_TIFFTileRowSize64_ciomv = TIFFTileRowSize64(tiff);
    if (ret_TIFFTileRowSize64_ciomv < 0){
    	return 0;
    }
    uint32_t cxkqkcpx = 0;

    int ret_TIFFReadRGBAImage_riyby = TIFFReadRGBAImage(tiff, (uint32_t )ret_TIFFIsCODECConfigured_azamr, TIFF_VARIABLE2, &cxkqkcpx, (int )ret_TIFFTileRowSize64_ciomv);
    if (ret_TIFFReadRGBAImage_riyby < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    uint32_t row = *(reinterpret_cast<const uint32_t *>(data));
    uint16_t sample = *(reinterpret_cast<const uint16_t *>(data + sizeof(uint32_t)));

    // Call the function-under-test
    uint32_t strip = TIFFComputeStrip(tiff, row, sample);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}