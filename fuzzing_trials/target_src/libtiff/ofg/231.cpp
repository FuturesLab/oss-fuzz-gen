#include <cstdint>
#include <cstdlib>
#include <cstring>  // Include this for memcpy

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_231(const uint8_t *data, size_t size) {
    // Initialize TIFF structure
    TIFF *tiff = TIFFOpen("dummy.tiff", "r");
    if (tiff == nullptr) {
        return 0;
    }

    // Define and initialize parameters for TIFFReadFromUserBuffer
    uint32_t read_offset = 0;  // Starting offset for reading
    void *user_buffer = malloc(size);  // Allocate a buffer of the same size as the input data
    if (user_buffer == nullptr) {
        TIFFClose(tiff);
        return 0;
    }

    tmsize_t user_buffer_size = static_cast<tmsize_t>(size);
    
    // Copy input data to user buffer
    memcpy(user_buffer, data, size);

    void *output_buffer = malloc(size);  // Allocate output buffer
    if (output_buffer == nullptr) {
        free(user_buffer);
        TIFFClose(tiff);
        return 0;
    }
    
    tmsize_t output_buffer_size = static_cast<tmsize_t>(size);

    // Call the function-under-test
    TIFFReadFromUserBuffer(tiff, read_offset, user_buffer, user_buffer_size, output_buffer, output_buffer_size);

    // Clean up
    free(user_buffer);
    free(output_buffer);
    TIFFClose(tiff);

    return 0;
}