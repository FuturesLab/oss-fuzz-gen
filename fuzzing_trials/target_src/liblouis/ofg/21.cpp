#include <stdint.h>
#include <stddef.h>

// Assuming logLevels is an enum or a similar type
typedef enum {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL
} logLevels;

extern "C" {
    // Function-under-test
    void lou_setLogLevel(logLevels level);
}

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Ensure there's at least one byte to read
    if (size < 1) {
        return 0;
    }

    // Use the first byte of data to determine the log level
    uint8_t level_index = data[0] % 5; // Assuming there are 5 log levels
    logLevels level = static_cast<logLevels>(level_index);

    // Call the function-under-test
    lou_setLogLevel(level);

    return 0;
}