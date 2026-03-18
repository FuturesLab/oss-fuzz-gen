#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h> // Include this for the 'close' function

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_333(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == nullptr) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the temporary file with TIFFOpen
    TIFF *tif = TIFFOpen(tmpl, "r");
    if (tif != nullptr) {
        // Call the function-under-test
        uint64_t stripSize = TIFFStripSize64(tif);

        // Close the TIFF file
        TIFFClose(tif);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}