// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_array_append at ucl_util.c:3131:6 in ucl.h
// ucl_array_append at ucl_util.c:3131:6 in ucl.h
// ucl_array_merge at ucl_util.c:3193:6 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_delete_key at ucl_util.c:2503:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdbool.h>

static void cleanup(ucl_object_t *obj1, ucl_object_t *obj2, ucl_object_t *obj3, ucl_object_t *obj4, ucl_object_t *obj5) {
    if (obj1) ucl_object_unref(obj1);
    if (obj2) ucl_object_unref(obj2);
    if (obj3) ucl_object_unref(obj3);
    if (obj4) ucl_object_unref(obj4);
    if (obj5) ucl_object_unref(obj5);
}

int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Ensure null-terminated string
    char *input = (char *)malloc(Size + 1);
    if (!input) return 0;
    memcpy(input, Data, Size);
    input[Size] = '\0';

    // Create UCL objects from strings
    ucl_object_t *obj1 = ucl_object_fromstring(input);
    ucl_object_t *obj2 = ucl_object_fromstring(input);

    // Initialize arrays and objects
    ucl_object_t *array1 = ucl_object_typed_new(UCL_ARRAY);
    ucl_object_t *array2 = ucl_object_typed_new(UCL_ARRAY);
    ucl_object_t *object = ucl_object_typed_new(UCL_OBJECT);

    if (array1 && array2 && object && obj1 && obj2) {
        // Insert objects into arrays to ensure they are arrays
        ucl_array_append(array1, obj1);
        ucl_array_append(array2, obj2);

        // Merge arrays
        ucl_array_merge(array1, array2, false);

        // Insert into object
        ucl_object_insert_key(object, ucl_object_fromstring(input), "key1", 4, true);
        ucl_object_insert_key(object, ucl_object_fromstring(input), "key2", 4, true);

        // Delete key from object
        ucl_object_delete_key(object, "key1");
    }

    // Cleanup
    cleanup(NULL, NULL, array1, array2, object);
    free(input);

    return 0;
}