// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_replace_key at ucl_util.c:2545:6 in ucl.h
// ucl_object_fromstring_common at ucl_util.c:2225:1 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_fromstring_common at ucl_util.c:2225:1 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_fromstring_common at ucl_util.c:2225:1 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

static ucl_object_t* create_ucl_object_from_data(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return NULL;
    }
    // Use a portion of data to determine the type
    ucl_type_t type = (ucl_type_t)(Data[0] % (UCL_NULL + 1));
    return ucl_object_typed_new(type);
}

int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Create a top level UCL object of type UCL_OBJECT
    ucl_object_t *top = ucl_object_typed_new(UCL_OBJECT);
    if (!top) {
        return 0;
    }

    // Create an element UCL object from input data
    ucl_object_t *element = create_ucl_object_from_data(Data, Size);
    if (!element) {
        ucl_object_unref(top);
        return 0;
    }

    // Use part of the data as a key
    const char *key = (const char *)Data;
    size_t keylen = Size < 256 ? Size : 255; // Limit key length to 255
    bool copy_key = true;

    // Replace key in the top object
    bool replaced = ucl_object_replace_key(top, element, key, keylen, copy_key);

    // Create another element from a string
    ucl_object_t *str_obj = ucl_object_fromstring_common(key, keylen, UCL_STRING_PARSE);
    if (str_obj) {
        ucl_object_insert_key(top, str_obj, "inserted_key_1", 14, true);
    }

    // Insert another element
    ucl_object_t *str_obj2 = ucl_object_fromstring_common(key, keylen, UCL_STRING_PARSE_BOOLEAN);
    if (str_obj2) {
        ucl_object_insert_key(top, str_obj2, "inserted_key_2", 14, true);
    }

    // Insert yet another element
    ucl_object_t *str_obj3 = ucl_object_fromstring_common(key, keylen, UCL_STRING_PARSE_INT);
    if (str_obj3) {
        ucl_object_insert_key(top, str_obj3, "inserted_key_3", 14, true);
    }

    // Create a final UCL object with a specific type
    ucl_object_t *final_obj = ucl_object_typed_new(UCL_STRING);
    if (final_obj) {
        ucl_object_unref(final_obj);
    }

    // Clean up
    ucl_object_unref(top);

    return 0;
}