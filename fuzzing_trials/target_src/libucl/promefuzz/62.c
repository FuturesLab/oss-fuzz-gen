// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_validate_root_ext at ucl_schema.c:1082:6 in ucl.h
// ucl_object_ref at ucl_util.c:3591:1 in ucl.h
// ucl_object_validate at ucl_schema.c:1068:6 in ucl.h
// ucl_object_validate_root at ucl_schema.c:1074:6 in ucl.h
// ucl_object_type at ucl_util.c:3068:1 in ucl.h
// ucl_object_toboolean at ucl_util.c:3499:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "ucl.h"

static ucl_object_t *create_dummy_ucl_object() {
    ucl_object_t *obj = malloc(sizeof(ucl_object_t));
    if (obj) {
        memset(obj, 0, sizeof(ucl_object_t));
        obj->type = UCL_OBJECT;
    }
    return obj;
}

static void free_ucl_object(ucl_object_t *obj) {
    if (obj) {
        free(obj);
    }
}

int LLVMFuzzerTestOneInput_62(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Create dummy UCL objects
    ucl_object_t *schema = create_dummy_ucl_object();
    ucl_object_t *obj = create_dummy_ucl_object();
    ucl_object_t *root = create_dummy_ucl_object();
    ucl_object_t *ext_refs = create_dummy_ucl_object();
    struct ucl_schema_error err;

    if (!schema || !obj || !root || !ext_refs) {
        free_ucl_object(schema);
        free_ucl_object(obj);
        free_ucl_object(root);
        free_ucl_object(ext_refs);
        return 0;
    }

    // Fuzz ucl_object_validate_root_ext
    ucl_object_validate_root_ext(schema, obj, root, ext_refs, &err);

    // Fuzz ucl_object_ref
    ucl_object_t *ref_obj = ucl_object_ref(obj);

    // Fuzz ucl_object_validate
    ucl_object_validate(schema, obj, &err);

    // Fuzz ucl_object_validate_root
    ucl_object_validate_root(schema, obj, root, &err);

    // Fuzz ucl_object_type
    ucl_type_t obj_type = ucl_object_type(obj);

    // Fuzz ucl_object_toboolean
    bool obj_bool = ucl_object_toboolean(obj);

    // Cleanup
    free_ucl_object(schema);
    free_ucl_object(obj);
    free_ucl_object(root);
    free_ucl_object(ext_refs);

    // Ensure ref_obj is not double-freed
    if (ref_obj != obj) {
        free_ucl_object(ref_obj);
    }

    return 0;
}