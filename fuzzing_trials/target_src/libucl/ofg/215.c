#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_215(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to extract an unsigned int for priority
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Create a new ucl_object_t
    ucl_object_t *obj = ucl_object_new();

    // Extract an unsigned int for priority from the input data
    unsigned int priority = *((unsigned int *)data);

    // Call the function-under-test
    ucl_object_set_priority(obj, priority);

    // Clean up
    ucl_object_unref(obj);

    return 0;
}