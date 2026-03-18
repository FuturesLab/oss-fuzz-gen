#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <tiffio.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_220(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for a meaningful test
    if (size < 1) {
        return 0;
    }

    // Create a temporary TIFF file for testing
    char tmpl[] = "/tmp/fuzzfileXXXXXX.tiff";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }

    // Write the fuzz data to the file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0;
    }

    // Prepare the parameters for TIFFWriteCheck
    int isTiled = 1; // Arbitrary non-zero value
    const char *module = "fuzzModule";

    // Call the function-under-test
    TIFFWriteCheck(tiff, isTiled, module);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}