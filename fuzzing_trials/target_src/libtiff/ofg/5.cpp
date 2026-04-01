extern "C" {
    #include <tiffio.h>
    #include <stdlib.h>
    #include <string.h>  // Include string.h for memcpy
}

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    // Ensure the size is a multiple of the size of float
    if (size % sizeof(float) != 0) {
        return 0;
    }

    // Calculate the number of floats
    tmsize_t num_floats = static_cast<tmsize_t>(size / sizeof(float));

    // Allocate memory for the float array
    float *float_array = static_cast<float *>(malloc(size));
    if (float_array == NULL) {
        return 0;
    }

    // Copy data into the float array
    memcpy(float_array, data, size);

    // Call the function-under-test
    TIFFSwabArrayOfFloat(float_array, num_floats);

    // Free the allocated memory
    free(float_array);

    return 0;
}