// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_vm_alloc at janet.c:31204:10 in janet.h
// janet_vm_load at janet.c:31220:6 in janet.h
// janet_vm_free at janet.c:31212:6 in janet.h
// janet_interpreter_interrupt at janet.c:31227:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "janet.h"

static void fuzz_janet_interpreter_interrupt(JanetVM *vm) {
    janet_interpreter_interrupt(vm);
}

static void fuzz_janet_free(void *ptr) {
    janet_free(ptr);
}

static JanetVM *fuzz_janet_vm_alloc() {
    return janet_vm_alloc();
}

static void fuzz_janet_vm_load(JanetVM *from) {
    janet_vm_load(from);
}

static void fuzz_janet_vm_free(JanetVM *vm) {
    janet_vm_free(vm);
}

int LLVMFuzzerTestOneInput_684(const uint8_t *Data, size_t Size) {
    JanetVM *vm1 = fuzz_janet_vm_alloc();
    JanetVM *vm2 = fuzz_janet_vm_alloc();

    if (vm1 && vm2) {
        fuzz_janet_interpreter_interrupt(vm1);
        fuzz_janet_vm_load(vm1);
        fuzz_janet_vm_load(vm2);
    }

    fuzz_janet_vm_free(vm1);
    fuzz_janet_vm_free(vm2);

    if (Size >= sizeof(void *)) {
        void *ptr = malloc(Size);
        if (ptr) {
            memcpy(ptr, Data, Size);
            fuzz_janet_free(ptr);
        }
    }

    return 0;
}