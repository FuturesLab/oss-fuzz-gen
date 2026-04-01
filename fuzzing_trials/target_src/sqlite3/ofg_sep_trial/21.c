#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Ensure we have enough data to read an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Use the first bytes of data to set the heap limit
    int heap_limit = *((int*)data);

    // Call the function-under-test
    sqlite3_soft_heap_limit(heap_limit);

    return 0;
}