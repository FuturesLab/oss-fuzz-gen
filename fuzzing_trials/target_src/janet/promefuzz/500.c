// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_parser_init at parse.c:784:6 in janet.h
// janet_parser_consume at parse.c:697:6 in janet.h
// janet_parser_flush at parse.c:737:6 in janet.h
// janet_parser_eof at parse.c:717:6 in janet.h
// janet_parser_has_more at parse.c:855:5 in janet.h
// janet_parser_produce at parse.c:756:7 in janet.h
// janet_parser_deinit at parse.c:804:6 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static void write_dummy_file(const uint8_t *data, size_t size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_500(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Initialize the Janet VM
    if (!janet_init()) {
        return 0;
    }

    JanetParser parser;
    janet_parser_init(&parser);

    for (size_t i = 0; i < Size; i++) {
        janet_parser_consume(&parser, Data[i]);
    }

    if (Size % 2 == 0) {
        janet_parser_flush(&parser);
    }

    if (Size % 3 == 0) {
        janet_parser_eof(&parser);
    }

    while (janet_parser_has_more(&parser)) {
        Janet result = janet_parser_produce(&parser);
        (void)result; // Suppress unused variable warning
    }

    janet_parser_deinit(&parser);

    // Deinitialize the Janet VM
    janet_deinit();

    return 0;
}