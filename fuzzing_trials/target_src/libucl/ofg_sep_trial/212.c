#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_212(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to extract an unsigned int for priority
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Create a new UCL object
    ucl_object_t *obj = ucl_object_new();

    // Extract an unsigned int from the data for priority
    unsigned int priority = *(unsigned int *)data;

    // Call the function-under-test
    ucl_object_set_priority(obj, priority);

    // Clean up the UCL object
    ucl_object_unref(obj);

    return 0;
}