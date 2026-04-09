#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy
#include <janet.h>

// Initialize the Janet VM
__attribute__((constructor))
static void initialize_janet_vm(void) {
    janet_init();
}

int LLVMFuzzerTestOneInput_289(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create a Janet number
    if (size < sizeof(double)) {
        return 0;
    }

    // Create a Janet number from the input data
    double num;
    memcpy(&num, data, sizeof(double));
    Janet janet_num = janet_wrap_number(num);

    // Call the function-under-test
    double result = janet_unwrap_number(janet_num);

    // Use the result to prevent optimization
    volatile double prevent_optimization = result;
    (void)prevent_optimization;

    return 0;
}