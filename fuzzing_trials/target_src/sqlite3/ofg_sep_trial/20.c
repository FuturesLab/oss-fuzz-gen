#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    int64_t heap_limit;

    // Ensure there is enough data to read an integer
    if (size < sizeof(int64_t)) {
        return 0;
    }

    // Copy the first few bytes of data into an integer for heap_limit
    heap_limit = *(const int64_t*)data;

    // Call the function-under-test
    sqlite3_soft_heap_limit64(heap_limit);

    return 0;
}

#ifdef __cplusplus
}
#endif