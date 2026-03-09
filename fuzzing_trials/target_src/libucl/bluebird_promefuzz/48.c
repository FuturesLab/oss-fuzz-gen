#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include <stdbool.h>
#include "ucl.h"

int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a new UCL object of type UCL_OBJECT
    ucl_object_t *top = ucl_object_typed_new(UCL_OBJECT);
    if (top == NULL) return 0;

    // Convert the input data to a string
    const char *str = (const char *)Data;
    size_t len = Size;

    // Create UCL objects from strings
    ucl_object_t *elt1 = ucl_object_fromstring_common(str, len, UCL_STRING_TRIM);
    ucl_object_t *elt2 = ucl_object_fromstring_common(str, len, UCL_STRING_PARSE);
    ucl_object_t *elt3 = ucl_object_fromstring_common(str, len, UCL_STRING_ESCAPE);

    // Insert keys into the UCL object
    ucl_object_insert_key(top, elt1, "key1", 4, true);
    ucl_object_insert_key(top, elt2, "key2", 4, true);
    ucl_object_insert_key(top, elt3, "key3", 4, true);

    // Open a dummy file for writing
    FILE *fp = fopen("./dummy_file", "w");
    if (fp == NULL) {
        ucl_object_unref(top);
        return 0;
    }

    // Get emitter functions for file output
    struct ucl_emitter_functions *emitter_funcs = ucl_object_emit_file_funcs(fp);
    if (emitter_funcs == NULL) {
        fclose(fp);
        ucl_object_unref(top);
        return 0;
    }

    // Create and manage streamlined UCL emitters
    struct ucl_emitter_context *ctx1 = ucl_object_emit_streamline_new(top, UCL_EMIT_JSON, emitter_funcs);
    struct ucl_emitter_context *ctx2 = ucl_object_emit_streamline_new(top, UCL_EMIT_JSON_COMPACT, emitter_funcs);
    struct ucl_emitter_context *ctx3 = ucl_object_emit_streamline_new(top, UCL_EMIT_CONFIG, emitter_funcs);
    struct ucl_emitter_context *ctx4 = ucl_object_emit_streamline_new(top, UCL_EMIT_YAML, emitter_funcs);

    // Create a new UCL object of type UCL_ARRAY
    ucl_object_t *array_obj = ucl_object_typed_new(UCL_ARRAY);
    if (array_obj != NULL) {
        // Start a container for streamlined output
        ucl_object_emit_streamline_start_container(ctx1, array_obj);
        ucl_object_emit_streamline_start_container(ctx2, array_obj);
        ucl_object_emit_streamline_start_container(ctx3, array_obj);
        ucl_object_emit_streamline_start_container(ctx4, array_obj);
    }

    // Cleanup
    if (ctx1) ucl_object_emit_streamline_finish(ctx1);
    if (ctx2) ucl_object_emit_streamline_finish(ctx2);
    if (ctx3) ucl_object_emit_streamline_finish(ctx3);
    if (ctx4) ucl_object_emit_streamline_finish(ctx4);
    if (array_obj) ucl_object_unref(array_obj);
    fclose(fp);
    ucl_object_unref(top);

    return 0;
}