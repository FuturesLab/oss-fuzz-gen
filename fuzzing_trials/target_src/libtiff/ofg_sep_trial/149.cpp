#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_149(const uint8_t *data, size_t size) {
    if (size < 4) {
        return 0; // Not enough data to proceed
    }

    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Failed to create a temporary file
    }

    // Write the fuzz data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == nullptr) {
        close(fd);
        return 0; // Failed to open the file
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF* tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0; // Failed to open the TIFF file
    }

    // Extract a tag from the data
    uint32_t tag = 0;
    memcpy(&tag, data, sizeof(tag));

    // Buffer to store the field value
    char field_value[256]; // Adjust size as needed

    // Call the function-under-test
    TIFFGetField(tiff, tag, field_value);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}