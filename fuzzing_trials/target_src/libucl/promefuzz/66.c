// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_type at ucl_util.c:3068:1 in ucl.h
// ucl_object_type_to_string at ucl_util.c:3879:1 in ucl.h
// ucl_object_new_full at ucl_util.c:2992:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_string_to_type at ucl_util.c:3845:6 in ucl.h
// ucl_object_new_userdata at ucl_util.c:3045:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdbool.h>

static const char *type_strings[] = {
    "object", "array", "int", "float", "string", "boolean", "time", "userdata", "null"
};

static void fuzz_ucl_object_type(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(ucl_object_t)) return;
    ucl_object_t *obj = (ucl_object_t *)Data;
    ucl_object_type(obj);
}

static void fuzz_ucl_object_type_to_string(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(ucl_type_t)) return;
    ucl_type_t type = *((ucl_type_t *)Data);
    ucl_object_type_to_string(type);
}

static void fuzz_ucl_object_new_full(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(ucl_type_t) + sizeof(unsigned)) return;
    ucl_type_t type = *((ucl_type_t *)Data);
    unsigned priority = *((unsigned *)(Data + sizeof(ucl_type_t)));
    ucl_object_t *obj = ucl_object_new_full(type, priority);
    if (obj) {
        ucl_object_unref(obj);
    }
}

static void fuzz_ucl_object_typed_new(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(ucl_type_t)) return;
    ucl_type_t type = *((ucl_type_t *)Data);
    ucl_object_t *obj = ucl_object_typed_new(type);
    if (obj) {
        ucl_object_unref(obj);
    }
}

static void fuzz_ucl_object_string_to_type(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    char *input = (char *)malloc(Size + 1);
    if (!input) return;
    memcpy(input, Data, Size);
    input[Size] = '\0';
    ucl_type_t res;
    ucl_object_string_to_type(input, &res);
    free(input);
}

static void dummy_dtor(void *ptr) {
    // Dummy destructor
}

static void dummy_emitter(void *ptr) {
    // Dummy emitter
}

static void fuzz_ucl_object_new_userdata(const uint8_t *Data, size_t Size) {
    void *ptr = (void *)Data;
    ucl_object_t *obj = ucl_object_new_userdata(dummy_dtor, dummy_emitter, ptr);
    if (obj) {
        ucl_object_unref(obj);
    }
}

int LLVMFuzzerTestOneInput_66(const uint8_t *Data, size_t Size) {
    fuzz_ucl_object_type(Data, Size);
    fuzz_ucl_object_type_to_string(Data, Size);
    fuzz_ucl_object_new_full(Data, Size);
    fuzz_ucl_object_typed_new(Data, Size);
    fuzz_ucl_object_string_to_type(Data, Size);
    fuzz_ucl_object_new_userdata(Data, Size);
    return 0;
}