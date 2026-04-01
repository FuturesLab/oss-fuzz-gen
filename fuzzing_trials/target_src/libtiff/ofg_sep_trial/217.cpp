#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h> // Include for the 'close' function

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_217(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // If file creation fails, exit
    }

    // Write the input data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == nullptr) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r+");
    if (tiff != nullptr) {
        // Call the function-under-test
        TIFFRewriteDirectory(tiff);

        // Close the TIFF file
        TIFFClose(tiff);
    }

    // Clean up the temporary file
    remove(tmpl);

    return 0;
}