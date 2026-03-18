// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_array_append at ucl_util.c:3131:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_array_replace_index at ucl_util.c:3378:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_lookup_path at ucl_util.c:2919:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Convert input data to null-terminated string for the first ucl_object_fromstring
    char *input_string1 = (char *)malloc(Size + 1);
    if (input_string1 == NULL) {
        return 0;
    }
    memcpy(input_string1, Data, Size);
    input_string1[Size] = '\0';

    // Create a UCL object from the input string
    ucl_object_t *obj1 = ucl_object_fromstring(input_string1);
    free(input_string1);

    if (obj1 == NULL) {
        return 0;
    }

    // Create an array UCL object
    ucl_object_t *array_obj = ucl_object_typed_new(UCL_ARRAY);
    if (array_obj == NULL) {
        ucl_object_unref(obj1);
        return 0;
    }

    // Append the first object to the array
    ucl_array_append(array_obj, obj1);

    // Replace an element in the array at a specific index
    // Convert input data to null-terminated string for the second ucl_object_fromstring
    char *input_string2 = (char *)malloc(Size + 1);
    if (input_string2 == NULL) {
        ucl_object_unref(array_obj);
        return 0;
    }
    memcpy(input_string2, Data, Size);
    input_string2[Size] = '\0';

    ucl_object_t *obj2 = ucl_object_fromstring(input_string2);
    free(input_string2);

    if (obj2 != NULL) {
        ucl_object_t *replaced_obj = ucl_array_replace_index(array_obj, obj2, 0);
        if (replaced_obj != NULL) {
            ucl_object_unref(replaced_obj);
        }
    }

    // Lookup a path in the array object
    const ucl_object_t *result = ucl_object_lookup_path(array_obj, "0");

    // Cleanup
    ucl_object_unref(array_obj);

    return 0;
}