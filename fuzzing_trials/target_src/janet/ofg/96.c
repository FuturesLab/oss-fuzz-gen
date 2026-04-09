#include <stdint.h>
#include <stddef.h>
#include <janet.h>

// Define a simple Janet object for fuzzing
Janet create_fuzz_janet_object(const uint8_t *data, size_t size) {
    // Ensure the size is at least the size of a Janet integer
    if (size >= sizeof(int32_t)) {
        // Use the first few bytes to create a Janet integer
        int32_t value = *((int32_t *)data);
        return janet_wrap_integer(value);
    } else {
        // Default to a Janet nil if size is insufficient
        return janet_wrap_nil();
    }
}

int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
    // Create a Janet object using the fuzzing data
    Janet janet_obj = create_fuzz_janet_object(data, size);

    // Call the function-under-test
    janet_gcroot(janet_obj);

    return 0;
}