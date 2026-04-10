// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_nanbox_from_double at janet.c:37710:7 in janet.h
// janet_nanbox_from_double at janet.c:37710:7 in janet.h
// janet_nanbox_from_pointer at janet.c:37686:7 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_in at value.c:453:7 in janet.h
// janet_equals at value.c:249:5 in janet.h
// janet_length at value.c:641:9 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

static Janet random_janet_value(const uint8_t *Data, size_t Size) {
    Janet value;
    if (Size < 1) return janet_wrap_nil();
    switch (Data[0] % 5) {
        case 0:
            value = janet_wrap_nil();
            break;
        case 1:
            value = janet_wrap_boolean(Data[0] % 2);
            break;
        case 2:
            value = janet_wrap_number((double)(Data[0]));
            break;
        case 3:
            value = janet_wrap_integer((int32_t)(Data[0]));
            break;
        case 4:
        default:
            value = janet_wrap_pointer((void *)(uintptr_t)(Data[0]));
            break;
    }
    return value;
}

int LLVMFuzzerTestOneInput_668(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    // Initialize the Janet environment
    if (!janet_init()) {
        return 0;
    }

    Janet ds = random_janet_value(Data, Size);
    Janet key = random_janet_value(Data + 1, Size - 1);

    Janet result_in;
    int result_equals;
    JanetType result_type;
    int32_t result_length;
    int result_checktype;

    // Fuzz janet_in
    result_in = janet_in(ds, key);

    // Fuzz janet_equals
    result_equals = janet_equals(ds, key);

    // Fuzz janet_type
    result_type = janet_type(ds);

    // Fuzz janet_length
    result_length = janet_length(ds);

    // Fuzz janet_checktype
    result_checktype = janet_checktype(ds, result_type);

    // Handle results (usually logging or further processing)
    (void)result_in;
    (void)result_equals;
    (void)result_type;
    (void)result_length;
    (void)result_checktype;

    // Cleanup the Janet environment
    janet_deinit();

    return 0;
}