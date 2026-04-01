// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_fromlstring at ucl_util.c:3084:1 in ucl.h
// ucl_object_tolstring_safe at ucl_util.c:3546:6 in ucl.h
// ucl_object_tostring_safe at ucl_util.c:3507:6 in ucl.h
// ucl_object_emit at ucl_emitter.c:661:1 in ucl.h
// ucl_object_emit_full at ucl_emitter.c:694:6 in ucl.h
// ucl_object_iterate_new at ucl_util.c:2794:1 in ucl.h
// ucl_object_iter_chk_excpn at ucl_util.c:2809:6 in ucl.h
// ucl_object_iterate_free at ucl_util.c:2903:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

static int dummy_emitter_append_character(unsigned char c, size_t nchars, void *ud) {
    return 0;
}

static int dummy_emitter_append_len(unsigned const char *str, size_t len, void *ud) {
    return 0;
}

static int dummy_emitter_append_int(int64_t elt, void *ud) {
    return 0;
}

static int dummy_emitter_append_double(double elt, void *ud) {
    return 0;
}

static void dummy_emitter_free_func(void *ud) {
}

int LLVMFuzzerTestOneInput_89(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Prepare a string from the input data
    char *input_str = malloc(Size + 1);
    if (!input_str) return 0;
    memcpy(input_str, Data, Size);
    input_str[Size] = '\0';

    // Test ucl_object_fromlstring
    ucl_object_t *ucl_obj = ucl_object_fromlstring(input_str, Size);

    if (ucl_obj) {
        // Test ucl_object_tolstring_safe
        const char *target;
        size_t tlen;
        ucl_object_tolstring_safe(ucl_obj, &target, &tlen);

        // Test ucl_object_tostring_safe
        ucl_object_tostring_safe(ucl_obj, &target);

        // Test ucl_object_emit
        unsigned char *emit_str = ucl_object_emit(ucl_obj, UCL_EMIT_JSON);
        if (emit_str) {
            free(emit_str);
        }

        // Test ucl_object_emit_full
        struct ucl_emitter_functions emitter_funcs = {
            .ucl_emitter_append_character = dummy_emitter_append_character,
            .ucl_emitter_append_len = dummy_emitter_append_len,
            .ucl_emitter_append_int = dummy_emitter_append_int,
            .ucl_emitter_append_double = dummy_emitter_append_double,
            .ucl_emitter_free_func = dummy_emitter_free_func,
            .ud = NULL
        };
        ucl_object_emit_full(ucl_obj, UCL_EMIT_JSON, &emitter_funcs, NULL);

        // Initialize iterator properly for ucl_object_iter_chk_excpn
        ucl_object_iter_t iter = ucl_object_iterate_new(ucl_obj);
        if (iter) {
            ucl_object_iter_chk_excpn(iter);
            ucl_object_iterate_free(iter);
        }

        // Free the UCL object
        ucl_object_unref(ucl_obj);
    }

    free(input_str);
    return 0;
}