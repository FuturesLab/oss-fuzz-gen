#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

extern int LLVMFuzzerTestOneInput_95(const uint8_t *data, size_t size) {
    // The function sqlite3_thread_cleanup does not take any parameters and does not return a value.
    // Thus, we can directly call it in the fuzzer test function.
    sqlite3_thread_cleanup();

    // Return 0 to indicate successful execution of the fuzzer test.
    return 0;
}