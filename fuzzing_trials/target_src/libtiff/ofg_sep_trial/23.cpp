#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        unlink(tmpl);
        return 0;
    }
    close(fd);

    // Open the TIFF file using libtiff
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        unlink(tmpl);
        return 0;
    }

    // Prepare a non-null char buffer for the second parameter
    char errmsg[1024];
    memset(errmsg, 0, sizeof(errmsg));

    // Call the function-under-test
    TIFFRGBAImageOK(tiff, errmsg);

    // Clean up
    TIFFClose(tiff);
    unlink(tmpl);

    return 0;
}