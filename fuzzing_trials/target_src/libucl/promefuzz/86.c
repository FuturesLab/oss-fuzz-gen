// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_replace_key at ucl_util.c:2545:6 in ucl.h
// ucl_object_fromstring_common at ucl_util.c:2225:1 in ucl.h
// ucl_object_tostring at ucl_util.c:3527:1 in ucl.h
// ucl_object_emit_full at ucl_emitter.c:694:6 in ucl.h
// ucl_object_key at ucl_util.c:3575:1 in ucl.h
// ucl_object_lookup_path_char at ucl_util.c:2926:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static ucl_object_t* create_dummy_object() {
    ucl_object_t* obj = (ucl_object_t*)malloc(sizeof(ucl_object_t));
    if (obj) {
        memset(obj, 0, sizeof(ucl_object_t));
        obj->type = UCL_OBJECT;
    }
    return obj;
}

static int dummy_emitter_append_character(unsigned char c, size_t nchars, void *ud) {
    // Dummy implementation
    return 0;
}

static int dummy_emitter_append_len(unsigned const char *str, size_t len, void *ud) {
    // Dummy implementation
    return 0;
}

static int dummy_emitter_append_int(int64_t elt, void *ud) {
    // Dummy implementation
    return 0;
}

static int dummy_emitter_append_double(double elt, void *ud) {
    // Dummy implementation
    return 0;
}

static void dummy_emitter_free_func(void *ud) {
    // Dummy implementation
}

int LLVMFuzzerTestOneInput_86(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare dummy objects
    ucl_object_t *top = create_dummy_object();
    ucl_object_t *elt = create_dummy_object();
    ucl_object_t *comments = create_dummy_object();

    // Copy key
    char key[256];
    size_t keylen = (Size < 256) ? Size : 255;
    memcpy(key, Data, keylen);
    key[keylen] = '\0';

    // Test ucl_object_replace_key
    ucl_object_replace_key(top, elt, key, keylen, true);

    // Test ucl_object_fromstring_common
    ucl_object_t *str_obj = ucl_object_fromstring_common((const char *)Data, Size, UCL_STRING_PARSE);

    // Test ucl_object_tostring
    const char *str = ucl_object_tostring(str_obj);

    // Test ucl_object_emit_full
    struct ucl_emitter_functions emitter = {
        .ucl_emitter_append_character = dummy_emitter_append_character,
        .ucl_emitter_append_len = dummy_emitter_append_len,
        .ucl_emitter_append_int = dummy_emitter_append_int,
        .ucl_emitter_append_double = dummy_emitter_append_double,
        .ucl_emitter_free_func = dummy_emitter_free_func,
        .ud = NULL
    };
    ucl_object_emit_full(top, UCL_EMIT_JSON, &emitter, comments);

    // Test ucl_object_key
    const char *obj_key = ucl_object_key(top);

    // Test ucl_object_lookup_path_char
    const ucl_object_t *path_obj = ucl_object_lookup_path_char(top, key, '.');

    // Cleanup
    free(top);
    free(elt);
    free(comments);
    if (str_obj) {
        ucl_object_unref(str_obj);
    }

    return 0;
}