#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>  // Include for close, write
#include <fcntl.h>   // Include for mkstemp

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_168(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the TIFF file
    TIFF* tif = TIFFOpen(tmpl, "r");
    if (tif == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    uint32_t numStrips = TIFFNumberOfStrips(tif);

    // Clean up
    TIFFClose(tif);
    remove(tmpl);

    return 0;
}