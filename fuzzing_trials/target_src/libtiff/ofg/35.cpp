#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h> // Include this for the 'close' function

extern "C" {
    // Wrap C headers and functions with extern "C" to ensure proper linkage
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == nullptr) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file using the temporary file path
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff != nullptr) {
        // Call the function-under-test
        TIFFReadWriteProc readProc = TIFFGetReadProc(tiff);

        // Perform any additional operations if needed
        if (readProc != nullptr) {
            // Example: Call the readProc function (if applicable)
            // readProc(...);
        }

        // Close the TIFF file
        TIFFClose(tiff);
    }

    // Clean up the temporary file
    remove(tmpl);

    return 0;
}