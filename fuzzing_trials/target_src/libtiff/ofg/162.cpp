#include <cstdint>
#include <cstddef>
#include <cmath>
#include <iostream>

extern "C" {
    // Declare the function-under-test
    int LogL10fromY(double, int);
}

extern "C" int LLVMFuzzerTestOneInput_162(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract a double and an int
    if (size < sizeof(double) + sizeof(int)) {
        return 0;
    }

    // Extract a double from the input data
    double inputDouble;
    std::memcpy(&inputDouble, data, sizeof(double));

    // Extract an int from the input data
    int inputInt;
    std::memcpy(&inputInt, data + sizeof(double), sizeof(int));

    // Call the function-under-test
    int result = LogL10fromY(inputDouble, inputInt);

    // Print the result for debugging purposes (optional)
    std::cout << "LogL10fromY(" << inputDouble << ", " << inputInt << ") = " << result << std::endl;

    return 0;
}