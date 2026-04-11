// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_nanbox_from_double at janet.c:37710:7 in janet.h
// janet_nanbox_from_double at janet.c:37710:7 in janet.h
// janet_wrap_number_safe at janet.c:37674:7 in janet.h
// janet_getnumber at janet.c:4511:1 in janet.h
// janet_optnumber at janet.c:4526:1 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "janet.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_507(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) {
        return 0;
    }

    // Initialize Janet VM
    janet_init();

    double input_number;
    memcpy(&input_number, Data, sizeof(double));

    // Test janet_wrap_number
    Janet wrapped_number = janet_wrap_number(input_number);

    // Test janet_nanbox_from_double
    Janet nanbox_number = janet_nanbox_from_double(input_number);

    // Test janet_wrap_number_safe
    Janet safe_wrapped_number = janet_wrap_number_safe(input_number);

    // Prepare a Janet array for testing janet_getnumber and janet_optnumber
    Janet argv[3] = {wrapped_number, nanbox_number, safe_wrapped_number};

    // Test janet_getnumber
    if (Size > sizeof(double)) {
        int32_t index = Data[sizeof(double)] % 3;
        if (janet_checktype(argv[index], JANET_NUMBER)) {
            double extracted_number = janet_getnumber(argv, index);
        }
    }

    // Test janet_optnumber
    double default_number = 42.0;
    if (Size > sizeof(double) + 1) {
        int32_t opt_index = Data[sizeof(double) + 1] % 3;
        double opt_number = janet_optnumber(argv, 3, opt_index, default_number);
    }

    // Test janet_unwrap_number
    if (janet_checktype(wrapped_number, JANET_NUMBER)) {
        double unwrapped_number = janet_unwrap_number(wrapped_number);
    }

    // Write dummy file if needed
    write_dummy_file(Data, Size);

    // Deinitialize Janet VM
    janet_deinit();

    return 0;
}