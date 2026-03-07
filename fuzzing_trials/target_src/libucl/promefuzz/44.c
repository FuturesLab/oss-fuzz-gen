// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_type at ucl_util.c:3068:1 in ucl.h
// ucl_object_ref at ucl_util.c:3591:1 in ucl.h
// ucl_object_validate_root_ext at ucl_schema.c:1082:6 in ucl.h
// ucl_object_validate at ucl_schema.c:1068:6 in ucl.h
// ucl_object_toboolean at ucl_util.c:3499:6 in ucl.h
// ucl_object_validate_root at ucl_schema.c:1074:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ucl.h>

static ucl_object_t* create_dummy_ucl_object() {
    ucl_object_t *obj = (ucl_object_t *)malloc(sizeof(ucl_object_t));
    if (obj) {
        memset(obj, 0, sizeof(ucl_object_t)); // Initialize memory to avoid undefined behavior
        obj->value.iv = 42;
        obj->type = UCL_INT;
        obj->ref = 1;
        obj->key = "dummy_key";
        obj->keylen = 9;
        obj->len = sizeof(int64_t);
    }
    return obj;
}

static void cleanup_ucl_objects(ucl_object_t *obj1, ucl_object_t *obj2, ucl_object_t *obj3, ucl_object_t *ext_refs) {
    if (obj1) free(obj1);
    if (obj2) free(obj2);
    if (obj3) free(obj3);
    if (ext_refs) free(ext_refs);
}

int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int64_t)) return 0;

    ucl_object_t *obj = create_dummy_ucl_object();
    ucl_object_t *schema = create_dummy_ucl_object();
    ucl_object_t *root = create_dummy_ucl_object();
    ucl_object_t *ext_refs = create_dummy_ucl_object();
    struct ucl_schema_error err;

    // Fuzz ucl_object_type
    ucl_type_t type = ucl_object_type(obj);

    // Fuzz ucl_object_ref
    if (obj) {
        ucl_object_t *ref_obj = ucl_object_ref(obj);
    }

    // Fuzz ucl_object_validate_root_ext
    bool valid_ext = ucl_object_validate_root_ext(schema, obj, root, ext_refs, &err);

    // Fuzz ucl_object_validate
    bool valid = ucl_object_validate(schema, obj, &err);

    // Fuzz ucl_object_toboolean
    bool boolean_value = ucl_object_toboolean(obj);

    // Fuzz ucl_object_validate_root
    bool valid_root = ucl_object_validate_root(schema, obj, root, &err);

    // Cleanup
    cleanup_ucl_objects(obj, schema, root, ext_refs);

    return 0;
}