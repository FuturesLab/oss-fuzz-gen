#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
    // Ensure we have enough data to construct an int
    if (size < sizeof(int)) {
        return 0;
    }

    // Interpret the first bytes of data as an int
    int heap_limit = *(const int*)data;

    // Call the function-under-test with the interpreted int
    sqlite3_soft_heap_limit(heap_limit);

    return 0;
}