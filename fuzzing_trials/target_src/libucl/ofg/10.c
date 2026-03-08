#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "/src/libucl/include/ucl.h"

int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    ucl_object_t *top_obj = ucl_object_typed_new(UCL_OBJECT);
    ucl_object_t *new_obj = NULL;
    const char *key = "test_key";
    size_t keylen = strlen(key);
    bool copy_key = true;

    // Check if the provided data size is sufficient to prevent buffer overflows
    if (size > 0) {
        // Convert data to a string and set it as the value of new_obj
        char *value = (char *)malloc(size + 1);
        if (value != NULL) {
            memcpy(value, data, size);
            value[size] = '\0'; // Null-terminate the string
            new_obj = ucl_object_fromstring(value); // Create a new UCL object from the string
            free(value);
        }
    }

    // Call the function-under-test
    if (new_obj != NULL) {
        bool result = ucl_object_insert_key(top_obj, new_obj, key, keylen, copy_key);
    }

    // Clean up
    ucl_object_unref(top_obj);

    return 0;
}