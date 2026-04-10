// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_array_n at janet.c:1576:13 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_nanbox_from_pointer at janet.c:37686:7 in janet.h
// janet_nanbox_to_pointer at janet.c:37680:7 in janet.h
// janet_array_peek at janet.c:1640:7 in janet.h
// janet_array_pop at janet.c:1631:7 in janet.h
// janet_getarray at janet.c:4512:1 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

static Janet *create_dummy_janet_elements(size_t count) {
    Janet *elements = (Janet *)malloc(sizeof(Janet) * count);
    if (!elements) {
        return NULL;
    }
    for (size_t i = 0; i < count; ++i) {
        elements[i].u64 = i; // Initialize with some dummy data
    }
    return elements;
}

int LLVMFuzzerTestOneInput_616(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) {
        return 0;
    }

    // Initialize the Janet environment
    janet_init();

    int32_t n = *((int32_t *)Data);
    Data += sizeof(int32_t);
    Size -= sizeof(int32_t);

    Janet *elements = create_dummy_janet_elements(n);
    if (!elements) {
        janet_deinit();
        return 0;
    }

    JanetArray *array = janet_array_n(elements, n);
    if (!array) {
        free(elements);
        janet_deinit();
        return 0;
    }

    Janet wrapped_array = janet_wrap_array(array);
    JanetArray *unwrapped_array = janet_unwrap_array(wrapped_array);

    if (unwrapped_array) {
        janet_array_peek(unwrapped_array);
        janet_array_pop(unwrapped_array);
    }

    if (Size > 0) {
        int32_t index = Data[0] % n; // Ensure index is within bounds
        janet_getarray(elements, index);
    }

    free(elements);

    // Deinitialize the Janet environment
    janet_deinit();
    
    return 0;
}