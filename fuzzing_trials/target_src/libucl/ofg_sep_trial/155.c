#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_155(const uint8_t *data, size_t size) {
    struct ucl_emitter_functions *emitter_funcs;

    // Allocate memory for the ucl_emitter_functions structure
    emitter_funcs = (struct ucl_emitter_functions *)malloc(sizeof(struct ucl_emitter_functions));
    if (emitter_funcs == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Initialize the structure with non-NULL values
    emitter_funcs->ucl_emitter_append_character = (void (*)(unsigned char, size_t, void *))data;
    emitter_funcs->ucl_emitter_append_len = (void (*)(const unsigned char *, size_t, void *))data;
    emitter_funcs->ucl_emitter_free_func = (void (*)(void *))data;
    emitter_funcs->ud = (void *)data;

    // Call the function under test
    ucl_object_emit_funcs_free(emitter_funcs);

    return 0;
}