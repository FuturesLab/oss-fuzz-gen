#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>  // For close and write
#include <sys/types.h> // For ssize_t

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_272(const uint8_t *data, size_t size) {
    // Create a temporary file to store the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != ssize_t(size)) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the TIFF file
    TIFF *tif = TIFFOpen(tmpl, "r");
    if (tif == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Prepare parameters for TIFFReadEncodedStrip
    uint32_t strip = 0;  // Assuming the first strip for simplicity
    tmsize_t bufferSize = TIFFStripSize(tif);
    void *buffer = malloc(bufferSize);
    if (buffer == nullptr) {
        TIFFClose(tif);
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFReadEncodedStrip(tif, strip, buffer, bufferSize);

    // Clean up
    free(buffer);
    TIFFClose(tif);
    remove(tmpl);

    return 0;
}