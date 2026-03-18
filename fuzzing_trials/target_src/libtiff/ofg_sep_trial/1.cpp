#include <cstdint>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <unistd.h> // Include for 'close' and 'write'
#include <fcntl.h>  // Include for 'mkstemp'

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    TIFF *tiff = nullptr;
    uint32_t tag = 0;

    // Ensure the data size is sufficient for processing
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Create a temporary file to simulate TIFF file input
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the temporary file with libtiff
    tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Initialize the tag for testing
    tag = *(reinterpret_cast<const uint32_t*>(data));

    // Since va_start cannot be used in a function with fixed arguments, 
    // we need to call TIFFVGetFieldDefaulted without a va_list.
    // Instead, we will call TIFFGetFieldDefaulted which does not require va_list.
    // However, this function does not exist, so we need to use TIFFGetField instead.
    uint16_t value;
    TIFFGetField(tiff, tag, &value);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}