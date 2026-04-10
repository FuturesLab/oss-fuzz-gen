#include <stdint.h>
#include <stdlib.h>
#include "/src/janet/src/include/janet.h"

// Ensure the Janet library is initialized before calling any Janet functions
__attribute__((constructor))
static void initialize_janet_322() {
    janet_init();
}

int LLVMFuzzerTestOneInput_322(const uint8_t *data, size_t size) {
    // Call the function-under-test
    Janet *janet = janet_init();

    // Additional operations can be performed on the Janet environment if needed
    // For now, we just ensure the function is called

    // Clean up and free the allocated Janet environment
    if (janet != NULL) {
        janet_deinit();
    }

    return 0;
}