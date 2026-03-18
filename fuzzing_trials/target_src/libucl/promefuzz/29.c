// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_iterate_new at ucl_util.c:2794:1 in ucl.h
// ucl_object_iterate_safe at ucl_util.c:2839:1 in ucl.h
// ucl_object_iter_chk_excpn at ucl_util.c:2809:6 in ucl.h
// ucl_object_type at ucl_util.c:3068:1 in ucl.h
// ucl_object_iterate_free at ucl_util.c:2903:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdbool.h>

int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(ucl_object_t)) {
        return 0;
    }

    // Prepare the environment
    ucl_object_t *obj = (ucl_object_t *)malloc(sizeof(ucl_object_t));
    if (obj == NULL) {
        return 0;
    }
    memcpy(obj, Data, sizeof(ucl_object_t));

    // Ensure the object is valid before creating an iterator
    obj->type = UCL_OBJECT; // Assuming a valid type for iteration
    obj->value.ov = NULL;   // Assuming an empty object for safety

    ucl_object_iter_t iter = ucl_object_iterate_new(obj);
    if (iter == NULL) {
        free(obj);
        return 0;
    }

    const ucl_object_t *next_obj;
    bool exception_occurred;
    ucl_type_t obj_type;

    // Explore program states by invoking the functions in order
    for (int i = 0; i < 4; i++) {
        next_obj = ucl_object_iterate_safe(iter, true);
        exception_occurred = ucl_object_iter_chk_excpn(iter);

        if (!exception_occurred && next_obj != NULL) {
            obj_type = ucl_object_type(next_obj);
        }
    }

    // Cleanup
    ucl_object_iterate_free(iter);
    free(obj);

    return 0;
}