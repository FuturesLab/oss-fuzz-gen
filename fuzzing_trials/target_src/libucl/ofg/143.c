#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <ucl.h>
#include <string.h>

int LLVMFuzzerTestOneInput_143(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    ucl_object_t *top = ucl_object_typed_new(UCL_OBJECT);
    ucl_object_t *obj = ucl_object_typed_new(UCL_OBJECT);
    const char *key = "example_key";
    size_t keylen = strlen(key);
    bool merge = true;

    // Ensure the data is not NULL and has a reasonable size
    if (size > 0 && data != NULL) {
        // Insert the data into the object
        ucl_object_t *data_obj = ucl_object_fromstring((const char *)data);
        ucl_object_insert_key_merged(top, data_obj, key, keylen, merge);
    }

    // Clean up
    ucl_object_unref(top);
    ucl_object_unref(obj);

    return 0;
}