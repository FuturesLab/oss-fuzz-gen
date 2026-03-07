#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include "ucl.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static int dummy_emitter_append_character(unsigned char c, size_t nchars, void *ud) {
    (void)c; (void)nchars; (void)ud;
    return 0;
}

static int dummy_emitter_append_len(unsigned const char *str, size_t len, void *ud) {
    (void)str; (void)len; (void)ud;
    return 0;
}

static int dummy_emitter_append_int(int64_t elt, void *ud) {
    (void)elt; (void)ud;
    return 0;
}

static int dummy_emitter_append_double(double elt, void *ud) {
    (void)elt; (void)ud;
    return 0;
}

static void dummy_emitter_free_func(void *ud) {
    (void)ud;
}

int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    ucl_object_t *ucl_obj = ucl_object_new();
    if (!ucl_obj) return 0;

    // Ensure the key is null-terminated and within bounds
    char *key = (char *)malloc(Size + 1);
    if (!key) {
        ucl_object_unref(ucl_obj);
        return 0;
    }
    memcpy(key, Data, Size);
    key[Size] = '\0';

    // Fuzz ucl_object_delete_key
    ucl_object_delete_key(ucl_obj, key);

    // Fuzz ucl_object_sort_keys
    enum ucl_object_keys_sort_flags sort_flag = (enum ucl_object_keys_sort_flags)(Data[0] % 3);
    ucl_object_sort_keys(ucl_obj, sort_flag);

    // Fuzz ucl_object_validate
    ucl_object_t *schema = ucl_object_new();
    struct ucl_schema_error err;
    ucl_object_validate(schema, ucl_obj, &err);

    // Fuzz ucl_object_emit_full
    struct ucl_emitter_functions emitter = {
        .ucl_emitter_append_character = dummy_emitter_append_character,
        .ucl_emitter_append_len = dummy_emitter_append_len,
        .ucl_emitter_append_int = dummy_emitter_append_int,
        .ucl_emitter_append_double = dummy_emitter_append_double,
        .ucl_emitter_free_func = dummy_emitter_free_func,
        .ud = NULL
    };
    ucl_object_emit_full(ucl_obj, UCL_EMIT_JSON, &emitter, NULL);

    // Fuzz ucl_object_validate_root
    ucl_object_t *root_schema = ucl_object_new();
    ucl_object_validate_root(schema, ucl_obj, root_schema, &err);

    // Cleanup
    free(key);
    ucl_object_unref(ucl_obj);
    ucl_object_unref(schema);
    ucl_object_unref(root_schema);

    return 0;
}