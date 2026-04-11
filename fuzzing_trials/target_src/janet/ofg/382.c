#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_382(const uint8_t *data, size_t size) {
    if (size < sizeof(void *)) {
        return 0;
    }

    // Create a Janet object from the input data
    Janet janet_value;

    // Ensure the data size is enough for a pointer
    void *ptr = (void *)data;
    janet_value = janet_wrap_pointer(ptr);

    // Call the function-under-test
    void *result = janet_unwrap_pointer(janet_value);

    // To avoid unused variable warning
    (void)result;

    return 0;
}