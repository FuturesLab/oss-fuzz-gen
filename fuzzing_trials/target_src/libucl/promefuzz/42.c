// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_fromstring_common at ucl_util.c:2225:1 in ucl.h
// ucl_object_fromstring_common at ucl_util.c:2225:1 in ucl.h
// ucl_object_fromstring_common at ucl_util.c:2225:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_replace_key at ucl_util.c:2545:6 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <ucl.h>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Prepare dummy file
    write_dummy_file(Data, Size);

    // Initialize UCL objects
    ucl_object_t *top = ucl_object_typed_new(UCL_OBJECT);
    ucl_object_t *elt1 = ucl_object_fromstring_common((const char *)Data, Size, UCL_STRING_RAW);
    ucl_object_t *elt2 = ucl_object_fromstring_common((const char *)Data, Size, UCL_STRING_TRIM);
    ucl_object_t *elt3 = ucl_object_fromstring_common((const char *)Data, Size, UCL_STRING_PARSE);

    if (!top || !elt1 || !elt2 || !elt3) {
        ucl_object_unref(top);
        ucl_object_unref(elt1);
        ucl_object_unref(elt2);
        ucl_object_unref(elt3);
        return 0;
    }

    const char *key1 = "key1";
    const char *key2 = "key2";
    const char *key3 = "key3";

    // Invoke target functions
    ucl_object_replace_key(top, elt1, key1, strlen(key1), true);
    ucl_object_insert_key(top, elt2, key2, strlen(key2), true);
    ucl_object_insert_key(top, elt3, key3, strlen(key3), true);

    // Create a new object of a different type
    ucl_object_t *new_obj = ucl_object_typed_new(UCL_STRING);

    // Clean up
    ucl_object_unref(top);
    ucl_object_unref(new_obj);

    return 0;
}