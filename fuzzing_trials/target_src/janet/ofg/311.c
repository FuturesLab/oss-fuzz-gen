#include <stddef.h>
#include <stdint.h>
#include <janet.h>

// Function signature for the fuzzer entry point
int LLVMFuzzerTestOneInput_311(const uint8_t *data, size_t size) {
    // Initialize the Janet environment (if required by the library)
    janet_init();

    // Ensure the data is large enough to be used as a pointer
    if (size < sizeof(void *)) {
        return 0;
    }

    // Use the data as a pointer
    const void *ptr = (const void *)data;

    // Call the function-under-test
    JanetAbstractHead *result = janet_abstract_head(ptr);

    // Use the result to avoid compiler optimizations removing the call
    if (result != NULL) {
        // Perform some trivial operation on the result
        // This is just to ensure the result is used in some way
        volatile JanetAbstractHead *volatile_result = result;
        (void)volatile_result;
    }

    // Deinitialize the Janet environment (if required by the library)
    janet_deinit();

    return 0;
}