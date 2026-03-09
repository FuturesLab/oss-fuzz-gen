#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    void *memory_context = (void *)data;  // Initialize with non-NULL value
    struct ucl_emitter_functions *emitter_funcs;

    // Call the function-under-test
    emitter_funcs = ucl_object_emit_memory_funcs(&memory_context);

    // Normally, you would use the returned `emitter_funcs` here.
    // For fuzzing purposes, we just ensure the function is called.
    // Clean up if necessary (depends on the library's requirements).

    return 0;
}