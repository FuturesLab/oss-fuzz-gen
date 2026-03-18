#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>  // Include for the 'close' function

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_266(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
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

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl); // Clean up the temporary file
        return 0;
    }

    // Use a non-zero directory offset for fuzzing
    uint64_t directoryOffset = 1; // A simple non-zero value

    // Call the function-under-test
    TIFFSetSubDirectory(tiff, directoryOffset);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl); // Remove the temporary file

    return 0;
}