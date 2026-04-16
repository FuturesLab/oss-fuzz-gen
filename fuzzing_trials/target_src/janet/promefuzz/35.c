// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_fiber at fiber.c:96:13 in janet.h
// janet_fiber_reset at fiber.c:68:13 in janet.h
// janet_schedule at janet.c:9402:6 in janet.h
// janet_cancel at janet.c:9395:6 in janet.h
// janet_getfiber at janet.c:4520:1 in janet.h
// janet_pcall at vm.c:1617:13 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

static JanetFunction *create_dummy_function() {
    JanetFunction *func = (JanetFunction *)malloc(sizeof(JanetFunction));
    if (!func) return NULL;
    func->gc.flags = 0;
    func->def = (JanetFuncDef *)malloc(sizeof(JanetFuncDef));
    if (!func->def) {
        free(func);
        return NULL;
    }
    return func;
}

static JanetFiber *create_dummy_fiber(int32_t capacity) {
    JanetFiber *fiber = (JanetFiber *)malloc(sizeof(JanetFiber));
    if (!fiber) return NULL;
    fiber->capacity = capacity;
    fiber->data = (Janet *)malloc(capacity * sizeof(Janet));
    if (!fiber->data) {
        free(fiber);
        return NULL;
    }
    return fiber;
}

int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t) * 2) return 0;

    int32_t capacity = *((int32_t *)Data);
    int32_t argc = *((int32_t *)(Data + sizeof(int32_t)));

    JanetFunction *func = create_dummy_function();
    if (!func) return 0;

    Janet *argv = (Janet *)malloc(argc * sizeof(Janet));
    if (!argv) {
        free(func->def);
        free(func);
        return 0;
    }

    for (int i = 0; i < argc; i++) {
        argv[i].u64 = 0; // Initialize with zero or any random value
    }

    JanetFiber *fiber = janet_fiber(func, capacity, argc, argv);
    if (fiber) {
        janet_fiber_reset(fiber, func, argc, argv);
        janet_schedule(fiber, argv[0]);
        janet_cancel(fiber, argv[0]);
        JanetFiber *retrieved_fiber = janet_getfiber(argv, 0);
        if (retrieved_fiber) {
            Janet out;
            janet_pcall(func, argc, argv, &out, &fiber);
        }
        free(fiber->data);
        free(fiber);
    }

    free(argv);
    free(func->def);
    free(func);

    return 0;
}