#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_333(const uint8_t *data, size_t size) {
    int enable = 0;

    if (size > 0) {
        // Use the first byte of data to determine the value of enable
        enable = data[0] % 2; // This will give either 0 or 1
    }

    // Call the function-under-test
    sqlite3_enable_shared_cache(enable);

    return 0;
}

#ifdef __cplusplus
}
#endif