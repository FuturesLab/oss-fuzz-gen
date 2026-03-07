#include <stdint.h>
#include <stdlib.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_104(const uint8_t *data, size_t size) {
    // Initialize a ucl_object_t
    ucl_object_t *obj = ucl_object_new();

    // Check if the object was created successfully
    if (obj == NULL) {
        return 0;
    }

    // Add some dummy data to the ucl_object_t
    ucl_object_insert_key(obj, ucl_object_fromstring("value1"), "key1", 0, false);
    ucl_object_insert_key(obj, ucl_object_fromstring("value2"), "key2", 0, false);

    // Define a ucl_object_t sort flag
    enum ucl_object_keys_sort_flags sort_flag = UCL_SORT_KEYS_DEFAULT;

    // Call the function-under-test
    ucl_object_sort_keys(obj, sort_flag);

    // Clean up
    ucl_object_unref(obj);

    return 0;
}