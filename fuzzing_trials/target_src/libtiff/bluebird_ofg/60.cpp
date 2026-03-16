#include "tiffio.h"
#include "cstdint"
#include <cstdio>
#include "cstdlib"
#include <unistd.h> // Include this for the 'close' function

extern "C" {
    #include "tiffio.h"
}

extern "C" int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient to create a valid input
    if (size < sizeof(thandle_t)) {
        return 0;
    }

    // Create a temporary file to simulate a TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb+");
    if (!file) {
        close(fd);
        return 0;
    }

    // Write the data to the temporary file
    fwrite(data, 1, size, file);
    fflush(file);
    fseek(file, 0, SEEK_SET);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        fclose(file);
        return 0;
    }

    // Extract a thandle_t value from the input data
    thandle_t clientdata = *(reinterpret_cast<const thandle_t*>(data));

    // Call the function-under-test
    thandle_t result = TIFFSetClientdata(tiff, clientdata);

    // Clean up
    TIFFClose(tiff);
    fclose(file);
    remove(tmpl);

    return 0;
}