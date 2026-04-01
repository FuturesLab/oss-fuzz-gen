#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <unistd.h>
#include <cstdlib> // Include for mkstemp
#include <cstdarg> // Include for va_list, va_start, va_end

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_115(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t)) {
        return 0; // Not enough data to extract a uint32_t tag
    }

    // Create a temporary TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    FILE *file = fdopen(fd, "wb+");
    if (!file) {
        close(fd);
        return 0;
    }

    fwrite(data, 1, size, file);
    fflush(file);
    rewind(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r+");
    if (!tiff) {
        fclose(file);
        return 0;
    }

    // Prepare parameters for TIFFVSetField
    uint32_t tag = *((uint32_t *)data);
    // Since va_list cannot be initialized with fixed arguments, we will simulate it
    // by assuming the tag requires an integer value, which we extract from the data
    if (size >= sizeof(uint32_t) * 2) {
        uint32_t value = *((uint32_t *)(data + sizeof(uint32_t)));
        TIFFSetField(tiff, tag, value);
    }

    // Clean up
    TIFFClose(tiff);
    fclose(file);
    remove(tmpl);

    return 0;
}