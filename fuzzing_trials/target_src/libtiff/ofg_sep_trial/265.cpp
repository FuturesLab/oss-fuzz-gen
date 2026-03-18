#include <cstdint>
#include <cstdio>
#include <cstdlib>  // Include for mkstemp and close
#include <unistd.h> // Include for mkstemp and close

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_265(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
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
        remove(tmpl);
        return 0;
    }

    // Use the first 8 bytes of the data as the directory offset
    uint64_t directoryOffset = 0;
    if (size >= sizeof(directoryOffset)) {
        directoryOffset = *reinterpret_cast<const uint64_t *>(data);
    }

    // Call the function-under-test
    TIFFSetSubDirectory(tiff, directoryOffset);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}