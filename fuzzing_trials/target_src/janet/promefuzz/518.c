// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_array at janet.c:1562:13 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_array_ensure at janet.c:1589:6 in janet.h
// janet_array_setcount at janet.c:1606:6 in janet.h
// janet_array_weak at janet.c:1569:13 in janet.h
// janet_array_setcount at janet.c:1606:6 in janet.h
// janet_getarray at janet.c:4512:1 in janet.h
// janet_array_ensure at janet.c:1589:6 in janet.h
// janet_optarray at janet.c:4540:1 in janet.h
// janet_array_ensure at janet.c:1589:6 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

static void initialize_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_518(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t) * 3) return 0;

    // Initialize Janet VM
    janet_init();

    int32_t capacity = ((int32_t *)Data)[0];
    int32_t growth = ((int32_t *)Data)[1];
    int32_t count = ((int32_t *)Data)[2];

    const Janet *argv = (const Janet *)(Data + sizeof(int32_t) * 3);
    int32_t argc = (Size - sizeof(int32_t) * 3) / sizeof(Janet);

    // Test janet_array
    JanetArray *array = janet_array(capacity);
    if (!array) {
        janet_deinit();
        return 0;
    }

    // Test janet_array_ensure
    janet_array_ensure(array, capacity, growth);

    // Test janet_array_setcount
    janet_array_setcount(array, count);

    // Test janet_array_weak
    JanetArray *weak_array = janet_array_weak(capacity);
    if (weak_array) {
        janet_array_setcount(weak_array, count);
    }

    // Test janet_getarray
    if (argc > 0) {
        JanetArray *retrieved_array = janet_getarray(argv, 0);
        if (retrieved_array) {
            janet_array_ensure(retrieved_array, capacity, growth);
        }
    }

    // Test janet_optarray
    JanetArray *opt_array = janet_optarray(argv, argc, 0, capacity);
    if (opt_array) {
        janet_array_ensure(opt_array, capacity, growth);
    }

    // Clean up
    // No need to free arrays explicitly as they are managed by Janet's garbage collector

    // Deinitialize Janet VM
    janet_deinit();

    return 0;
}