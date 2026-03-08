// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_new_full at ucl_util.c:2992:1 in ucl.h
// ucl_object_type at ucl_util.c:3068:1 in ucl.h
// ucl_object_get_priority at ucl_util.c:3823:1 in ucl.h
// ucl_object_set_priority at ucl_util.c:3832:6 in ucl.h
// ucl_object_iterate_new at ucl_util.c:2794:1 in ucl.h
// ucl_object_new_userdata at ucl_util.c:3045:1 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <ucl.h>

static void dummy_dtor(void *ud) {
    // Dummy destructor
}

static void dummy_emitter(void *ud) {
    // Dummy emitter
}

int LLVMFuzzerTestOneInput_57(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(ucl_type_t) + sizeof(unsigned int)) {
        return 0;
    }

    // Extract type and priority from input data
    ucl_type_t type = *(ucl_type_t *)Data;
    unsigned int priority = *(unsigned int *)(Data + sizeof(ucl_type_t));

    // Test ucl_object_new_full
    ucl_object_t *obj = ucl_object_new_full(type, priority);
    if (obj) {
        // Test ucl_object_type
        ucl_type_t obj_type = ucl_object_type(obj);

        // Test ucl_object_get_priority
        unsigned int obj_priority = ucl_object_get_priority(obj);

        // Test ucl_object_set_priority
        ucl_object_set_priority(obj, priority & 0xF);

        // Test ucl_object_iterate_new
        ucl_object_iter_t iter = ucl_object_iterate_new(obj);
        if (iter) {
            // Normally you'd iterate here, but we're just testing creation
            free(iter);
        }

        // Cleanup
        free(obj);
    }

    // Test ucl_object_new_userdata
    if (Size > sizeof(ucl_type_t) + sizeof(unsigned int) + sizeof(void *)) {
        void *user_data = (void *)(Data + sizeof(ucl_type_t) + sizeof(unsigned int));
        ucl_object_t *ud_obj = ucl_object_new_userdata(dummy_dtor, dummy_emitter, user_data);
        if (ud_obj) {
            free(ud_obj);
        }
    }

    return 0;
}