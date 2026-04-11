// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_parser_init at parse.c:784:6 in janet.h
// janet_parser_flush at parse.c:737:6 in janet.h
// janet_parser_eof at parse.c:717:6 in janet.h
// janet_parser_deinit at parse.c:804:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static void dummy_finalizer(void *mem) {
    // Custom finalizer logic can go here, for now it does nothing.
}

int LLVMFuzzerTestOneInput_480(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(JanetParser)) {
        return 0; // Not enough data to initialize a parser
    }

    // Allocate parser on the heap to avoid stack-buffer-underflow
    JanetParser *parser = (JanetParser *)malloc(sizeof(JanetParser));
    if (!parser) {
        return 0; // Handle allocation failure
    }

    // Initialize the parser
    janet_parser_init(parser);

    // Ensure the memory block is suitable for a finalizer
    // Assuming `janet_sfinalizer` requires memory managed by Janet's GC
    // We will not set a finalizer directly on the parser
    // janet_sfinalizer(parser, dummy_finalizer);

    // Simulate parsing by using some of the input data
    if (Size > 0) {
        parser->line = Data[0] % 256;
    }
    if (Size > 1) {
        parser->column = Data[1] % 256;
    }

    // Flush the parser to test error recovery
    janet_parser_flush(parser);

    // Signal end of parsing
    janet_parser_eof(parser);

    // Deinitialize the parser to clean up resources
    janet_parser_deinit(parser);

    // Free the allocated parser
    free(parser);

    return 0;
}