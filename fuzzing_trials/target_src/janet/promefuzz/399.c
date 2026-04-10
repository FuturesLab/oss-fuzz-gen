// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_local_vm at janet.c:31200:10 in janet.h
// janet_interpreter_interrupt at janet.c:31227:6 in janet.h
// janet_vm_alloc at janet.c:31204:10 in janet.h
// janet_vm_free at janet.c:31212:6 in janet.h
// janet_vm_alloc at janet.c:31204:10 in janet.h
// janet_vm_alloc at janet.c:31204:10 in janet.h
// janet_vm_save at janet.c:31216:6 in janet.h
// janet_vm_load at janet.c:31220:6 in janet.h
// janet_vm_free at janet.c:31212:6 in janet.h
// janet_vm_free at janet.c:31212:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <setjmp.h>
#include "janet.h"

static void fuzz_janet_local_vm() {
    JanetVM *vm = janet_local_vm();
    if (vm) {
        janet_interpreter_interrupt(vm);
    }
}

static void fuzz_janet_vm_alloc_free() {
    JanetVM *vm = janet_vm_alloc();
    if (vm) {
        janet_vm_free(vm);
    }
}

static void fuzz_janet_vm_save_load() {
    JanetVM *vm1 = janet_vm_alloc();
    JanetVM *vm2 = janet_vm_alloc();
    if (vm1 && vm2) {
        janet_vm_save(vm1);
        janet_vm_load(vm2);
    }
    if (vm1) janet_vm_free(vm1);
    if (vm2) janet_vm_free(vm2);
}

int LLVMFuzzerTestOneInput_399(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) {
        return 0;
    }

    // Use the first byte of data to decide which function to fuzz
    switch (Data[0] % 3) {
        case 0:
            fuzz_janet_local_vm();
            break;
        case 1:
            fuzz_janet_vm_alloc_free();
            break;
        case 2:
            fuzz_janet_vm_save_load();
            break;
        default:
            break;
    }

    return 0;
}