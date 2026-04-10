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

int LLVMFuzzerTestOneInput_1431(const uint8_t *Data, size_t Size) {
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