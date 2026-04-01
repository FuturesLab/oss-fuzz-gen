// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_array_prepend at ucl_util.c:3163:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_copy at ucl_util.c:3692:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_array_index_of at ucl_util.c:3355:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Prepare a dummy string from input data
    char *dummy_string = (char *)malloc(Size + 1);
    if (dummy_string == NULL) {
        return 0;
    }
    memcpy(dummy_string, Data, Size);
    dummy_string[Size] = '\0';

    // Create a UCL object from the string
    ucl_object_t *str_obj = ucl_object_fromstring(dummy_string);
    if (str_obj == NULL) {
        free(dummy_string);
        return 0;
    }

    // Create a UCL array object
    ucl_object_t *array_obj = ucl_object_typed_new(UCL_ARRAY);
    if (array_obj == NULL) {
        ucl_object_unref(str_obj);
        free(dummy_string);
        return 0;
    }

    // Prepend the string object to the array
    bool prepended = ucl_array_prepend(array_obj, str_obj);
    if (!prepended) {
        ucl_object_unref(str_obj);
        ucl_object_unref(array_obj);
        free(dummy_string);
        return 0;
    }

    // Copy the string object
    ucl_object_t *copy_obj = ucl_object_copy(str_obj);
    if (copy_obj == NULL) {
        ucl_object_unref(array_obj);
        free(dummy_string);
        return 0;
    }

    // Find the index of the copied object in the array
    unsigned int index = ucl_array_index_of(array_obj, copy_obj);

    // Cleanup
    ucl_object_unref(copy_obj);
    ucl_object_unref(array_obj);
    free(dummy_string);

    return 0;
}