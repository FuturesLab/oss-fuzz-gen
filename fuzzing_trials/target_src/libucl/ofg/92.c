#include <stddef.h>
#include <stdint.h>
#include <ucl.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_92(const uint8_t *data, size_t size) {
    // Ensure that the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Cast the input data to a string
    const char *input_string = (const char *)data;

    // Define a non-zero string flag for testing
    ucl_string_flags_t flags = UCL_STRING_RAW;

    // Call the function-under-test
    ucl_object_t *result = ucl_object_fromstring_common(input_string, size, flags);

    // Clean up the result if it's not NULL
    if (result != NULL) {
        ucl_object_unref(result);
    }

    return 0;
}

#ifdef __cplusplus
}
#endif