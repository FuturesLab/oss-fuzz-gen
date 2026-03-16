#include "tiffio.h"
#include "cstdint"
#include <cstdio>
#include "cstdlib"
#include "cstring"
#include <unistd.h>  // Include for write and close
#include <fcntl.h>   // Include for mkstemps

extern "C" int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    // Create a temporary TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX.tiff";
    int fd = mkstemps(tmpl, 5);
    if (fd == -1) {
        return 0;
    }
    
    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Create a non-null string for the field name
    const char *fieldName = "ImageWidth";

    // Call the function-under-test
    const TIFFField *field = TIFFFieldWithName(tiff, fieldName);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}