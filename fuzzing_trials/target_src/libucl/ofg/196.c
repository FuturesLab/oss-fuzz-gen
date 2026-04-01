#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_196(const uint8_t *data, size_t size) {
    // Call the function-under-test
    ucl_object_t *obj = ucl_object_new();

    // Simulate usage of the created object
    if (obj != NULL) {
        // Example of feeding non-null input to the function under test
        // Adjust the number of arguments to match the function declaration
        ucl_object_fromstring_common((const char *)data, size, 0);

        // Free the object after use
        ucl_object_unref(obj);
    }

    return 0;
}