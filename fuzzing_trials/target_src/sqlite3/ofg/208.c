#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_208(const uint8_t *data, size_t size) {
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the data
    int config_option = *((int*)data);

    // Create a non-NULL void pointer
    int dummy_value = 42;
    void *dummy_ptr = &dummy_value;

    // Call the function-under-test
    sqlite3_config(config_option, dummy_ptr);

    return 0;
}