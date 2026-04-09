// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_local_vm at janet.c:31200:10 in janet.h
// janet_interpreter_interrupt at janet.c:31227:6 in janet.h
// janet_loop1_interrupt at janet.c:10456:6 in janet.h
// janet_interpreter_interrupt_handled at janet.c:31232:6 in janet.h
// janet_vm_save at janet.c:31216:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <setjmp.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_284(const uint8_t *Data, size_t Size) {
    // Prepare the environment
    JanetVM *vm = janet_local_vm();

    // Fuzz janet_interpreter_interrupt
    janet_interpreter_interrupt(vm);

    // Fuzz janet_loop1_interrupt
    janet_loop1_interrupt(vm);

    // Fuzz janet_interpreter_interrupt_handled
    janet_interpreter_interrupt_handled(vm);

    // Since JanetVM is an incomplete type, we cannot allocate it directly.
    // We will assume janet_vm_save is used to save the state into an existing VM instance.
    // For fuzzing purposes, we will use the local VM instance itself.
    janet_vm_save(vm);

    return 0;
}