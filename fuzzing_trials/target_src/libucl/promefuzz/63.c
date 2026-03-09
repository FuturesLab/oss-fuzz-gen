// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_frombool at ucl_util.c:3118:1 in ucl.h
// ucl_object_toboolean at ucl_util.c:3499:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_fromdouble at ucl_util.c:3104:1 in ucl.h
// ucl_object_todouble at ucl_util.c:3446:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_toint_safe at ucl_util.c:3454:6 in ucl.h
// ucl_object_toboolean_safe at ucl_util.c:3483:6 in ucl.h
// ucl_object_fromdouble at ucl_util.c:3104:1 in ucl.h
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
#include <stdlib.h>
#include <stdio.h>

static void fuzz_ucl_object_frombool(bool bv) {
    ucl_object_t *obj = ucl_object_frombool(bv);
    if (obj) {
        bool result = ucl_object_toboolean(obj);
        ucl_object_unref(obj);
    }
}

static void fuzz_ucl_object_fromdouble(double dv) {
    ucl_object_t *obj = ucl_object_fromdouble(dv);
    if (obj) {
        double result = ucl_object_todouble(obj);
        ucl_object_unref(obj);
    }
}

static void fuzz_ucl_object_toint_safe(const ucl_object_t *obj) {
    int64_t target;
    bool success = ucl_object_toint_safe(obj, &target);
    if (success) {
        // Successfully converted to int
    }
}

static void fuzz_ucl_object_toboolean_safe(const ucl_object_t *obj) {
    bool target;
    bool success = ucl_object_toboolean_safe(obj, &target);
    if (success) {
        // Successfully converted to boolean
    }
}

int LLVMFuzzerTestOneInput_63(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double) + sizeof(bool)) {
        return 0;
    }

    // Extract a double and a boolean from the input data
    double dv;
    bool bv;
    memcpy(&dv, Data, sizeof(double));
    memcpy(&bv, Data + sizeof(double), sizeof(bool));

    // Fuzz ucl_object_frombool
    fuzz_ucl_object_frombool(bv);

    // Fuzz ucl_object_fromdouble
    fuzz_ucl_object_fromdouble(dv);

    // Create a dummy UCL object for conversion tests
    ucl_object_t *dummy_obj = ucl_object_fromdouble(dv);
    if (dummy_obj) {
        // Fuzz ucl_object_toint_safe
        fuzz_ucl_object_toint_safe(dummy_obj);

        // Fuzz ucl_object_toboolean_safe
        fuzz_ucl_object_toboolean_safe(dummy_obj);

        ucl_object_unref(dummy_obj);
    }

    return 0;
}