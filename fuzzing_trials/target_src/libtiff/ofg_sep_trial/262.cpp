#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_262(const uint8_t *data, size_t size) {
    if (size < sizeof(thandle_t)) {
        return 0; // Not enough data to extract a thandle_t
    }

    // Create a temporary TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX.tiff";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Could not create a temporary file
    }

    // Write the data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0; // Could not write data to the file
    }

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        close(fd);
        unlink(tmpl);
        return 0; // Could not open the TIFF file
    }

    // Extract a thandle_t from the data
    thandle_t clientdata = *(reinterpret_cast<const thandle_t *>(data));

    // Call the function-under-test
    thandle_t result = TIFFSetClientdata(tiff, clientdata);

    // Clean up
    TIFFClose(tiff);
    close(fd);
    unlink(tmpl);

    return 0;
}