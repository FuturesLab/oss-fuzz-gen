#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_68(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0; // Not enough data to proceed
    }

    // Initialize the first ucl_object_t
    ucl_object_t *obj1 = ucl_object_typed_new(UCL_OBJECT);

    // Initialize the second ucl_object_t
    ucl_object_t *obj2 = ucl_object_typed_new(UCL_OBJECT);

    // Use the first byte of data as a boolean value
    bool insert_duplicate = data[0] % 2 == 0;

    // Use the rest of the data as a key
    const char *key = (const char *)(data + 1);
    size_t key_length = size - 1;

    // Call the function under test
    ucl_object_insert_key(obj1, obj2, key, key_length, insert_duplicate);

    // Clean up
    ucl_object_unref(obj1);
    ucl_object_unref(obj2);

    return 0;
}