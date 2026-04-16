#include "janet.h"

extern JanetAbstract janet_checkfile(Janet);

int LLVMFuzzerTestOneInput_1423(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Initialize Janet VM
    janet_init();

    // Create a Janet string from the input data
    Janet input_string = janet_stringv(data, size);

    // Call the function-under-test
    JanetAbstract result = janet_checkfile(input_string);

    // Clean up Janet VM
    janet_deinit();

    return 0;
}