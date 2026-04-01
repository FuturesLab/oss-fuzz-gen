#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Declare a pointer to a void pointer
    void *memory_pointer = NULL;

    // Call the function-under-test
    struct ucl_emitter_functions *emitter_funcs = ucl_object_emit_memory_funcs(&memory_pointer);

    // Normally, you would use the `emitter_funcs` and `memory_pointer` here,
    // but for the purpose of this fuzzing harness, we are only interested in
    // calling the function to see if it handles the inputs correctly.

    // Clean up if necessary
    if (emitter_funcs != NULL) {
        // Assuming there's a function to free or clean up emitter_funcs, if needed.
        // Example: ucl_emitter_functions_free(emitter_funcs);
    }

    return 0;
}