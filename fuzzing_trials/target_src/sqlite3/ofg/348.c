#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_348(const uint8_t *data, size_t size) {
    // Ensure there is enough data for both the integer and the void pointer
    if (size < sizeof(int) + sizeof(void*)) {
        return 0;
    }

    // Extract an integer from the data
    int control_type = *(const int*)data;

    // Advance the data pointer past the integer
    data += sizeof(int);
    size -= sizeof(int);

    // Use the remaining data as a pointer-like value
    void* ptr_value = (void*)data;

    // Call the function-under-test
    sqlite3_test_control(control_type, ptr_value);

    return 0;
}