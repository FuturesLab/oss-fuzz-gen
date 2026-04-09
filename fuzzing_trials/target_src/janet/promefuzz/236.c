// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_checkuint16 at janet.c:34556:5 in janet.h
// janet_array at janet.c:1562:13 in janet.h
// janet_nanbox_from_pointer at janet.c:37686:7 in janet.h
// janet_putindex at value.c:718:6 in janet.h
// janet_hash at value.c:309:9 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <janet.h>

static Janet generate_janet_value(const uint8_t *data, size_t size) {
    Janet x;
    if (size >= sizeof(uint64_t)) {
        x.u64 = *((uint64_t *)data);
    } else {
        x.u64 = 0;
    }
    return x;
}

int LLVMFuzzerTestOneInput_236(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Initialize Janet environment
    janet_init();

    Janet x = generate_janet_value(Data, Size);

    // Fuzz janet_checkuint16
    int result_checkuint16 = janet_checkuint16(x);

    // Fuzz janet_checktypes with a random typeflag
    int typeflags = (int)(Data[0]); // Simple conversion for demonstration
    int result_checktypes = janet_checktypes(x, typeflags);

    // Fuzz janet_truthy
    int result_truthy = janet_truthy(x);

    // Fuzz janet_putindex
    JanetArray *array = janet_array(10);
    int32_t index = (int32_t)(Size >= 4 ? *((int32_t *)Data) : 0);
    Janet value = generate_janet_value(Data, Size);
    janet_putindex(janet_wrap_array(array), index, value);

    // Fuzz janet_hash
    int32_t result_hash = janet_hash(x);

    // Prevent unused variable warnings
    (void)result_checkuint16;
    (void)result_checktypes;
    (void)result_truthy;
    (void)result_hash;

    // Clean up Janet environment
    janet_deinit();

    return 0;
}