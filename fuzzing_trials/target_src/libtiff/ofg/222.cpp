#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_222(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for creating a string
    if (size < 1) {
        return 0;
    }

    // Create a temporary TIFF file in memory
    TIFF* tiff = TIFFOpen("temp.tiff", "w");
    if (tiff == nullptr) {
        return 0;
    }

    // Use the first byte of the data to determine the 'isTiled' parameter
    int isTiled = data[0] % 2;

    // Create a null-terminated string from the remaining data
    size_t str_size = size - 1;
    char* mode = static_cast<char*>(malloc(str_size + 1));
    if (mode == nullptr) {
        TIFFClose(tiff);
        return 0;
    }
    memcpy(mode, data + 1, str_size);
    mode[str_size] = '\0';

    // Call the function-under-test
    TIFFWriteCheck(tiff, isTiled, mode);

    // Clean up
    free(mode);
    TIFFClose(tiff);

    return 0;
}