#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <unistd.h>  // Include for close() and write()
#include <cstdio>    // Include for remove()

// Ensure the TIFF library is linked correctly with C++
extern "C" {
    #include <tiffio.h>
}

// Fuzzing harness for TIFFClientdata function
extern "C" int LLVMFuzzerTestOneInput_112(const uint8_t *data, size_t size) {
    // Create a memory-mapped TIFF file from the input data
    if (size < 4) {
        // TIFF header is at least 4 bytes, return if input is too small
        return 0;
    }

    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {  // Cast size to ssize_t
        close(fd);
        return 0;
    }
    close(fd);

    // Open the TIFF file
    TIFF* tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    thandle_t handle = TIFFClientdata(tiff);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}