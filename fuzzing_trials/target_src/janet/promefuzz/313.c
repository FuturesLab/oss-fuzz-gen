// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_gcunlock at gc.c:698:6 in janet.h
// janet_gcunlock at gc.c:698:6 in janet.h
// janet_gclock at gc.c:695:5 in janet.h
// janet_gcunroot at gc.c:640:5 in janet.h
// janet_gcunrootall at gc.c:653:5 in janet.h
// janet_collect at gc.c:576:6 in janet.h
// janet_sweep at gc.c:404:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "janet.h"

static void prepare_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_313(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) {
        return 0;
    }

    Janet janet_value;
    memcpy(&janet_value, Data, sizeof(Janet));

    // Prepare dummy file
    prepare_dummy_file(Data, Size);

    // Fuzz janet_gcunlock
    janet_gcunlock(0);
    janet_gcunlock(1);

    // Fuzz janet_gclock
    int lock_count = janet_gclock();
    (void)lock_count; // Use lock_count to avoid unused variable warning

    // Fuzz janet_gcunroot
    int unroot_result = janet_gcunroot(janet_value);
    (void)unroot_result; // Use unroot_result to avoid unused variable warning

    // Fuzz janet_gcunrootall
    int unrootall_result = janet_gcunrootall(janet_value);
    (void)unrootall_result; // Use unrootall_result to avoid unused variable warning

    // Fuzz janet_collect
    janet_collect();

    // Fuzz janet_sweep
    janet_sweep();

    return 0;
}