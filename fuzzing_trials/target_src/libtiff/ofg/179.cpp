#include <cstdint>
#include <cstdio>
#include <unistd.h>  // For mkstemp, close, and write
#include <sys/types.h>  // For ssize_t
#include <sys/stat.h>   // For mode constants
#include <fcntl.h>      // For open
#include <cstdlib>      // For remove

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_179(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to extract a uint32_t value
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Create a temporary file to store the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        remove(tmpl);
        return 0;
    }
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Extract a uint32_t value from the input data
    uint32_t strile = *reinterpret_cast<const uint32_t *>(data);

    // Call the function-under-test
    uint64_t offset = TIFFGetStrileOffset(tiff, strile);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}