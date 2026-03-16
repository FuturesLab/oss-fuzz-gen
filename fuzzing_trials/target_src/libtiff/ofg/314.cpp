#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_314(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        remove(tmpl);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the TIFF file
    TIFF* tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Extract a uint32_t index from the data
    uint32_t index = *reinterpret_cast<const uint32_t*>(data);

    // Call the function-under-test
    uint64_t byteCount = TIFFGetStrileByteCount(tiff, index);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}