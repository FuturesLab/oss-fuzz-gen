// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_core_env at janet.c:7992:13 in janet.h
// janet_register at janet.c:34286:6 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_addtimeout at janet.c:9521:6 in janet.h
// janet_addtimeout_nil at janet.c:9534:6 in janet.h
// janet_sleep_await at janet.c:12093:22 in janet.h
// janet_nanbox_from_double at janet.c:37710:7 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "janet.h"

static void setup_janet_environment() {
    // Initialize Janet runtime and environment
    janet_init();
    JanetTable *env = janet_core_env(NULL);
    janet_register("core", env);
}

static void cleanup_janet_environment() {
    // Deinitialize Janet runtime
    janet_deinit();
}

static void fuzz_janet_addtimeout(const uint8_t *Data, size_t Size) {
    if (Size >= sizeof(double)) {
        double sec;
        memcpy(&sec, Data, sizeof(double));
        janet_addtimeout(sec);
    }
}

static void fuzz_janet_addtimeout_nil(const uint8_t *Data, size_t Size) {
    if (Size >= sizeof(double)) {
        double sec;
        memcpy(&sec, Data, sizeof(double));
        janet_addtimeout_nil(sec);
    }
}

static void fuzz_janet_sleep_await(const uint8_t *Data, size_t Size) {
    if (Size >= sizeof(double)) {
        double sec;
        memcpy(&sec, Data, sizeof(double));
        janet_sleep_await(sec);
    }
}

static void fuzz_janet_wrap_number(const uint8_t *Data, size_t Size) {
    if (Size >= sizeof(double)) {
        double x;
        memcpy(&x, Data, sizeof(double));
        Janet result = janet_wrap_number(x);
        (void)result; // Suppress unused variable warning
    }
}

int LLVMFuzzerTestOneInput_635(const uint8_t *Data, size_t Size) {
    setup_janet_environment();
    
    fuzz_janet_addtimeout(Data, Size);
    fuzz_janet_addtimeout_nil(Data, Size);
    fuzz_janet_sleep_await(Data, Size);
    fuzz_janet_wrap_number(Data, Size);
    
    cleanup_janet_environment();
    return 0;
}