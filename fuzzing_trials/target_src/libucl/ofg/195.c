#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_195(const uint8_t *data, size_t size) {
    // Call the function-under-test
    ucl_object_t *obj = ucl_object_new();

    // Perform operations with the created object if needed
    // For this example, we will just check if the object is not NULL
    if (obj != NULL) {
        // Normally, you would perform additional operations with 'obj' here

        // Free the object after use
        ucl_object_unref(obj);
    }

    return 0;
}