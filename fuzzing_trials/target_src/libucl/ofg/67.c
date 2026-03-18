#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_67(const uint8_t *data, size_t size) {
    if (size < 2) return 0; // Ensure there's at least one byte for the key and one for the boolean

    // Initialize ucl_object_t structures
    ucl_object_t *top = ucl_object_typed_new(UCL_OBJECT);
    ucl_object_t *value = ucl_object_fromstring("test_value");

    // Use the first byte of data as the boolean value
    bool insert_duplicate = data[0] % 2 == 0;

    // Use the remaining data as the key
    const char *key = (const char *)(data + 1);
    size_t key_length = size - 1;

    // Call the function under test
    ucl_object_insert_key(top, value, key, key_length, insert_duplicate);

    // Clean up
    ucl_object_unref(top);
    ucl_object_unref(value);

    return 0;
}