// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_fromstring_common at ucl_util.c:2225:1 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_fromstring_common at ucl_util.c:2225:1 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_fromstring_common at ucl_util.c:2225:1 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_emit_file_funcs at ucl_emitter_utils.c:401:1 in ucl.h
// ucl_object_emit_streamline_new at ucl_emitter_streamline.c:63:1 in ucl.h
// ucl_object_emit_streamline_start_container at ucl_emitter_streamline.c:90:6 in ucl.h
// ucl_object_emit_streamline_new at ucl_emitter_streamline.c:63:1 in ucl.h
// ucl_object_emit_streamline_new at ucl_emitter_streamline.c:63:1 in ucl.h
// ucl_object_emit_streamline_new at ucl_emitter_streamline.c:63:1 in ucl.h
// ucl_object_emit_streamline_new at ucl_emitter_streamline.c:63:1 in ucl.h
// ucl_object_emit_streamline_finish at ucl_emitter_streamline.c:169:6 in ucl.h
// ucl_object_emit_streamline_finish at ucl_emitter_streamline.c:169:6 in ucl.h
// ucl_object_emit_streamline_finish at ucl_emitter_streamline.c:169:6 in ucl.h
// ucl_object_emit_streamline_finish at ucl_emitter_streamline.c:169:6 in ucl.h
// ucl_object_emit_streamline_finish at ucl_emitter_streamline.c:169:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    ucl_object_t *top = ucl_object_typed_new(UCL_OBJECT);
    if (!top) return 0;

    // Convert the first part of the data to a string
    ucl_object_t *string_obj = ucl_object_fromstring_common((const char *)Data, Size, UCL_STRING_PARSE);
    if (string_obj) {
        ucl_object_insert_key(top, string_obj, "key1", 4, true);
    }

    // Convert the second part of the data to a string
    string_obj = ucl_object_fromstring_common((const char *)Data, Size, UCL_STRING_ESCAPE);
    if (string_obj) {
        ucl_object_insert_key(top, string_obj, "key2", 4, true);
    }

    // Convert the third part of the data to a string
    string_obj = ucl_object_fromstring_common((const char *)Data, Size, UCL_STRING_TRIM);
    if (string_obj) {
        ucl_object_insert_key(top, string_obj, "key3", 4, true);
    }

    FILE *fp = fopen("./dummy_file", "w");
    if (fp) {
        struct ucl_emitter_functions *emitter_funcs = ucl_object_emit_file_funcs(fp);
        if (emitter_funcs) {
            struct ucl_emitter_context *ctx = ucl_object_emit_streamline_new(top, UCL_EMIT_JSON, emitter_funcs);
            if (ctx) {
                ucl_object_emit_streamline_start_container(ctx, top);
                // Emit using different formats
                struct ucl_emitter_context *ctx_json = ucl_object_emit_streamline_new(top, UCL_EMIT_JSON, emitter_funcs);
                struct ucl_emitter_context *ctx_json_compact = ucl_object_emit_streamline_new(top, UCL_EMIT_JSON_COMPACT, emitter_funcs);
                struct ucl_emitter_context *ctx_config = ucl_object_emit_streamline_new(top, UCL_EMIT_CONFIG, emitter_funcs);
                struct ucl_emitter_context *ctx_yaml = ucl_object_emit_streamline_new(top, UCL_EMIT_YAML, emitter_funcs);

                // Clean up
                ucl_object_emit_streamline_finish(ctx);
                if (ctx_json) ucl_object_emit_streamline_finish(ctx_json);
                if (ctx_json_compact) ucl_object_emit_streamline_finish(ctx_json_compact);
                if (ctx_config) ucl_object_emit_streamline_finish(ctx_config);
                if (ctx_yaml) ucl_object_emit_streamline_finish(ctx_yaml);
            }
            // Free emitter functions
            if (emitter_funcs->ucl_emitter_free_func) {
                emitter_funcs->ucl_emitter_free_func(emitter_funcs->ud);
            }
            free(emitter_funcs);
        }
        fclose(fp);
    }

    ucl_object_unref(top);
    return 0;
}