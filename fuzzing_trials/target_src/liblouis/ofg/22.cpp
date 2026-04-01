#include <cstdint>
#include <cstdlib>

// Assuming logLevels is an enum or a similar type
typedef int logLevels;

// Function prototype for the function-under-test
extern "C" void lou_setLogLevel(logLevels level);

extern "C" int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    // Declare and initialize logLevel variable
    logLevels level = 0;

    // Make sure the size is large enough to extract a log level
    if (size >= sizeof(logLevels)) {
        // Copy the data into the logLevels variable
        level = *reinterpret_cast<const logLevels*>(data);
    }

    // Call the function-under-test
    lou_setLogLevel(level);

    return 0;
}