#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <tiffio.h>
#include <unistd.h> // Include for close()

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_319(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd < 0) {
        return 0; // If file creation fails, exit early
    }

    // Write the fuzz data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == nullptr) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file using the function-under-test
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff != nullptr) {
        // If the file is successfully opened, close it
        TIFFClose(tiff);
    }

    // Clean up the temporary file
    remove(tmpl);

    return 0;
}