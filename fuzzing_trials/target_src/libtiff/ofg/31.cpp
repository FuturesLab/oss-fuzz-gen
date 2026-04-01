#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>

extern "C" {
#include <tiffio.h>
#include <stdarg.h>
}

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write data to the temporary file
    if (write(fd, data, size) != ssize_t(size)) {
        close(fd);
        unlink(tmpl);
        return 0;
    }
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        unlink(tmpl);
        return 0;
    }

    // Prepare the tag and va_list for TIFFVGetField
    uint32_t tag;
    memcpy(&tag, data, sizeof(uint32_t));

    // Call the function-under-test
    TIFFVGetField(tiff, tag, nullptr);

    // Clean up
    TIFFClose(tiff);
    unlink(tmpl);

    return 0;
}