#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>  // Include for 'close' and 'unlink'

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_244(const uint8_t *data, size_t size) {
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzzing data to the temporary file
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
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    int result = TIFFLastDirectory(tiff);

    // Clean up
    TIFFClose(tiff);
    unlink(tmpl);

    return 0;
}