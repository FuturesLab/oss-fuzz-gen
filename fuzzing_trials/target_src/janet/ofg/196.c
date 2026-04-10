#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include for memcpy
#include <janet.h>

int LLVMFuzzerTestOneInput_196(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to form a valid Janet structure
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Create a Janet object from the input data
    Janet janet_obj;
    memcpy(&janet_obj, data, sizeof(Janet));

    // Call the function-under-test
    JanetTuple result = janet_unwrap_tuple(janet_obj);

    // Optionally, perform some operations with the result to ensure it is used
    if (result != NULL) {
        // For example, get the length of the tuple
        int32_t tuple_length = janet_tuple_length(result);
        (void)tuple_length; // Suppress unused variable warning
    }

    return 0;
}