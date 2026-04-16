#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_313(const uint8_t *data, size_t size) {
    // Ensure the size is large enough to create a Janet object
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Create a Janet object from the input data
    Janet janet_obj = janet_wrap_number((double)data[0]);

    // Create a dummy JanetAbstractType
    JanetAbstractType dummy_type = {
        "dummy_type",
        NULL, // no special behavior for abstract type
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

    // Use the result to avoid compiler optimizations
    if (result != NULL) {
        // Perform some dummy operation
        volatile void *dummy = result;
        (void)dummy;
    }

    return 0;
}