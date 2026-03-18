#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_216(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient for extracting a priority value
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Create a new UCL object
    ucl_object_t *ucl_obj = ucl_object_new();

    // Extract an unsigned int from the data for the priority
    unsigned int priority = *((unsigned int *)data);

    // Call the function-under-test
    ucl_object_set_priority(ucl_obj, priority);

    // Clean up
    ucl_object_unref(ucl_obj);

    return 0;
}