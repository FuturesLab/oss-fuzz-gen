#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    ucl_object_t *top_obj = ucl_object_typed_new(UCL_OBJECT);
    ucl_object_t *new_obj = ucl_object_typed_new(UCL_OBJECT);
    const char *key = "test_key";
    size_t keylen = strlen(key);
    bool copy_key = true;

    // Ensure data is not empty
    if (size > 0) {
        // Use data as input for new_obj
        ucl_object_fromstring_common((const char *)data, size, UCL_STRING_RAW);
    }

    // Call the function-under-test
    bool result = ucl_object_replace_key(top_obj, new_obj, key, keylen, copy_key);

    // Clean up
    ucl_object_unref(top_obj);
    ucl_object_unref(new_obj);

    return 0;
}