#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    // Ensure that the size is at least the size of a Janet object
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Initialize the Janet environment
    janet_init();

    // Create a Janet object from the input data
    Janet janet_obj = janet_wrap_nil(); // Initialize as a valid Janet object
    memcpy(&janet_obj, data, sizeof(Janet));

    // Ensure that the index is within a reasonable range
    int32_t index = 0;
    if (size > sizeof(Janet)) {
        index = (int32_t)data[sizeof(Janet)] % 10; // Limit index to a small range
    }

    // Check if the Janet object is a valid dictionary
    if (janet_checktype(janet_obj, JANET_TABLE)) {
        // Call the function-under-test
        JanetDictView result = janet_getdictionary(&janet_obj, index); // Take the address of janet_obj

        // Use the result in a way that avoids compiler optimizations
        // (e.g., by printing or otherwise processing it)
        // In this case, we'll simply return 0 as there's no further processing needed
    }

    // Deinitialize the Janet environment
    janet_deinit();

    return 0;
}