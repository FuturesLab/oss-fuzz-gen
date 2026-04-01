// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_string_to_type at ucl_util.c:3845:6 in ucl.h
// ucl_object_new_full at ucl_util.c:2992:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_type_to_string at ucl_util.c:3879:1 in ucl.h
// ucl_object_new_userdata at ucl_util.c:3045:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_type at ucl_util.c:3068:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdbool.h>

static void dummy_dtor(void *ud) {
    // Dummy destructor
}

static const char *dummy_emitter(void *ud) {
    // Dummy emitter
    return "dummy";
}

int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Fuzz ucl_object_typed_new
    ucl_type_t type = (ucl_type_t)(Data[0] % (UCL_NULL + 1));
    ucl_object_t *obj1 = ucl_object_typed_new(type);

    // Fuzz ucl_object_string_to_type
    char input[Size + 1];
    memcpy(input, Data, Size);
    input[Size] = '\0';
    ucl_type_t res;
    bool conversion_success = ucl_object_string_to_type(input, &res);

    // Fuzz ucl_object_new_full
    unsigned priority = Data[0];
    ucl_object_t *obj2 = ucl_object_new_full(type, priority);
    if (obj2) {
        ucl_object_unref(obj2);
    }

    // Fuzz ucl_object_type_to_string
    const char *type_str = ucl_object_type_to_string(type);

    // Fuzz ucl_object_new_userdata
    void *user_data = (void *)Data; // Just use the data pointer as user data
    ucl_object_t *obj3 = ucl_object_new_userdata(dummy_dtor, dummy_emitter, user_data);
    if (obj3) {
        ucl_object_unref(obj3);
    }

    // Fuzz ucl_object_type
    if (obj1) {
        ucl_type_t obj_type = ucl_object_type(obj1);
        ucl_object_unref(obj1);
    }

    return 0;
}