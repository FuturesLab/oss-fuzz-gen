#include <ucl.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

int LLVMFuzzerTestOneInput_69(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for our needs
    if (size < 3) {
        return 0;
    }

    // Initialize variables
    ucl_object_t *top = ucl_object_typed_new(UCL_OBJECT);
    ucl_object_t *value = ucl_object_typed_new(UCL_STRING);

    // Use the first byte of data to determine the boolean value
    bool replace = data[0] % 2 == 0;

    // Use the remaining data as the key
    const char *key = (const char *)(data + 1);
    size_t key_len = size - 1;

    // Insert the key-value pair into the UCL object
    ucl_object_insert_key(top, value, key, key_len, replace);

    // Clean up
    ucl_object_unref(top);
    ucl_object_unref(value);

    return 0;
}