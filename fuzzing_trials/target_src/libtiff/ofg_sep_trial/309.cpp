#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

// Define a temporary file path
const char *tempFilePath = "/tmp/fuzz_tiff.tiff";

// Helper function to create a temporary TIFF file
void createTempTIFFFile(const uint8_t *data, size_t size) {
    FILE *file = fopen(tempFilePath, "wb");
    if (file != nullptr) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

extern "C" int LLVMFuzzerTestOneInput_309(const uint8_t *data, size_t size) {
    // Create a temporary TIFF file with the fuzz data
    createTempTIFFFile(data, size);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tempFilePath, "r");
    if (tiff != nullptr) {
        // Call the function-under-test
        TIFFSeekProc seekProc = TIFFGetSeekProc(tiff);

        // Use the seekProc if needed (for example, call it with some parameters)
        if (seekProc != nullptr) {
            // Example usage of seekProc
            seekProc(nullptr, 0, SEEK_SET);
        }

        // Close the TIFF file
        TIFFClose(tiff);
    }

    // Remove the temporary file
    remove(tempFilePath);

    return 0;
}