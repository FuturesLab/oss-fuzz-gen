#include <stdint.h>
#include "cstdlib"
#include "cstring"
#include <unistd.h>  // Include for close, write, and unlink
#include <fcntl.h>   // Include for mkstemp

extern "C" {
    #include "tiffio.h"
    #include "/src/libtiff/libtiff/tiff.h"
}

extern "C" int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for a minimal TIFF header
    if (size < 8) {
        return 0;
    }

    // Create a temporary file to store the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        unlink(tmpl);
        return 0;
    }

    // Initialize the TIFFRGBAImage structure
    TIFFRGBAImage img;
    char emsg[1024];

    // Call the function-under-test
    int result = TIFFRGBAImageBegin(&img, tiff, 0, emsg);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from TIFFRGBAImageBegin to TIFFVStripSize64


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of TIFFVStripSize64
    uint64_t ret_TIFFVStripSize64_xdaod = TIFFVStripSize64(tiff, CIELABTORGB_TABLE_RANGE);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_TIFFVStripSize64_xdaod < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    TIFFClose(tiff);
    unlink(tmpl);

    return 0;
}