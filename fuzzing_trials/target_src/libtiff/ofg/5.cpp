#include <cstdint>
#include <cstdlib>
#include <cstring> // Include this header for memcpy
#include <tiffio.h>

extern "C" {
    #include <tiffio.h> // Ensure TIFFSwabArrayOfFloat is correctly linked
}

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    // Ensure the size is a multiple of sizeof(float) to correctly interpret the data as floats
    if (size % sizeof(float) != 0 || size == 0) {
        return 0;
    }

    // Calculate the number of floats
    tmsize_t num_floats = size / sizeof(float);

    // Allocate memory for the float array
    float *floatArray = static_cast<float *>(malloc(size));

    if (floatArray == nullptr) {
        return 0; // Exit if memory allocation fails
    }

    // Copy the input data into the float array
    memcpy(floatArray, data, size);

    // Call the function-under-test
    TIFFSwabArrayOfFloat(floatArray, num_floats);

    // Clean up allocated memory
    free(floatArray);

    return 0;
}