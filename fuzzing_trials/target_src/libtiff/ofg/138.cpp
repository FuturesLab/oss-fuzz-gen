#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_138(const uint8_t *data, size_t size) {
    TIFF *tiff = nullptr;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);

    if (fd == -1) {
        return 0;
    }

    // Write the fuzzing data to the temporary file
    if (write(fd, data, size) != ssize_t(size)) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the temporary file with TIFF
    tiff = TIFFOpen(tmpl, "r+");
    if (tiff == nullptr) {
        return 0;
    }

    // Call the function-under-test
    TIFFWriteDirectory(tiff);

    // Close the TIFF file
    TIFFClose(tiff);

    // Clean up the temporary file
    unlink(tmpl);

    return 0;
}