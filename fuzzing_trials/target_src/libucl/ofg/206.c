#include "ucl.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_206(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated
    if (size == 0) {
        return 0;
    }

    // Allocate a buffer that is one byte larger than the input size
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0;
    }

    // Copy the input data into the buffer and null-terminate it
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Call the function under test
    ucl_object_t *obj = ucl_object_fromstring(null_terminated_data);

    // Free the allocated buffer
    free(null_terminated_data);

    // If the function returns a non-NULL object, free it
    if (obj != NULL) {
        ucl_object_unref(obj);
    }

    return 0;
}