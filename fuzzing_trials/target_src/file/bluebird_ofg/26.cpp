extern "C" {
    #include "magic.h"
    #include "stddef.h"
    #include "stdint.h"
    #include "stdlib.h" // For malloc and free
    #include <string.h> // For memcpy
}

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    struct magic_set *magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        return 0;
    }

    // Ensure data is not null and has enough size to be used as a parameter
    if (size < sizeof(int) + 1) { // Ensure there's at least one byte for value
        magic_close(magic);
        return 0;
    }

    // Use the first part of data as an integer parameter
    int param = *(const int *)data;
    const void *value = data + sizeof(int);

    // Ensure value is not null and size is valid for the function
    // The value should be a valid pointer to a null-terminated string.
    // Therefore, ensure the remaining data is null-terminated.
    size_t remaining_size = size - sizeof(int);
    char *null_terminated_value = (char *)malloc(remaining_size + 1);
    if (null_terminated_value == NULL) {
        magic_close(magic);
        return 0;
    }
    memcpy(null_terminated_value, value, remaining_size);
    null_terminated_value[remaining_size] = '\0'; // Null-terminate

    // Call the function under test
    // Check if the param is a valid magic parameter type
    if (param >= MAGIC_PARAM_INDIR_MAX && param <= MAGIC_PARAM_NAME_MAX) {
        if (magic_setparam(magic, param, null_terminated_value) != 0) {
            // Handle error if magic_setparam fails
            free(null_terminated_value);
            magic_close(magic);
            return 0;
        }
    }

    // Clean up
    free(null_terminated_value);
    magic_close(magic);
    return 0;
}