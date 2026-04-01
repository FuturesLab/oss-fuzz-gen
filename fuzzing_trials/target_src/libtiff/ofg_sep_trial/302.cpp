#include <cstdint>
#include <cstdio>
#include <cstdlib> // For mkstemp and close
#include <unistd.h> // For mkstemp and close

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_302(const uint8_t *data, size_t size) {
    // Create a temporary file to store the TIFF data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Failed to create a temporary file
    }

    // Write the input data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == nullptr) {
        close(fd);
        return 0; // Failed to open the file
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl); // Clean up the temporary file
        return 0; // Failed to open the TIFF file
    }

    // Initialize parameters for the function call
    uint32_t strile = 0; // Example strile index
    int err = 0;

    // Call the function-under-test
    uint64_t byteCount = TIFFGetStrileByteCountWithErr(tiff, strile, &err);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl); // Remove the temporary file

    return 0;
}