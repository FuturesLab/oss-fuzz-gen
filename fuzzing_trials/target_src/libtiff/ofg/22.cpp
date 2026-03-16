#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h> // Include for write, close, unlink

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
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
    close(fd);

    // Open the TIFF file using the TIFF library
    TIFF* tif = TIFFOpen(tmpl, "r");
    if (tif == nullptr) {
        unlink(tmpl);
        return 0;
    }

    // Prepare a non-NULL char pointer
    char description[] = "Test Description";

    // Call the function-under-test
    TIFFRGBAImageOK(tif, description);

    // Clean up
    TIFFClose(tif);
    unlink(tmpl);

    return 0;
}