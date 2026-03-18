#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_230(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for the function parameters
    if (size < sizeof(uint32_t) + sizeof(tmsize_t) * 2) {
        return 0;
    }

    // Initialize TIFF structure
    TIFF *tiff = TIFFOpen("/dev/null", "r");
    if (tiff == nullptr) {
        return 0;
    }

    // Extract parameters from data
    uint32_t read_offset = *(reinterpret_cast<const uint32_t*>(data));
    tmsize_t read_size = *(reinterpret_cast<const tmsize_t*>(data + sizeof(uint32_t)));
    tmsize_t buffer_size = *(reinterpret_cast<const tmsize_t*>(data + sizeof(uint32_t) + sizeof(tmsize_t)));

    // Ensure buffer sizes are non-zero and within reasonable limits
    read_size = read_size > 0 ? read_size : 1;
    buffer_size = buffer_size > 0 ? buffer_size : 1;

    // Allocate buffers
    void *read_buffer = malloc(read_size);
    void *user_buffer = malloc(buffer_size);

    if (read_buffer == nullptr || user_buffer == nullptr) {
        TIFFClose(tiff);
        free(read_buffer);
        free(user_buffer);
        return 0;
    }

    // Call the function-under-test
    TIFFReadFromUserBuffer(tiff, read_offset, read_buffer, read_size, user_buffer, buffer_size);

    // Clean up
    free(read_buffer);
    free(user_buffer);
    TIFFClose(tiff);

    return 0;
}