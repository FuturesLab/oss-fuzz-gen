// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_parser_consume at parse.c:697:6 in janet.h
// janet_parser_error at parse.c:744:13 in janet.h
// janet_parser_flush at parse.c:737:6 in janet.h
// janet_parser_eof at parse.c:717:6 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_parser_init at parse.c:784:6 in janet.h
// janet_parser_deinit at parse.c:804:6 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include "janet.h"

static void fuzz_parser(JanetParser *parser, const uint8_t *data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        janet_parser_consume(parser, data[i]);
        if (janet_parser_error(parser)) {
            janet_parser_flush(parser);
        }
    }
    janet_parser_eof(parser);
}

int LLVMFuzzerTestOneInput_101(const uint8_t *Data, size_t Size) {
    // Initialize the Janet environment
    janet_init();

    JanetParser parser;
    janet_parser_init(&parser);

    fuzz_parser(&parser, Data, Size);

    janet_parser_deinit(&parser);

    // Deinitialize the Janet environment
    janet_deinit();

    return 0;
}