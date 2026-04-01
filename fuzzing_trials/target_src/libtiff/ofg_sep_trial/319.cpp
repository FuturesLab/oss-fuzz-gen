#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <tiffio.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_319(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0; // Ensure there is enough data for mode and filename
    }

    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Failed to create a temporary file
    }

    // Write the fuzz data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }

    fwrite(data, 1, size, file);
    fclose(file);

    // Prepare the mode string
    const char *mode = reinterpret_cast<const char *>(data + size - 1);

    // Call the function-under-test
    TIFF *tiff = TIFFOpen(tmpl, mode);

    // Cleanup
    if (tiff) {
        TIFFClose(tiff);
    }
    remove(tmpl);

    return 0;
}