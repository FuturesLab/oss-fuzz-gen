#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for the test
    if (size < sizeof(void *)) {
        return 0;
    }

    // Prepare a non-NULL pointer for the function call
    void *memory_ptr = (void *)data;

    // Call the function-under-test
    struct ucl_emitter_functions *emitter_funcs = ucl_object_emit_memory_funcs(&memory_ptr);

    // Clean up if necessary
    if (emitter_funcs != NULL) {
        // Perform any required cleanup on emitter_funcs if the library requires it
    }

    return 0;
}