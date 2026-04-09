#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_84(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a Janet object and an index
    if (size < sizeof(Janet) + sizeof(int32_t)) {
        return 0;
    }

    // Initialize a Janet object from the data
    Janet janet_obj;
    memcpy(&janet_obj, data, sizeof(Janet));

    // Extract an int32_t index from the remaining data
    int32_t index;
    memcpy(&index, data + sizeof(Janet), sizeof(int32_t));

    // Ensure the Janet object is a valid Janet string
    if (!janet_checktype(janet_obj, JANET_STRING)) {
        return 0;
    }

    // Call the function-under-test
    JanetString result = janet_getstring(&janet_obj, index);

    // Use the result in some way to avoid compiler optimizing it away
    if (result != NULL) {
        // Do something with the result, like printing or logging
        // For the purpose of fuzzing, we just ensure the function is called
    }

    return 0;
}