// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_fromlstring at ucl_util.c:3084:1 in ucl.h
// ucl_object_tolstring_safe at ucl_util.c:3546:6 in ucl.h
// ucl_object_emit_full at ucl_emitter.c:694:6 in ucl.h
// ucl_object_emit at ucl_emitter.c:661:1 in ucl.h
// ucl_object_tostring_safe at ucl_util.c:3507:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_iterate_new at ucl_util.c:2794:1 in ucl.h
// ucl_object_iter_chk_excpn at ucl_util.c:2809:6 in ucl.h
// ucl_object_iterate_free at ucl_util.c:2903:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>

static void write_dummy_file(const uint8_t *data, size_t size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_78(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Prepare data for ucl_object_fromlstring
    const char *str = (const char *)Data;
    size_t len = Size;
    ucl_object_t *obj = ucl_object_fromlstring(str, len);
    
    if (obj != NULL) {
        // Test ucl_object_tolstring_safe
        const char *target;
        size_t tlen;
        ucl_object_tolstring_safe(obj, &target, &tlen);

        // Only proceed with valid string objects for serialization
        if (obj->type == UCL_STRING) {
            // Test ucl_object_emit_full
            struct ucl_emitter_functions emitter_functions = {0};
            emitter_functions.ucl_emitter_append_character = NULL;
            emitter_functions.ucl_emitter_append_len = NULL;
            emitter_functions.ucl_emitter_append_int = NULL;
            emitter_functions.ucl_emitter_append_double = NULL;
            emitter_functions.ucl_emitter_free_func = NULL;
            emitter_functions.ud = NULL;

            // Ensure the emitter functions are valid before calling
            if (emitter_functions.ucl_emitter_append_len != NULL) {
                ucl_object_emit_full(obj, UCL_EMIT_JSON, &emitter_functions, NULL);
            }

            // Test ucl_object_emit
            unsigned char *emitted_str = ucl_object_emit(obj, UCL_EMIT_JSON);
            if (emitted_str != NULL) {
                free(emitted_str);
            }
        }

        // Test ucl_object_tostring_safe
        ucl_object_tostring_safe(obj, &target);

        ucl_object_unref(obj);
    }

    // Properly initialize an iterator before using it
    ucl_object_iter_t iter = ucl_object_iterate_new(obj);

    if (iter != NULL) {
        ucl_object_iter_chk_excpn(iter);
        ucl_object_iterate_free(iter);
    }

    // Write data to dummy file
    write_dummy_file(Data, Size);

    return 0;
}