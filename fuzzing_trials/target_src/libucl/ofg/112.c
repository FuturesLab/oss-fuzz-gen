#include <stdint.h>
#include <stdbool.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_112(const uint8_t *data, size_t size) {
    // Ensure the input is large enough to initialize the parameters
    if (size < sizeof(int)) {
        return 0;
    }

    // Initialize the parameters for the function
    ucl_object_t *obj = ucl_object_fromstring("test");
    ucl_object_iter_t iter = ucl_object_iterate_new(obj);
    bool expand_values = true;
    int error_code = 0;

    // Call the function-under-test
    const ucl_object_t *result = ucl_object_iterate_with_error(obj, &iter, expand_values, &error_code);

    // Clean up
    ucl_object_iterate_free(iter);
    ucl_object_unref(obj);

    return 0;
}