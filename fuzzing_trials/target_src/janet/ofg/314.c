#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_314(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for creating a Janet structure
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Initialize the Janet environment
    janet_init();

    // Create a Janet object from the input data
    Janet janet_obj = janet_wrap_number((double)data[0]);

    // Define a dummy JanetAbstractType
    JanetAbstractType dummy_type = {
        "dummy_type",
        NULL, // No specific functions for the dummy type
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    };

    // Call the function-under-test
    JanetAbstract result = janet_checkabstract(janet_obj, &dummy_type);

    // Clean up the Janet environment
    janet_deinit();

    return 0;
}