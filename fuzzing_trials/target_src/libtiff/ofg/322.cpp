#include <stdint.h>
#include <stddef.h>
#include <tiffio.h>

extern "C" {
    void TIFFReverseBits(uint8_t *, tmsize_t);
}

extern "C" int LLVMFuzzerTestOneInput_322(const uint8_t *data, size_t size) {
    // Allocate a buffer to copy the input data.
    uint8_t *buffer = new uint8_t[size];
    
    // Copy the input data to the buffer.
    for (size_t i = 0; i < size; ++i) {
        buffer[i] = data[i];
    }
    
    // Call the function-under-test.
    TIFFReverseBits(buffer, (tmsize_t)size);
    
    // Clean up.
    delete[] buffer;
    
    return 0;
}