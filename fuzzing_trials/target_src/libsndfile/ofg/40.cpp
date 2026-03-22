#include <cstdint>
#include <cstddef>

// Assuming the function is part of a C library
extern "C" {
    const char * sf_error_number(int);
}

extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    // Initialize an integer from the input data
    int error_code = 0;

    // If size is at least 4, use the first 4 bytes to form the integer
    if (size >= 4) {
        error_code = static_cast<int>(data[0]) |
                     (static_cast<int>(data[1]) << 8) |
                     (static_cast<int>(data[2]) << 16) |
                     (static_cast<int>(data[3]) << 24);
    }

    // Call the function-under-test
    const char *error_message = sf_error_number(error_code);

    // Normally, you would do something with error_message, but for fuzzing, just return
    (void)error_message; // Suppress unused variable warning

    return 0;
}