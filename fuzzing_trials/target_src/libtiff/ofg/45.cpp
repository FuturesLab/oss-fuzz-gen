#include <cstdint>
#include <cstdio>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    // Ensure there is enough data to proceed
    if (size < sizeof(int)) {
        return 0;
    }

    // Create a temporary file to simulate a TIFF file
    FILE *tempFile = tmpfile();
    if (!tempFile) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    fwrite(data, 1, size, tempFile);
    fflush(tempFile);
    rewind(tempFile);

    // Open the TIFF file using libtiff
    TIFF *tiff = TIFFFdOpen(fileno(tempFile), "temp", "r");
    if (!tiff) {
        fclose(tempFile);
        return 0;
    }

    // Extract an integer from the data to use as the file descriptor
    int fileDescriptor = *(reinterpret_cast<const int*>(data));

    // Call the function-under-test
    TIFFSetFileno(tiff, fileDescriptor);

    // Clean up
    TIFFClose(tiff);
    fclose(tempFile);

    return 0;
}