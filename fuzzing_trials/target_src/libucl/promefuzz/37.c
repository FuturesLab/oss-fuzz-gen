// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_fromdouble at ucl_util.c:3104:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_todouble_safe at ucl_util.c:3425:6 in ucl.h
// ucl_object_toint_safe at ucl_util.c:3454:6 in ucl.h
// ucl_object_frombool at ucl_util.c:3118:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_toboolean at ucl_util.c:3499:6 in ucl.h
// ucl_object_toboolean_safe at ucl_util.c:3483:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

static void fuzz_ucl_object_fromdouble(double dv) {
    ucl_object_t *obj = ucl_object_fromdouble(dv);
    if (obj) {
        ucl_object_unref(obj);
    }
}

static void fuzz_ucl_object_todouble_safe(const ucl_object_t *obj) {
    double target;
    ucl_object_todouble_safe(obj, &target);
}

static void fuzz_ucl_object_toint_safe(const ucl_object_t *obj) {
    int64_t target;
    ucl_object_toint_safe(obj, &target);
}

static void fuzz_ucl_object_frombool(bool bv) {
    ucl_object_t *obj = ucl_object_frombool(bv);
    if (obj) {
        ucl_object_unref(obj);
    }
}

static void fuzz_ucl_object_toboolean(const ucl_object_t *obj) {
    ucl_object_toboolean(obj);
}

static void fuzz_ucl_object_toboolean_safe(const ucl_object_t *obj) {
    bool target;
    ucl_object_toboolean_safe(obj, &target);
}

int LLVMFuzzerTestOneInput_37(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double) + sizeof(bool)) return 0;

    double dv;
    memcpy(&dv, Data, sizeof(double));
    fuzz_ucl_object_fromdouble(dv);

    bool bv = Data[sizeof(double)] % 2;
    fuzz_ucl_object_frombool(bv);

    ucl_object_t obj;
    memset(&obj, 0, sizeof(ucl_object_t));
    obj.type = UCL_FLOAT;
    obj.value.dv = dv;

    fuzz_ucl_object_todouble_safe(&obj);
    fuzz_ucl_object_toint_safe(&obj);
    fuzz_ucl_object_toboolean(&obj);
    fuzz_ucl_object_toboolean_safe(&obj);

    return 0;
}