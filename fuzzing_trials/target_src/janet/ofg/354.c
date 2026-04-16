#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <janet.h>

// Fuzzing harness for janet_dictionary_next
int LLVMFuzzerTestOneInput_354(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient to create a JanetKV array
    if (size < sizeof(JanetKV) * 3) {
        return 0;
    }

    // Cast the data to JanetKV pointers
    const JanetKV *dict = (const JanetKV *)data;
    const JanetKV *end = (const JanetKV *)(data + size - sizeof(JanetKV));

    // Initialize index to 0
    int32_t index = 0;

    // Call the function-under-test
    const JanetKV *result = janet_dictionary_next(dict, index, end);

    // Use the result in some way to avoid compiler optimizations removing the call
    if (result != NULL) {
        // Perform some trivial operation
        (void)result->key;
        (void)result->value;
    }

    return 0;
}