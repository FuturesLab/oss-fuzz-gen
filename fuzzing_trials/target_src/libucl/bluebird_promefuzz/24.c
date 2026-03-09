#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "ucl.h"

static int dummy_append_character(unsigned char c, size_t nchars, void *ud) {
    return 0;
}

static int dummy_append_len(unsigned const char *str, size_t len, void *ud) {
    return 0;
}

static int dummy_append_int(int64_t elt, void *ud) {
    return 0;
}

static int dummy_append_double(double elt, void *ud) {
    return 0;
}

static void dummy_free_func(void *ud) {
}

static struct ucl_emitter_functions *create_dummy_emitter_functions() {
    struct ucl_emitter_functions *funcs = malloc(sizeof(struct ucl_emitter_functions));
    if (funcs) {
        funcs->ucl_emitter_append_character = dummy_append_character;
        funcs->ucl_emitter_append_len = dummy_append_len;
        funcs->ucl_emitter_append_int = dummy_append_int;
        funcs->ucl_emitter_append_double = dummy_append_double;
        funcs->ucl_emitter_free_func = dummy_free_func;
        funcs->ud = NULL;
    }
    return funcs;
}

int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(ucl_object_t)) {
        return 0;
    }

    // Create a dummy UCL object
    ucl_object_t *obj = (ucl_object_t *)malloc(sizeof(ucl_object_t));
    if (!obj) {
        return 0;
    }
    memset(obj, 0, sizeof(ucl_object_t));
    obj->value.sv = (const char *)Data;
    obj->type = UCL_STRING;

    // Create dummy emitter functions
    struct ucl_emitter_functions *emitter_funcs = create_dummy_emitter_functions();
    if (!emitter_funcs) {
        free(obj);
        return 0;
    }

    // Initialize a streamlined context
    struct ucl_emitter_context *ctx = ucl_object_emit_streamline_new(obj, UCL_EMIT_JSON, emitter_funcs);
    if (ctx) {
        // Start a container
        ucl_object_emit_streamline_start_container(ctx, obj);

        // Add the object to the context
        ucl_object_emit_streamline_add_object(ctx, obj);

        // End the container
        ucl_object_emit_streamline_end_container(ctx);

        // Finish the context
        ucl_object_emit_streamline_finish(ctx);
    }

    // Free the emitter functions
    ucl_object_emit_funcs_free(emitter_funcs);

    // Clean up
    free(obj);

    return 0;
}