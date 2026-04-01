#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_390(const uint8_t *data, size_t size) {
    // Ensure the size is at least the size of an int
    if (size < sizeof(int)) {
        return 0;
    }

    // Cast the first bytes of data to an int
    int memory_to_release = *(const int *)data;

    // Call the function-under-test
    sqlite3_release_memory(memory_to_release);

    return 0;
}