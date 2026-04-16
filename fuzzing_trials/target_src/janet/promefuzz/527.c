// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_local_vm at janet.c:31200:10 in janet.h
// janet_interpreter_interrupt at janet.c:31227:6 in janet.h
// janet_interpreter_interrupt at janet.c:31227:6 in janet.h
// janet_vm_alloc at janet.c:31204:10 in janet.h
// janet_interpreter_interrupt at janet.c:31227:6 in janet.h
// janet_vm_free at janet.c:31212:6 in janet.h
// janet_vm_alloc at janet.c:31204:10 in janet.h
// janet_vm_save at janet.c:31216:6 in janet.h
// janet_vm_load at janet.c:31220:6 in janet.h
// janet_vm_free at janet.c:31212:6 in janet.h
// janet_vm_alloc at janet.c:31204:10 in janet.h
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
    if (vm != NULL) {
        janet_interpreter_interrupt(vm);
    }
}

static void fuzz_janet_interpreter_interrupt(JanetVM *vm) {
    janet_interpreter_interrupt(vm);
}

static void fuzz_janet_vm_alloc_and_free() {
    JanetVM *vm = janet_vm_alloc();
    if (vm != NULL) {
        janet_interpreter_interrupt(vm);
        janet_vm_free(vm);
    }
}

static void fuzz_janet_vm_load_and_save(JanetVM *vm) {
    JanetVM *new_vm = janet_vm_alloc();
    if (new_vm != NULL) {
        janet_vm_save(new_vm);
        janet_vm_load(new_vm);
        janet_vm_free(new_vm);
    }
}

int LLVMFuzzerTestOneInput_527(const uint8_t *Data, size_t Size) {
    (void)Data;
    (void)Size;

    // Fuzz janet_local_vm
    fuzz_janet_local_vm();

    // Allocate a new VM instance and fuzz janet_interpreter_interrupt
    JanetVM *vm = janet_vm_alloc();
    if (vm != NULL) {
        fuzz_janet_interpreter_interrupt(vm);

        // Fuzz janet_vm_load and janet_vm_save
        fuzz_janet_vm_load_and_save(vm);

        // Free the VM instance
        janet_vm_free(vm);
    }

    // Directly fuzz janet_vm_alloc and janet_vm_free
    fuzz_janet_vm_alloc_and_free();

    return 0;
}