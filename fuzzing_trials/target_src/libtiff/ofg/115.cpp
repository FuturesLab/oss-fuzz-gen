#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <tiffio.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_115(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for our needs
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Create a temporary TIFF file in memory
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Initialize a TIFF structure
    TIFF *tiff = TIFFOpen(tmpl, "w");
    if (tiff == nullptr) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Extract a uint32_t value from the input data
    uint32_t field_tag = *(reinterpret_cast<const uint32_t*>(data));

    // Call the function-under-test
    TIFFUnsetField(tiff, field_tag);

    // Clean up
    TIFFClose(tiff);
    close(fd);
    unlink(tmpl);

    return 0;
}