#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_93(const uint8_t *data, size_t size) {
    // Call the function-under-test
    sqlite3_thread_cleanup();

    return 0;
}