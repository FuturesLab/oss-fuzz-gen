#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_176(const uint8_t *data, size_t size) {
    // Initialize TIFF variables
    TIFF *tiff = nullptr;
    uint32_t strile_index = 0;

    // Create a temporary file to store the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the TIFF file
    tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        // Clean up the temporary file
        unlink(tmpl);
        return 0;
    }

    // Fuzzing the TIFFGetStrileOffset function
    // Try multiple strile indices to explore different paths
    for (uint32_t i = 0; i < 10; ++i) {
        strile_index = i;
        TIFFGetStrileOffset(tiff, strile_index);
    }

    // Close the TIFF file
    TIFFClose(tiff);

    // Clean up the temporary file
    unlink(tmpl);

    return 0;
}