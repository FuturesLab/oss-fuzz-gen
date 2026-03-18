#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int arg = *(const int *)data;

    // Call the function-under-test
    sqlite3_int64 result = sqlite3_memory_highwater(arg);

    // Use the result in some way, e.g., print it (optional)
    // printf("Highwater mark: %lld\n", result);

    return 0;
}