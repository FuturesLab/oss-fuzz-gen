#include <stdint.h>
#include <stddef.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract a ucl_type_t value
    if (size < sizeof(ucl_type_t)) {
        return 0;
    }

    // Cast the input data to a ucl_type_t
    ucl_type_t type = *(ucl_type_t *)data;

    // Call the function-under-test
    const char *type_str = ucl_object_type_to_string(type);

    // Use the returned string in some way to prevent compiler optimizations
    // from removing the call (e.g., by checking if it's not NULL)
    if (type_str != NULL) {
        // Do something trivial with type_str, such as printing or logging
        // In this case, we'll just check its length
        size_t len = 0;
        while (type_str[len] != '\0') {
            len++;
        }
    }

    return 0;
}