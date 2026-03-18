#include <ucl.h>
#include <stdint.h>
#include <stddef.h>
#include "/src/libucl/include/ucl.h"

int LLVMFuzzerTestOneInput_182(const uint8_t *data, size_t size) {
    // Initialize two ucl_object_t objects
    ucl_object_t *obj1 = ucl_object_new();
    ucl_object_t *obj2 = ucl_object_new();

    // Ensure both objects are not NULL
    if (obj1 == NULL || obj2 == NULL) {
        if (obj1 != NULL) ucl_object_unref(obj1);
        if (obj2 != NULL) ucl_object_unref(obj2);
        return 0;
    }

    // Use the data to set some values in the objects
    ucl_object_t *key1_value = ucl_object_fromstring((const char *)data);
    ucl_object_t *key2_value = ucl_object_fromstring((const char *)data);

    if (key1_value != NULL && key2_value != NULL) {
        ucl_object_insert_key(obj1, key1_value, "key1", 0, false);
        ucl_object_insert_key(obj2, key2_value, "key2", 0, false);

        // Call the function under test
        ucl_object_t *result = ucl_elt_append(obj1, obj2);

        // Clean up
        if (result != NULL) {
            ucl_object_unref(result);
        }
    } else {
        if (key1_value != NULL) ucl_object_unref(key1_value);
        if (key2_value != NULL) ucl_object_unref(key2_value);
    }

    ucl_object_unref(obj1);
    ucl_object_unref(obj2);

    return 0;
}