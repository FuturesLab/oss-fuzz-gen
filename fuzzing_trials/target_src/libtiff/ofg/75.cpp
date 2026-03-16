#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h> // Include for write and close functions

extern "C" {
    int LLVMFuzzerTestOneInput_75(const uint8_t *data, size_t size) {
        if (size < sizeof(TIFFFieldInfo)) {
            return 0;
        }

        // Create a temporary file to simulate a TIFF file
        char tmpl[] = "/tmp/fuzzfileXXXXXX";
        int fd = mkstemp(tmpl);
        if (fd == -1) {
            return 0;
        }

        // Write the fuzz data to the temporary file
        write(fd, data, size);
        close(fd);

        // Open the temporary file as a TIFF
        TIFF *tiff = TIFFOpen(tmpl, "r");
        if (tiff == nullptr) {
            remove(tmpl);
            return 0;
        }

        // Prepare a TIFFFieldInfo object from the fuzz data
        const TIFFFieldInfo *fieldInfo = reinterpret_cast<const TIFFFieldInfo *>(data);

        // Call the function-under-test
        uint32_t fieldCount = 1; // Assume at least one field for testing
        TIFFMergeFieldInfo(tiff, fieldInfo, fieldCount);

        // Clean up
        TIFFClose(tiff);
        remove(tmpl);

        return 0;
    }
}