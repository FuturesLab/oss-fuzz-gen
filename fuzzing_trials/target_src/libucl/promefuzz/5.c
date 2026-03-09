// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_object_lookup at ucl_util.c:2673:1 in ucl.h
// ucl_object_lookup at ucl_util.c:2673:1 in ucl.h
// ucl_object_lookup at ucl_util.c:2673:1 in ucl.h
// ucl_object_validate at ucl_schema.c:1068:6 in ucl.h
// ucl_object_toboolean at ucl_util.c:3499:6 in ucl.h
// ucl_object_toboolean at ucl_util.c:3499:6 in ucl.h
// ucl_object_tostring at ucl_util.c:3527:1 in ucl.h
// ucl_object_emit at ucl_emitter.c:661:1 in ucl.h
// ucl_object_emit at ucl_emitter.c:661:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare dummy UCL objects
    ucl_object_t *root = ucl_object_fromstring("root");
    ucl_object_t *schema = ucl_object_fromstring("schema");
    struct ucl_schema_error err;

    // Ensure null-terminated keys
    char key1[256] = {0};
    char key2[256] = {0};
    char key3[256] = {0};

    size_t len1 = (Size > 255) ? 255 : Size;
    size_t len2 = (Size > 256) ? 255 : (Size - 1);
    size_t len3 = (Size > 257) ? 255 : (Size - 2);

    memcpy(key1, Data, len1);
    if (Size > 1) memcpy(key2, Data + 1, len2);
    if (Size > 2) memcpy(key3, Data + 2, len3);

    // Lookup objects
    const ucl_object_t *obj1 = ucl_object_lookup(root, key1);
    const ucl_object_t *obj2 = ucl_object_lookup(root, key2);
    const ucl_object_t *obj3 = ucl_object_lookup(root, key3);

    // Validate object
    bool is_valid = ucl_object_validate(schema, root, &err);

    // Convert to boolean
    bool bool_val1 = ucl_object_toboolean(obj1);
    bool bool_val2 = ucl_object_toboolean(obj2);

    // Convert to string
    const char *str_val = ucl_object_tostring(obj3);

    // Emit object
    unsigned char *json_str = ucl_object_emit(root, UCL_EMIT_JSON);
    unsigned char *config_str = ucl_object_emit(root, UCL_EMIT_CONFIG);

    // Clean up
    if (json_str) free(json_str);
    if (config_str) free(config_str);
    ucl_object_unref(root);
    ucl_object_unref(schema);

    return 0;
}