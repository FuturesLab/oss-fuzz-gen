#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_164(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int input_value = 0;
    for (size_t i = 0; i < sizeof(int); ++i) {
        input_value |= data[i] << (i * 8);
    }

    // Call the function-under-test with the extracted integer
    const unsigned char *result = TIFFGetBitRevTable(input_value);

    // Use the result in some way to avoid compiler optimizations removing the call
    if (result != nullptr) {
        // Access the first element to ensure the result is used
        volatile unsigned char first_element = result[0];
        (void)first_element; // Suppress unused variable warning
    }

    return 0;
}