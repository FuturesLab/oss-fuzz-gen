// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_new_full at ucl_util.c:2992:1 in ucl.h
// ucl_object_merge at ucl_util.c:2551:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_new_full at ucl_util.c:2992:1 in ucl.h
// ucl_array_append at ucl_util.c:3131:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "ucl.h"

static ucl_object_t* create_random_ucl_object(const uint8_t *Data, size_t Size) {
    if (Size < 1) return NULL;

    ucl_type_t type = Data[0] % 8; // Random type based on first byte
    unsigned priority = Data[0] % 10; // Random priority
    return ucl_object_new_full(type, priority);
}

int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    // Create two random UCL objects
    ucl_object_t *obj1 = create_random_ucl_object(Data, Size);
    ucl_object_t *obj2 = create_random_ucl_object(Data + 1, Size - 1);

    if (obj1 && obj2) {
        // Merge obj2 into obj1
        bool copy = Data[1] % 2; // Random boolean
        ucl_object_merge(obj1, obj2, copy);

        // Unref obj2 as it's no longer needed
        ucl_object_unref(obj2);

        // Create a new UCL array object
        ucl_object_t *array_obj = ucl_object_new_full(UCL_ARRAY, 0);
        if (array_obj) {
            // Append obj1 to the array
            ucl_array_append(array_obj, obj1);

            // Unref array_obj
            ucl_object_unref(array_obj);
        } else {
            // If array creation failed, unref obj1
            ucl_object_unref(obj1);
        }
    } else {
        // Cleanup if objects are not created
        if (obj1) ucl_object_unref(obj1);
        if (obj2) ucl_object_unref(obj2);
    }

    return 0;
}