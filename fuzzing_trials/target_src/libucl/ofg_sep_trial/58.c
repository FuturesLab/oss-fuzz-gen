#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    // Ensure the data is not NULL and size is greater than zero
    if (data == NULL || size == 0) {
        return 0;
    }

    // Call the function-under-test
    ucl_object_t *obj = ucl_object_fromlstring((const char *)data, size);

    // Free the object if it was successfully created
    if (obj != NULL) {
        ucl_object_unref(obj);
    }

    return 0;
}