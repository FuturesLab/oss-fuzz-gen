// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_set_priority at ucl_util.c:3832:6 in ucl.h
// ucl_object_get_priority at ucl_util.c:3823:1 in ucl.h
// ucl_object_iterate_new at ucl_util.c:2794:1 in ucl.h
// ucl_object_new_userdata at ucl_util.c:3045:1 in ucl.h
// ucl_object_type at ucl_util.c:3068:1 in ucl.h
// ucl_object_new_full at ucl_util.c:2992:1 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <ucl.h>

static ucl_object_t* create_random_ucl_object() {
    ucl_type_t type = rand() % (UCL_NULL + 1);
    unsigned priority = rand() % 16;
    return ucl_object_new_full(type, priority);
}

static void dummy_dtor(void *ptr) {
    // Dummy destructor
}

static const char* dummy_emitter(void *ptr) {
    // Dummy emitter
    return NULL;
}

int LLVMFuzzerTestOneInput_79(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int)) return 0;

    // Create a new UCL object
    ucl_object_t *obj = create_random_ucl_object();
    if (obj == NULL) return 0;

    // Set a priority
    unsigned int priority = *((unsigned int *)Data);
    ucl_object_set_priority(obj, priority);

    // Get the priority
    unsigned int retrieved_priority = ucl_object_get_priority(obj);

    // Create a new iterator
    ucl_object_iter_t iter = ucl_object_iterate_new(obj);
    if (iter != NULL) {
        // Normally we would iterate, but for fuzzing, just free
        free(iter);
    }

    // Create a new userdata object
    ucl_object_t *userdata_obj = ucl_object_new_userdata(dummy_dtor, dummy_emitter, NULL);
    if (userdata_obj != NULL) {
        // Clean up
        free(userdata_obj);
    }

    // Get the type of the object
    ucl_type_t obj_type = ucl_object_type(obj);

    // Clean up the original object
    free(obj);

    return 0;
}