#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
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

int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

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
    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function ucl_object_tostring with ucl_object_tostring_forced
    const char *str = ucl_object_tostring_forced(str_obj);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR

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
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_29(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
