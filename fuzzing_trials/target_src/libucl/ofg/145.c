#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_145(const uint8_t *data, size_t size) {
    // Ensure that the input data is null-terminated
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0; // Handle memory allocation failure
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    ucl_type_t type;
    // Call the function-under-test
    ucl_object_string_to_type(null_terminated_data, &type);

    // Clean up
    free(null_terminated_data);
    return 0;
}