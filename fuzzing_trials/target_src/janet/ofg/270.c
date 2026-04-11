#include <stdint.h>
#include <stddef.h>
#include <janet.h>

// Initialize the Janet environment before using any Janet functions
static void initialize_janet_270() {
    static int initialized = 0;
    if (!initialized) {
        janet_init();
        initialized = 1;
    }
}

int LLVMFuzzerTestOneInput_270(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract parameters
    if (size < sizeof(Janet) + 2 * sizeof(int32_t) + sizeof(void *)) {
        return 0;
    }

    // Initialize Janet environment
    initialize_janet_270();

    // Extract parameters from the input data
    const Janet *janet_ptr = (const Janet *)(data);
    int32_t n = *(const int32_t *)(data + sizeof(Janet));
    int32_t def = *(const int32_t *)(data + sizeof(Janet) + sizeof(int32_t));
    void *dflt = (void *)(data + sizeof(Janet) + 2 * sizeof(int32_t));

    // Validate the extracted pointers
    if (janet_ptr == NULL || dflt == NULL) {
        return 0;
    }

    // Ensure the Janet pointer is valid by checking its type
    if (!janet_checktype(*janet_ptr, JANET_NIL) && 
        !janet_checktype(*janet_ptr, JANET_NUMBER) && 
        !janet_checktype(*janet_ptr, JANET_STRING) && 
        !janet_checktype(*janet_ptr, JANET_SYMBOL) && 
        !janet_checktype(*janet_ptr, JANET_KEYWORD) && 
        !janet_checktype(*janet_ptr, JANET_ARRAY) && 
        !janet_checktype(*janet_ptr, JANET_TUPLE) && 
        !janet_checktype(*janet_ptr, JANET_TABLE) && 
        !janet_checktype(*janet_ptr, JANET_STRUCT) && 
        !janet_checktype(*janet_ptr, JANET_BUFFER) && 
        !janet_checktype(*janet_ptr, JANET_FUNCTION) && 
        !janet_checktype(*janet_ptr, JANET_CFUNCTION) && 
        !janet_checktype(*janet_ptr, JANET_FIBER) && 
        !janet_checktype(*janet_ptr, JANET_ABSTRACT) && 
        !janet_checktype(*janet_ptr, JANET_POINTER)) {
        return 0;
    }

    // Check if 'n' is within a reasonable range
    if (n < 0 || n > 100) { // Assuming 100 as a reasonable upper limit for demonstration
        return 0;
    }

    // Call the function-under-test
    void *result = janet_optpointer(janet_ptr, n, def, dflt);

    // Use the result to avoid any compiler optimizations that might skip the call
    (void)result;

    return 0;
}