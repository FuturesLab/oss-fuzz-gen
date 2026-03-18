#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_259(const uint8_t *data, size_t size) {
    // Call the function-under-test
    int keyword_count = sqlite3_keyword_count();

    // Use the result in some way to avoid compiler optimizations removing the call
    if (keyword_count > 0) {
        // Do something trivial with the result
        volatile int dummy = keyword_count;
        (void)dummy;
    }

    return 0;
}