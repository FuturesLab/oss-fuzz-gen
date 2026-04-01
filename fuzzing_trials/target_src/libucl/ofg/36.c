#include <stdint.h>
#include <stddef.h>
#include <ucl.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    // Initialize variables for the function-under-test
    ucl_object_iter_t iter = (ucl_object_iter_t)data; // Use data as an initial iterator value
    ucl_object_t *obj = ucl_object_fromstring("test_object"); // Create a non-NULL ucl_object_t

    // Call the function-under-test
    ucl_object_iter_t result = ucl_object_iterate_reset(iter, obj);

    // Clean up
    ucl_object_unref(obj);

    return 0;
}

#ifdef __cplusplus
}
#endif