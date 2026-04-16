// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_smalloc at gc.c:706:7 in janet.h
// janet_srealloc at gc.c:735:7 in janet.h
// janet_abstract_begin at janet.c:1330:7 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "janet.h"

// Initialize and deinitialize Janet VM
static void initialize_janet_vm() {
    janet_init();
}

static void deinitialize_janet_vm() {
    janet_deinit();
}

static const JanetAbstractType dummy_type = {
    "dummy", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

int LLVMFuzzerTestOneInput_499(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize Janet VM
    initialize_janet_vm();

    // Fuzz janet_smalloc
    size_t smalloc_size = Data[0];
    void *smalloc_mem = janet_smalloc(smalloc_size);

    // Fuzz janet_malloc
    size_t malloc_size = (Size > 1) ? Data[1] : 0;
    void *malloc_mem = janet_malloc(malloc_size);

    // Fuzz janet_srealloc
    if (smalloc_mem) {
        size_t srealloc_size = (Size > 2) ? Data[2] : 0;
        smalloc_mem = janet_srealloc(smalloc_mem, srealloc_size);
    }

    // Fuzz janet_abstract_begin
    size_t abstract_size = (Size > 3) ? Data[3] : 0;
    void *abstract_mem = janet_abstract_begin(&dummy_type, abstract_size);

    // Fuzz janet_realloc
    if (malloc_mem) {
        size_t realloc_size = (Size > 4) ? Data[4] : 0;
        malloc_mem = janet_realloc(malloc_mem, realloc_size);
    }

    // Deinitialize Janet VM
    deinitialize_janet_vm();

    return 0;
}