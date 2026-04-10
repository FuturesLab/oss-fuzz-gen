// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_nanbox_from_double at janet.c:37710:7 in janet.h
// janet_string at string.c:49:16 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_symbol at janet.c:32957:16 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_symbol at janet.c:32957:16 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_array at janet.c:1562:13 in janet.h
// janet_tuple_n at tuple.c:50:14 in janet.h
// janet_table at janet.c:33121:13 in janet.h
// janet_struct_begin at janet.c:32494:10 in janet.h
// janet_buffer at buffer.c:82:14 in janet.h
// janet_nanbox_from_pointer at janet.c:37686:7 in janet.h
// janet_nanbox_from_pointer at janet.c:37686:7 in janet.h
// janet_nanbox_from_pointer at janet.c:37686:7 in janet.h
// janet_nanbox_from_pointer at janet.c:37686:7 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_getboolean at janet.c:4523:1 in janet.h
// janet_optinteger at janet.c:4856:9 in janet.h
// janet_putindex at value.c:718:6 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <janet.h>

static Janet generate_random_janet_value(const uint8_t *Data, size_t Size, size_t *offset) {
    Janet value;
    if (*offset >= Size) return janet_wrap_nil();
    switch (Data[(*offset)++] % 15) {
        case 0: value = janet_wrap_nil(); break;
        case 1: value = janet_wrap_boolean(Data[(*offset)++] % 2); break;
        case 2: value = janet_wrap_number((double)(Data[(*offset)++])); break;
        case 3: 
            if (*offset < Size) {
                size_t len = (Size - *offset);
                value = janet_wrap_string(janet_string(Data + *offset, len));
                *offset += len;
            } else {
                value = janet_wrap_nil();
            }
            break;
        case 4: 
            if (*offset < Size) {
                size_t len = (Size - *offset);
                value = janet_wrap_symbol(janet_symbol(Data + *offset, len));
                *offset += len;
            } else {
                value = janet_wrap_nil();
            }
            break;
        case 5: 
            if (*offset < Size) {
                size_t len = (Size - *offset);
                value = janet_wrap_keyword(janet_keyword(Data + *offset, len));
                *offset += len;
            } else {
                value = janet_wrap_nil();
            }
            break;
        case 6: value = janet_wrap_array(janet_array(0)); break;
        case 7: value = janet_wrap_tuple(janet_tuple_n(NULL, 0)); break;
        case 8: value = janet_wrap_table(janet_table(0)); break;
        case 9: value = janet_wrap_struct(janet_struct_begin(0)); break;
        case 10: value = janet_wrap_buffer(janet_buffer(0)); break;
        case 11: value = janet_wrap_function(NULL); break;
        case 12: value = janet_wrap_cfunction(NULL); break;
        case 13: value = janet_wrap_abstract(NULL); break;
        case 14: value = janet_wrap_pointer(NULL); break;
        default: value = janet_wrap_nil(); break;
    }
    return value;
}

int LLVMFuzzerTestOneInput_596(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Ensure Janet is initialized before using its API
    janet_init();

    size_t offset = 0;
    Janet argv[10];
    for (int i = 0; i < 10 && offset < Size; i++) {
        argv[i] = generate_random_janet_value(Data, Size, &offset);
    }

    int32_t n = (int32_t)(Data[offset % Size] % 10);
    int32_t dflt = (int32_t)(Data[offset % Size]);
    JanetType type = (JanetType)(Data[offset % Size] % 15);
    Janet ds = generate_random_janet_value(Data, Size, &offset);
    Janet value = generate_random_janet_value(Data, Size, &offset);

    // Check bounds before accessing argv
    if (n < 10) {
        // Fuzz janet_getboolean
        int boolean_result = janet_getboolean(argv, n);

        // Fuzz janet_truthy
        int truthy_result = janet_truthy(argv[n]);

        // Fuzz janet_checktype
        int checktype_result = janet_checktype(argv[n], type);

        // Fuzz janet_optinteger
        int32_t optinteger_result = janet_optinteger(argv, 10, n, dflt);
    }

    // Fuzz janet_putindex
    // Ensure ds is a valid Janet data structure that can accept an index
    if (janet_checktype(ds, JANET_ARRAY) || janet_checktype(ds, JANET_BUFFER) || janet_checktype(ds, JANET_TABLE)) {
        janet_putindex(ds, n, value);
    }

    // Clean up Janet environment
    janet_deinit();

    return 0;
}