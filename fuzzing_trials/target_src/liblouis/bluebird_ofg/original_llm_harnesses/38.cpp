#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" {
    // Function-under-test declaration
    void lou_logPrint(const char *message, void *userData);
}

extern "C" int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
    // Ensure that the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the message and ensure it's null-terminated
    char *message = new char[size + 1];
    std::memcpy(message, data, size);
    message[size] = '\0';

    // Dummy user data, as the function signature requires a void pointer
    int dummyData = 42;
    void *userData = static_cast<void*>(&dummyData);

    // Call the function-under-test
    lou_logPrint(message, userData);

    // Clean up allocated memory
    delete[] message;

    return 0;
}