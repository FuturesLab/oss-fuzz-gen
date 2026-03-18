#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_334(const uint8_t *data, size_t size) {
    int cache_setting;

    // Ensure the size is sufficient to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer value from the input data
    cache_setting = *(const int *)data;

    // Call the function-under-test with the extracted integer
    sqlite3_enable_shared_cache(cache_setting);

    return 0;
}