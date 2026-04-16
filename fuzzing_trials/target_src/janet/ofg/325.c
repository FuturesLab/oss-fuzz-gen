#include <stdint.h>
#include <stddef.h>
#include <janet.h>
#include <string.h>
#include <stdlib.h> // Include for malloc and free

int LLVMFuzzerTestOneInput_325(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for the parameters
    if (size < sizeof(Janet) + sizeof(int32_t) * 2 + 1) {
        return 0;
    }

    // Initialize parameters
    Janet janet_array[1]; // Ensure there is at least one Janet element
    memcpy(janet_array, data, sizeof(Janet));
    int32_t n = *(int32_t *)(data + sizeof(Janet));
    int32_t def = *(int32_t *)(data + sizeof(Janet) + sizeof(int32_t));
    const char *default_string = (const char *)(data + sizeof(Janet) + sizeof(int32_t) * 2);

    // Ensure the default_string is null-terminated
    size_t max_string_length = size - (sizeof(Janet) + sizeof(int32_t) * 2);
    char *safe_default_string = (char *)malloc(max_string_length + 1);
    if (!safe_default_string) {
        return 0; // Fail gracefully if memory allocation fails
    }
    memcpy(safe_default_string, default_string, max_string_length);
    safe_default_string[max_string_length] = '\0';

    // Ensure that the Janet structure is properly initialized
    janet_array[0] = janet_wrap_nil(); // Initialize with a default value

    // Validate 'n' to be within a valid range for janet_optcbytes
    if (n < 0 || n >= 1) { // Assuming the array has only one element
        free(safe_default_string);
        return 0;
    }

    // Call the function-under-test
    const char *result = janet_optcbytes(janet_array, n, def, safe_default_string);

    // Use the result to avoid compiler optimizations removing the call
    if (result) {
        // Do something with the result if needed
    }

    free(safe_default_string); // Free the allocated memory

    return 0;
}