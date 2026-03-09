#include <stdint.h>
#include <stddef.h>
#include <ucl.h>
#include <string.h>

int LLVMFuzzerTestOneInput_167(const uint8_t *data, size_t size) {
    // Initialize a ucl_object_t object
    ucl_object_t *obj = ucl_object_typed_new(UCL_OBJECT);

    // Ensure there is data to be used as a key
    if (size == 0) {
        ucl_object_unref(obj);
        return 0;
    }

    // Use the input data as a key
    const char *key = (const char *)data;
    size_t key_len = size;

    // Add a dummy key-value pair to the object
    ucl_object_insert_key(obj, ucl_object_fromstring("dummy_value"), "dummy_key", 0, false);

    // Call the function-under-test
    ucl_object_t *result = ucl_object_pop_keyl(obj, key, key_len);

    // Clean up
    if (result != NULL) {
        ucl_object_unref(result);
    }
    ucl_object_unref(obj);

    return 0;
}