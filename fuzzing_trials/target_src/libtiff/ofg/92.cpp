#include <cstddef>
#include <cstdint>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio> // Include for mkstemp
#include <cstdlib> // Include for mkstemp

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_92(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a TIFF file input
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Exit if the temporary file cannot be created
    }

    // Write the fuzzing data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        unlink(tmpl);
        return 0; // Exit if the data cannot be written to the file
    }
    close(fd);

    // Open the temporary file as a TIFF file
    TIFF *tif = TIFFOpen(tmpl, "r");
    if (tif == nullptr) {
        unlink(tmpl);
        return 0; // Exit if the TIFF file cannot be opened
    }

    // Call the function-under-test
    TIFFDeferStrileArrayWriting(tif);

    // Clean up
    TIFFClose(tif);
    unlink(tmpl);

    return 0;
}