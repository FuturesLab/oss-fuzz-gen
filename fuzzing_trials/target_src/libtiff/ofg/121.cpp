#include <cstdint>
#include <cstdlib>
#include <iostream>

extern "C" {
    // Assuming the function is defined somewhere in a C library
    double LogL10toY(int);
}

extern "C" int LLVMFuzzerTestOneInput_121(const uint8_t *data, size_t size) {
    if (size < sizeof(int)) {
        return 0; // Not enough data to form an int
    }

    // Convert the first 4 bytes of data into an int
    int input_value = 0;
    for (size_t i = 0; i < sizeof(int); ++i) {
        input_value |= (data[i] << (i * 8));
    }

    // Call the function-under-test
    double result = LogL10toY(input_value);

    // Optionally print the result for debugging purposes
    std::cout << "LogL10toY(" << input_value << ") = " << result << std::endl;

    return 0;
}