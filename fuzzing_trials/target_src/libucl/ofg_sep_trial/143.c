#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_143(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    ucl_object_t *top_obj = ucl_object_typed_new(UCL_OBJECT);
    ucl_object_t *new_obj;
    const char *key = "test_key";
    size_t keylen = strlen(key);
    bool merge = true;

    // Ensure that the data is large enough to be used meaningfully
    if (size > 0) {
        // Use the data to create a UCL object
        new_obj = ucl_object_fromstring_common((const char *)data, size, UCL_STRING_TRIM);

        // Call the function-under-test
        bool result = ucl_object_insert_key_merged(top_obj, new_obj, key, keylen, merge);

        // Use result for further operations if needed
    }

    // Clean up
    ucl_object_unref(top_obj);
    ucl_object_unref(new_obj);

    return 0;
}