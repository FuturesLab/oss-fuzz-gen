#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <tiffio.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_308(const uint8_t *data, size_t size) {
    // Create a temporary file to hold the input data
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

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff != nullptr) {
        // Call the function-under-test
        TIFFSeekProc seekProc = TIFFGetSeekProc(tiff);

        // Use the seekProc to perform some operations if needed
        // (This is just an example, you might not need to use it)
        if (seekProc != nullptr) {
            // Example: seek to the beginning of the file
            seekProc((thandle_t)(intptr_t)fd, 0, SEEK_SET);
        }

        // Close the TIFF file
        TIFFClose(tiff);
    }

    // Clean up the temporary file
    remove(tmpl);

    return 0;
}