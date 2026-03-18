// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_array_prepend at ucl_util.c:3163:6 in ucl.h
// ucl_array_prepend at ucl_util.c:3163:6 in ucl.h
// ucl_array_prepend at ucl_util.c:3163:6 in ucl.h
// ucl_array_prepend at ucl_util.c:3163:6 in ucl.h
// ucl_object_array_sort at ucl_util.c:3799:6 in ucl.h
// ucl_object_fromdouble at ucl_util.c:3104:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

static int cmp_func(const ucl_object_t **o1, const ucl_object_t **o2) {
    // Simple comparison function for sorting, comparing string values
    return strcmp((*o1)->value.sv, (*o2)->value.sv);
}

int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Prepare a null-terminated string from the input data
    char *input_string = (char *)malloc(Size + 1);
    if (input_string == NULL) {
        return 0;
    }
    memcpy(input_string, Data, Size);
    input_string[Size] = '\0';

    // Create UCL objects from strings
    ucl_object_t *obj1 = ucl_object_fromstring(input_string);
    ucl_object_t *obj2 = ucl_object_fromstring(input_string);
    ucl_object_t *obj3 = ucl_object_fromstring(input_string);
    ucl_object_t *obj4 = ucl_object_fromstring(input_string);

    // Create an array object
    ucl_object_t *array_obj = ucl_object_fromstring(""); // Dummy initialization

    // Prepend objects to the array
    if (array_obj) {
        ucl_array_prepend(array_obj, obj1);
        ucl_array_prepend(array_obj, obj2);
        ucl_array_prepend(array_obj, obj3);
        ucl_array_prepend(array_obj, obj4);

        // Sort the array
        ucl_object_array_sort(array_obj, cmp_func);
    }

    // Create a double object
    double value = 0.0;
    if (Size >= sizeof(double)) {
        memcpy(&value, Data, sizeof(double));
    }
    ucl_object_t *double_obj = ucl_object_fromdouble(value);

    // Cleanup
    free(input_string);
    ucl_object_unref(obj1);
    ucl_object_unref(obj2);
    ucl_object_unref(obj3);
    ucl_object_unref(obj4);
    ucl_object_unref(array_obj);
    ucl_object_unref(double_obj);

    return 0;
}