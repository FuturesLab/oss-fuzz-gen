#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy
#include <janet.h>

// Initialize the Janet VM
__attribute__((constructor))
static void initialize_janet_308() {
    janet_init();
}

int LLVMFuzzerTestOneInput_308(const uint8_t *data, size_t size) {
    // Ensure the size is enough to create a Janet object
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Create a Janet object from the input data
    Janet janet_value;
    memcpy(&janet_value, data, sizeof(Janet));

    // Call the function-under-test
    JanetArray *result = janet_unwrap_array(janet_value);

    // Perform any necessary cleanup
    // Note: In this case, no specific cleanup is needed for JanetArray

    return 0;
}