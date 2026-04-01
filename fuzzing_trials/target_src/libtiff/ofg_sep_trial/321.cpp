#include <cstdint>
#include <cstddef>
#include <tiffio.h> // Ensure the TIFF library is included

extern "C" {

// Function signature for the function-under-test
void TIFFReverseBits(uint8_t *data, tmsize_t size);

int LLVMFuzzerTestOneInput_321(const uint8_t *data, size_t size) {
    // Ensure size is not zero to avoid passing NULL to TIFFReverseBits
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the input buffer
    uint8_t *inputData = new uint8_t[size];

    // Copy the fuzzing data into the input buffer
    for (size_t i = 0; i < size; ++i) {
        inputData[i] = data[i];
    }

    // Call the function-under-test
    TIFFReverseBits(inputData, static_cast<tmsize_t>(size));

    // Clean up allocated memory
    delete[] inputData;

    return 0;
}

}