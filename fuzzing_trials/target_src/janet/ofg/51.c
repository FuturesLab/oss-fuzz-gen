#include <stdint.h>
#include <stddef.h>
#include <janet.h>

// Ensure that the Janet library is initialized before calling janet_root_fiber
void initialize_janet_51() {
    static int initialized = 0;
    if (!initialized) {
        janet_init();
        initialized = 1;
    }
}

int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    // Initialize Janet VM if not already initialized
    initialize_janet_51();

    // Call the function-under-test
    JanetFiber *fiber = janet_root_fiber();

    // Ensure the fiber is not NULL (though it should never be)
    if (fiber == NULL) {
        return 0;
    }

    // Perform any additional operations on the fiber if needed
    // For this simple function, there's nothing else to do

    return 0;
}