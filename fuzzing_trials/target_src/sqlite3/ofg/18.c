#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    int limit;

    // Ensure the size is sufficient to extract an int
    if (size < sizeof(int)) {
        return 0;
    }

    // Copy data into an int variable to use as the heap limit
    limit = *(const int*)data;

    // Call the function-under-test
    sqlite3_soft_heap_limit64(limit);

    return 0;
}