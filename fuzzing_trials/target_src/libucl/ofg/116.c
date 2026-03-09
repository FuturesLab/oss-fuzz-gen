#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_116(const uint8_t *data, size_t size) {
    // Initialize variables
    ucl_object_t *obj = ucl_object_fromstring((const char *)data);
    const char *result_str = NULL;
    size_t result_len = 0;

    // Ensure the object is not NULL
    if (obj == NULL) {
        return 0;
    }

    // Call the function-under-test
    bool success = ucl_object_tolstring_safe(obj, &result_str, &result_len);

    // Clean up
    ucl_object_unref(obj);

    return 0;
}