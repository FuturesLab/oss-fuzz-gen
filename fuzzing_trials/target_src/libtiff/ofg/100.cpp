extern "C" {
#include <tiffio.h>
}

#include <cstdint>
#include <cstdio>
#include <cstdlib>   // For mkstemp
#include <unistd.h>  // For close, unlink
#include <fcntl.h>   // For write

extern "C" int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size) {
    TIFF *tiff = nullptr;
    toff_t offset = 0;

    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Open the temporary file as a TIFF file
    tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Ensure offset is within a reasonable range
    if (size >= sizeof(toff_t)) {
        offset = *(reinterpret_cast<const toff_t*>(data));
    }

    // Call the function-under-test
    TIFFReadGPSDirectory(tiff, offset);

    // Clean up
    TIFFClose(tiff);
    close(fd);
    unlink(tmpl);

    return 0;
}