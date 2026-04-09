#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static JanetFunction *create_random_function() {
    JanetFuncDef *def = (JanetFuncDef *)malloc(sizeof(JanetFuncDef));
    if (!def) return NULL;
    memset(def, 0, sizeof(JanetFuncDef));
    return janet_thunk(def);
}

static JanetFiber *create_random_fiber() {
    JanetFunction *callee = create_random_function();
    if (!callee) return NULL;
    int32_t capacity = rand() % 100;
    int32_t argc = rand() % 10;
    Janet *argv = (Janet *)malloc(sizeof(Janet) * argc);
    if (!argv) {
        free(callee->def);
        free(callee);
        return NULL;
    }
    for (int32_t i = 0; i < argc; ++i) {
        argv[i].u64 = rand();
    }
    JanetFiber *fiber = janet_fiber(callee, capacity, argc, argv);
    free(argv);
    return fiber;
}

int LLVMFuzzerTestOneInput_1287(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return 0;

    janet_init();

    Janet x;
    memcpy(&x, Data, sizeof(Janet));

    JanetFunction *thunk = janet_thunk_delay(x);

    JanetFiber *fiber = create_random_fiber();
    if (fiber) {
        JanetFunction *callee = create_random_function();
        if (callee) {
            Janet *argv = (Janet *)malloc(sizeof(Janet) * fiber->capacity);
            if (argv) {
                for (int32_t i = 0; i < fiber->capacity; ++i) {
                    argv[i].u64 = rand();
                }
                janet_fiber_reset(fiber, callee, fiber->capacity, argv);
                free(argv);
            }
        }
    }

    janet_deinit();

    return 0;
}