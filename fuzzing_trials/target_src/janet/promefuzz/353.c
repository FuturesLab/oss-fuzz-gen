// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_nanbox_from_cpointer at janet.c:37698:7 in janet.h
// janet_nanbox_from_pointer at janet.c:37686:7 in janet.h
// janet_nanbox_to_pointer at janet.c:37680:7 in janet.h
// janet_nanbox_to_pointer at janet.c:37680:7 in janet.h
// janet_nanbox_from_pointer at janet.c:37686:7 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

static void prepare_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_353(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(void *) + sizeof(uint64_t)) {
        return 0;
    }

    prepare_dummy_file(Data, Size);

    const void *ptr = (const void *)(Data);
    uint64_t tagmask = *(uint64_t *)(Data + sizeof(void *));

    // Fuzz janet_nanbox_from_cpointer
    Janet janet_value_from_cpointer = janet_nanbox_from_cpointer(ptr, tagmask);

    // Fuzz janet_wrap_pointer
    Janet janet_value_wrap_pointer = janet_wrap_pointer((void *)ptr);

    // Fuzz janet_unwrap_pointer
    void *unwrapped_pointer = janet_unwrap_pointer(janet_value_wrap_pointer);

    // Fuzz janet_nanbox_to_pointer
    void *nanbox_to_pointer = janet_nanbox_to_pointer(janet_value_from_cpointer);

    // Fuzz janet_nanbox_from_pointer
    Janet janet_value_from_pointer = janet_nanbox_from_pointer((void *)ptr, tagmask);

    return 0;
}