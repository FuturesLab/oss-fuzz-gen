#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_144(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for splitting into meaningful parts
    if (size < 2) {
        return 0;
    }

    // Initialize ucl_object_t pointers
    ucl_object_t *obj1 = ucl_object_new();
    ucl_object_t *obj2 = ucl_object_new();

    // Use the first byte to determine the boolean value
    bool merge = data[0] % 2;

    // Use the remaining bytes as a key
    const char *key = (const char *)(data + 1);
    size_t key_len = size - 1;

    // Call the function under test
    ucl_object_insert_key_merged(obj1, obj2, key, key_len, merge);

    // Clean up
    ucl_object_unref(obj1);
    ucl_object_unref(obj2);

    return 0;
}