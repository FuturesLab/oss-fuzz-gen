#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

// Define a custom append function for ucl_emitter_functions
static int custom_append_len(const unsigned char *str, size_t len, void *ud) {
    (void)str;  // Unused parameter
    (void)len;  // Unused parameter
    (void)ud;   // Unused parameter
    return 0;
}

int LLVMFuzzerTestOneInput_155(const uint8_t *data, size_t size) {
    struct ucl_emitter_functions *emitter_funcs;

    // Allocate memory for the ucl_emitter_functions structure
    emitter_funcs = (struct ucl_emitter_functions *)malloc(sizeof(struct ucl_emitter_functions));
    if (emitter_funcs == NULL) {
        return 0;
    }

    // Initialize the structure with a custom append function
    emitter_funcs->ucl_emitter_append_len = custom_append_len;
    emitter_funcs->ud = NULL;

    // Call the function-under-test
    ucl_object_emit_funcs_free(emitter_funcs);

    // Free the allocated memory
    free(emitter_funcs);

    return 0;
}