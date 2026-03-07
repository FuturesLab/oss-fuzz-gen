#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib>  // Include for std::rand and std::srand
#include <ctime>    // Include for std::time

extern "C" {
    // Include the header where magic_getpath is declared
    const char * magic_getpath(const char *, int);
}

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    // Ensure size is greater than 0 to have at least one byte for the string
    if (size == 0) {
        return 0;
    }

    // Seed the random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Create a buffer to hold the input data as a string
    char *inputString = new char[size + 1];
    std::memcpy(inputString, data, size);
    inputString[size] = '\0'; // Null-terminate the string

    // Use a random integer value for the second parameter
    int someIntValue = std::rand() % 100; // Limit the range for more predictable behavior

    // Call the function-under-test
    const char *result = magic_getpath(inputString, someIntValue);

    // Check if result is not null to ensure the function is being utilized
    if (result != nullptr) {
        // Do something with result if needed, for example, check its length
        volatile size_t resultLength = std::strlen(result);
        (void)resultLength; // Suppress unused variable warning

        // Additional check: print or log the result for debugging
        // This can help understand what kind of inputs lead to different outputs
        // For fuzzing, this might be redirected to a log file or a debugger
        // printf("Result: %s\n", result); // Uncomment if needed for debugging
    }

    // Clean up
    delete[] inputString;

    return 0;
}