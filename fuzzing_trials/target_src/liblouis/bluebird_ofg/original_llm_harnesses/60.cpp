#include <cstdint>
#include <cstddef>
#include <cstring>

extern "C" {
    void lou_logFile(const char *);
}

extern "C" int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated and non-empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for a null-terminated string
    char *logFileName = new char[size + 1];
    if (logFileName == nullptr) {
        return 0;
    }

    // Copy the input data to the logFileName and null-terminate it
    std::memcpy(logFileName, data, size);
    logFileName[size] = '\0';

    // Call the function under test
    lou_logFile(logFileName);

    // Clean up
    delete[] logFileName;

    return 0;
}