#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <tiffio.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_65(const uint8_t *data, size_t size) {
    if (size < sizeof(uint64_t)) {
        return 0; // Not enough data to extract a uint64_t
    }

    // Create a temporary TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX.tiff";
    int fd = mkstemps(tmpl, 5);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r+");
    if (!tiff) {
        return 0;
    }

    // Extract a uint64_t from the data
    uint64_t customDirOffset = 0;
    memcpy(&customDirOffset, data, sizeof(uint64_t));

    // Call the function-under-test
    TIFFWriteCustomDirectory(tiff, &customDirOffset);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}