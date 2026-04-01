#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>

// Mock sqlite3_context for testing purposes
typedef struct {
    char dummy[8]; // Ensure alignment and size for testing
} MockSqlite3Context;

// Fuzzing function
int LLVMFuzzerTestOneInput_360(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    uint64_t blobSize;

    // Ensure size is at least 8 bytes to extract a uint64_t value
    if (size < sizeof(uint64_t)) {
        return 0;
    }

    // Initialize blobSize from the input data
    memcpy(&blobSize, data, sizeof(uint64_t));

    // Create a mock context
    MockSqlite3Context mockContext;

    // Ensure blobSize is within a reasonable range to avoid excessive allocation
    if (blobSize > 1024 * 1024) { // Limit to 1MB for testing purposes
        return 0;
    }

    // Call the function-under-test with a mock context
    sqlite3_result_zeroblob64((sqlite3_context *)&mockContext, blobSize);

    return 0;
}