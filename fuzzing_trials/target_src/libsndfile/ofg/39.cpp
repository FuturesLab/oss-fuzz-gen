#include <cstdint>
#include <cstddef>
#include <iostream>

extern "C" {
    // Assuming the function is defined in an external C library
    const char * sf_error_number(int);
}

extern "C" int LLVMFuzzerTestOneInput_39(const uint8_t *data, size_t size) {
    // Ensure there's enough data to construct an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int error_number = 0;
    for (size_t i = 0; i < sizeof(int); ++i) {
        error_number |= data[i] << (i * 8);
    }

    // Call the function-under-test
    const char *error_message = sf_error_number(error_number);

    // Optionally print the result for debugging purposes
    if (error_message != nullptr) {
        std::cout << "Error number: " << error_number << ", Message: " << error_message << std::endl;
    }

    return 0;
}