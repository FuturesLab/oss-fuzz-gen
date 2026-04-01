#include <ucl.h> // Corrected the path to the UCL library header
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Initialize an integer to store the result
    int64_t result = 0;

    // Create a ucl_object_t from the input data
    ucl_object_t *obj = ucl_object_fromstring_common((const char *)data, size, UCL_STRING_RAW);

    if (obj == NULL) {
        return 0;
    }

    // Call the function-under-test
    bool success = ucl_object_toint_safe(obj, &result);

    // Clean up
    ucl_object_unref(obj);

    return 0;
}