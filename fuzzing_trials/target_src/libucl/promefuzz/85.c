// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_fromstring_common at ucl_util.c:2225:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_fromstring_common at ucl_util.c:2225:1 in ucl.h
// ucl_object_replace_key at ucl_util.c:2545:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_fromstring_common at ucl_util.c:2225:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_tostring at ucl_util.c:3527:1 in ucl.h
// ucl_object_emit_full at ucl_emitter.c:694:6 in ucl.h
// ucl_object_key at ucl_util.c:3575:1 in ucl.h
// ucl_object_lookup_path_char at ucl_util.c:2926:1 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

static int dummy_append_character(unsigned char c, size_t nchars, void *ud) {
    // Dummy implementation for appending a character
    return 0;
}

static int dummy_append_len(unsigned const char *str, size_t len, void *ud) {
    // Dummy implementation for appending a string
    return 0;
}

static int dummy_append_int(int64_t elt, void *ud) {
    // Dummy implementation for appending an integer
    return 0;
}

static int dummy_append_double(double elt, void *ud) {
    // Dummy implementation for appending a double
    return 0;
}

static void dummy_free_func(void *ud) {
    // Dummy implementation for freeing userdata
}

static void fuzz_ucl_object_replace_key(ucl_object_t *top) {
    ucl_object_t *elt = ucl_object_fromstring_common("test", 0, UCL_STRING_RAW);
    if (!elt) return;

    const char *key = "key";
    bool result = ucl_object_replace_key(top, elt, key, strlen(key), true);

    // Handle result if necessary
    if (!result) {
        ucl_object_unref(elt);
    }
}

static void fuzz_ucl_object_fromstring_common(const uint8_t *Data, size_t Size) {
    char *null_terminated_data = (char *)malloc(Size + 1);
    if (null_terminated_data == NULL) {
        return;
    }
    memcpy(null_terminated_data, Data, Size);
    null_terminated_data[Size] = '\0';

    ucl_object_t *obj = ucl_object_fromstring_common(null_terminated_data, Size, UCL_STRING_PARSE);
    if (obj) {
        ucl_object_unref(obj);
    }

    free(null_terminated_data);
}

static void fuzz_ucl_object_tostring(ucl_object_t *obj) {
    const char *str = ucl_object_tostring(obj);
    // Use the string if needed, but do not free it as per the documentation
    (void)str;
}

static void fuzz_ucl_object_emit_full(ucl_object_t *obj) {
    struct ucl_emitter_functions emitter = {
        .ucl_emitter_append_character = dummy_append_character,
        .ucl_emitter_append_len = dummy_append_len,
        .ucl_emitter_append_int = dummy_append_int,
        .ucl_emitter_append_double = dummy_append_double,
        .ucl_emitter_free_func = dummy_free_func,
        .ud = NULL
    };

    bool result = ucl_object_emit_full(obj, UCL_EMIT_JSON, &emitter, NULL);
    // Handle result if necessary
    (void)result;
}

static void fuzz_ucl_object_key(ucl_object_t *obj) {
    const char *key = ucl_object_key(obj);
    // Use the key if needed, do not free it
    (void)key;
}

static void fuzz_ucl_object_lookup_path_char(ucl_object_t *obj) {
    const char *path = "some.path";
    const ucl_object_t *found = ucl_object_lookup_path_char(obj, path, '.');
    // Use the found object if needed
    (void)found;
}

int LLVMFuzzerTestOneInput_85(const uint8_t *Data, size_t Size) {
    char *null_terminated_data = (char *)malloc(Size + 1);
    if (null_terminated_data == NULL) {
        return 0;
    }
    memcpy(null_terminated_data, Data, Size);
    null_terminated_data[Size] = '\0';

    ucl_object_t *root = ucl_object_fromstring_common(null_terminated_data, Size, UCL_STRING_PARSE);
    if (root) {
        fuzz_ucl_object_replace_key(root);
        fuzz_ucl_object_fromstring_common(Data, Size);
        fuzz_ucl_object_tostring(root);
        fuzz_ucl_object_emit_full(root);
        fuzz_ucl_object_key(root);
        fuzz_ucl_object_lookup_path_char(root);

        ucl_object_unref(root);
    }

    free(null_terminated_data);
    return 0;
}