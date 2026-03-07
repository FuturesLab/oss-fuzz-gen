#include "ucl.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient to create a valid string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *input_str = (char *)malloc(size + 1);
    if (input_str == NULL) {
        return 0;
    }
    memcpy(input_str, data, size);
    input_str[size] = '\0';

    // Create a ucl_object_t from the string
    ucl_object_t *ucl_obj = ucl_object_fromstring(input_str);
    free(input_str);

    // Prepare a pointer for the resulting string
    const char *result_str = NULL;

    // Call the function-under-test
    bool success = ucl_object_tostring_safe(ucl_obj, &result_str);

    // Clean up
    ucl_object_unref(ucl_obj);

    return 0;
}