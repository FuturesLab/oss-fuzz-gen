#include <stdint.h>
#include <stddef.h>
#include <janet.h>

// Function to safely extract an integer from the input data
static int32_t safe_extract_int32(const uint8_t *data, size_t size, size_t offset) {
    if (offset + sizeof(int32_t) <= size) {
        return *(int32_t *)(data + offset);
    }
    return 0; // Return a default value if extraction is not possible
}

int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract the necessary parameters
    if (size < sizeof(Janet) + 3 * sizeof(int32_t)) {
        return 0;
    }

    // Initialize Janet VM
    janet_init();

    // Extract parameters from the input data
    Janet janet_data;
    memcpy(&janet_data, data, sizeof(Janet)); // Safely copy data into janet_data
    int32_t arg1 = safe_extract_int32(data, size, sizeof(Janet));
    int32_t arg2 = safe_extract_int32(data, size, sizeof(Janet) + sizeof(int32_t));
    int32_t arg3 = safe_extract_int32(data, size, sizeof(Janet) + 2 * sizeof(int32_t));

    // Ensure janet_data is valid before calling the function
    if (janet_checktype(janet_data, JANET_ARRAY)) {
        // Call the function-under-test
        JanetArray *result = janet_optarray(&janet_data, arg1, arg2, arg3);

        // Use the result in some way to avoid compiler optimizations removing the call
        if (result) {
            // For instance, access the length of the result array
            (void)result->count;
        }
    }

    // Clean up Janet VM
    janet_deinit();

    return 0;
}