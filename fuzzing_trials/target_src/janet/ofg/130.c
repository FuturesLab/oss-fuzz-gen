#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_130(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract a Janet and an int32_t
    if (size < sizeof(Janet) + sizeof(int32_t)) {
        return 0;
    }

    // Prepare the Janet pointer
    Janet janet_value;
    janet_value = janet_wrap_integer(*(int32_t *)data); // Assuming the data can be interpreted as an integer

    // Prepare the int32_t index
    int32_t index = *(int32_t *)(data + sizeof(int32_t));

    // Ensure the index is within a valid range
    if (index < 0 || index >= size / sizeof(Janet)) {
        return 0;
    }

    // Call the function-under-test
    uint32_t result = janet_getuinteger(&janet_value, index);

    // Use the result in some way to avoid compiler optimizations
    (void)result;

    return 0;
}