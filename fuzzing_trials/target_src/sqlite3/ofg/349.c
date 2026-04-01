#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_349(const uint8_t *data, size_t size) {
    int control_option;
    void *test_data;

    // Ensure the size is sufficient to extract an integer for control_option
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the data for the control_option
    control_option = *((int *)data);

    // Point test_data to the remaining data, if any
    if (size > sizeof(int)) {
        test_data = (void *)(data + sizeof(int));
    } else {
        // If no remaining data, point to a non-NULL memory location
        test_data = (void *)data;
    }

    // Call the function-under-test
    sqlite3_test_control(control_option, test_data);

    return 0;
}