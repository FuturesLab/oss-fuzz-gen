// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_new at ucl_util.c:2980:1 in ucl.h
// ucl_object_new at ucl_util.c:2980:1 in ucl.h
// ucl_object_new at ucl_util.c:2980:1 in ucl.h
// ucl_object_new at ucl_util.c:2980:1 in ucl.h
// ucl_object_validate_root_ext at ucl_schema.c:1082:6 in ucl.h
// ucl_object_validate at ucl_schema.c:1068:6 in ucl.h
// ucl_object_delete_keyl at ucl_util.c:2482:6 in ucl.h
// ucl_object_validate_root at ucl_schema.c:1074:6 in ucl.h
// ucl_object_free at ucl_util.c:292:6 in ucl.h
// ucl_object_free at ucl_util.c:292:6 in ucl.h
// ucl_object_free at ucl_util.c:292:6 in ucl.h
// ucl_object_free at ucl_util.c:292:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file != NULL) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_49(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare environment
    ucl_object_t *schema = ucl_object_new();
    ucl_object_t *obj = ucl_object_new();
    ucl_object_t *root = ucl_object_new();
    ucl_object_t *ext_refs = ucl_object_new();
    struct ucl_schema_error err;

    // Use the data to manipulate the objects
    write_dummy_file(Data, Size);

    // Fuzz ucl_object_validate_root_ext
    ucl_object_validate_root_ext(schema, obj, root, ext_refs, &err);

    // Fuzz ucl_object_validate
    ucl_object_validate(schema, obj, &err);

    // Fuzz ucl_object_delete_keyl
    const char *key = (const char *)Data;
    size_t keylen = Size > 255 ? 255 : Size;
    ucl_object_delete_keyl(obj, key, keylen);

    // Fuzz ucl_object_validate_root
    ucl_object_validate_root(schema, obj, root, &err);

    // Cleanup
    ucl_object_free(schema);
    ucl_object_free(obj);
    ucl_object_free(root);
    ucl_object_free(ext_refs);

    return 0;
}