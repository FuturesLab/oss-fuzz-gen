// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_fromdouble at ucl_util.c:3104:1 in ucl.h
// ucl_object_todouble at ucl_util.c:3446:1 in ucl.h
// ucl_object_toint_safe at ucl_util.c:3454:6 in ucl.h
// ucl_object_toboolean at ucl_util.c:3499:6 in ucl.h
// ucl_object_toboolean_safe at ucl_util.c:3483:6 in ucl.h
// ucl_object_frombool at ucl_util.c:3118:1 in ucl.h
// ucl_object_todouble at ucl_util.c:3446:1 in ucl.h
// ucl_object_toint_safe at ucl_util.c:3454:6 in ucl.h
// ucl_object_toboolean at ucl_util.c:3499:6 in ucl.h
// ucl_object_toboolean_safe at ucl_util.c:3483:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "ucl.h"

int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double) + sizeof(bool)) {
        return 0; // Not enough data
    }

    // Extract a double value from the input data
    double double_value;
    memcpy(&double_value, Data, sizeof(double));
    
    // Extract a boolean value from the input data
    bool bool_value = *(Data + sizeof(double)) % 2;

    // Test ucl_object_fromdouble
    ucl_object_t *obj_double = ucl_object_fromdouble(double_value);
    if (obj_double != NULL) {
        // Test ucl_object_todouble
        double converted_double = ucl_object_todouble(obj_double);

        // Test ucl_object_toint_safe
        int64_t int_value;
        ucl_object_toint_safe(obj_double, &int_value);

        // Test ucl_object_toboolean
        bool converted_bool = ucl_object_toboolean(obj_double);

        // Test ucl_object_toboolean_safe
        bool safe_bool;
        ucl_object_toboolean_safe(obj_double, &safe_bool);

        // Free the object
        free(obj_double);
    }

    // Test ucl_object_frombool
    ucl_object_t *obj_bool = ucl_object_frombool(bool_value);
    if (obj_bool != NULL) {
        // Test ucl_object_todouble
        double converted_double = ucl_object_todouble(obj_bool);

        // Test ucl_object_toint_safe
        int64_t int_value;
        ucl_object_toint_safe(obj_bool, &int_value);

        // Test ucl_object_toboolean
        bool converted_bool = ucl_object_toboolean(obj_bool);

        // Test ucl_object_toboolean_safe
        bool safe_bool;
        ucl_object_toboolean_safe(obj_bool, &safe_bool);

        // Free the object
        free(obj_bool);
    }

    return 0;
}