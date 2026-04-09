#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

// Fuzzing harness for janet_get_abstract_type
int LLVMFuzzerTestOneInput_156(const uint8_t *data, size_t size) {
    // Initialize Janet runtime
    janet_init();

    // Ensure the input size is sufficient to create a Janet object
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Create a Janet object from the input data
    Janet janet_obj;
    memcpy(&janet_obj, data, sizeof(Janet));

    // Call the function-under-test
    const JanetAbstractType *abstract_type = janet_get_abstract_type(janet_obj);

    // Use the result to avoid compiler optimizations removing the call
    if (abstract_type) {
        // Do something trivial with the result
        (void)abstract_type->name;
    }

    // Cleanup Janet runtime
    janet_deinit();

    return 0;
}