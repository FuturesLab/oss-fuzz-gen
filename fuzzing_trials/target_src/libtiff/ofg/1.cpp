#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cstdlib>  // For mkstemp
#include <unistd.h>  // For close and remove
#include <cstdarg>  // For va_list

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Create a temporary file to write the TIFF data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }

    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0;
    }

    // Extract a tag from the data
    uint32_t tag = *(reinterpret_cast<const uint32_t*>(data));

    // Call the function-under-test
    // Use va_list to call TIFFVGetFieldDefaulted
    int value;
    if (TIFFGetField(tiff, tag, &value)) {
        // Successfully retrieved the field
    }

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}