// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_array_prepend at ucl_util.c:3163:6 in ucl.h
// ucl_object_array_sort at ucl_util.c:3799:6 in ucl.h
// ucl_object_fromdouble at ucl_util.c:3104:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <ucl.h>
#include <stdlib.h>
#include <string.h>

static int cmp_func(const ucl_object_t **o1, const ucl_object_t **o2) {
    if ((*o1)->type == UCL_FLOAT && (*o2)->type == UCL_FLOAT) {
        double diff = (*o1)->value.dv - (*o2)->value.dv;
        return (diff > 0) - (diff < 0);
    }
    return 0;
}

int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare a string from the input data
    char *input_string = (char *)malloc(Size + 1);
    if (!input_string) return 0;
    memcpy(input_string, Data, Size);
    input_string[Size] = '\0';

    // Create array object
    ucl_object_t *array = ucl_object_typed_new(UCL_ARRAY);
    if (!array) {
        free(input_string);
        return 0;
    }

    // Create UCL objects from string and prepend to array
    for (int i = 0; i < 4; i++) {
        ucl_object_t *string_obj = ucl_object_fromstring(input_string);
        if (string_obj) {
            ucl_array_prepend(array, string_obj);
        }
    }

    // Sort the array
    ucl_object_array_sort(array, cmp_func);

    // Create a UCL object from a double value
    double dv = (Size > 7) ? *((double*)Data) : 0.0;
    ucl_object_t *double_obj = ucl_object_fromdouble(dv);

    // Cleanup
    ucl_object_unref(array);
    if (double_obj) {
        ucl_object_unref(double_obj);
    }
    free(input_string);

    return 0;
}