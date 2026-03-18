// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_new_userdata at ucl_util.c:3045:1 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_fromlstring at ucl_util.c:3084:1 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_lookup_any at ucl_util.c:2683:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>

static void dummy_dtor(void *ptr) {
    // Dummy destructor function
}

static const char *dummy_emitter(void *ptr) {
    // Dummy emitter function
    return "dummy";
}

int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Ensure there's at least some data

    // Prepare a dummy file if needed
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }

    // Create a top-level UCL object
    ucl_object_t *top = ucl_object_typed_new(UCL_OBJECT);

    // Insert first key-value pair
    ucl_object_t *first_elt = ucl_object_typed_new(UCL_STRING);
    first_elt->value.sv = "first_value";
    ucl_object_insert_key(top, first_elt, "first_key", 9, false);

    // Insert second key-value pair
    ucl_object_t *second_elt = ucl_object_typed_new(UCL_STRING);
    second_elt->value.sv = "second_value";
    ucl_object_insert_key(top, second_elt, "second_key", 10, false);

    // Create a user data object
    ucl_object_t *user_data_obj = ucl_object_new_userdata(dummy_dtor, dummy_emitter, NULL);
    if (user_data_obj) {
        ucl_object_insert_key(top, user_data_obj, "user_data_key", 13, false);
    }

    // Create an object from string
    const char *str = "sample_string";
    ucl_object_t *str_obj = ucl_object_fromlstring(str, strlen(str));
    if (str_obj) {
        ucl_object_insert_key(top, str_obj, "string_key", 10, false);
    }

    // Lookup a key
    const ucl_object_t *found_obj = ucl_object_lookup_any(top, "first_key", "second_key", "nonexistent_key", NULL);

    // Cleanup
    ucl_object_unref(top);

    return 0;
}