#include <stdint.h>
#include <stddef.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_167(const uint8_t *data, size_t size) {
    // Initialize a ucl_object_t
    ucl_object_t *obj = ucl_object_typed_new(UCL_OBJECT);

    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Use the data as a key
    const char *key = (const char *)data;
    size_t key_length = size;

    // Call the function-under-test
    ucl_object_t *result = ucl_object_pop_keyl(obj, key, key_length);

    // Clean up
    if (result != NULL) {
        ucl_object_unref(result);
    }
    ucl_object_unref(obj);

    return 0;
}