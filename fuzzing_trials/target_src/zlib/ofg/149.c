#include <stdint.h>
#include <stddef.h>
#include <inttypes.h> // Include this header for int64_t
#include <zlib.h>

int LLVMFuzzerTestOneInput_149(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract one uLong value
    if (size < sizeof(uLong)) {
        return 0;
    }

    // Extract uLong value1 from the data
    uLong value1 = *(const uLong *)(data);

    // Use the remaining data as the input for the adler32 function
    const uint8_t *data_stream = data + sizeof(uLong);
    size_t data_stream_size = size - sizeof(uLong);

    // Call the adler32 function from zlib
    uLong result = adler32(value1, data_stream, data_stream_size);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    return 0;
}