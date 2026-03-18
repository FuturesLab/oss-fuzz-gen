// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_parser_new at ucl_parser.c:2804:1 in ucl.h
// ucl_parser_free at ucl_util.c:599:6 in ucl.h
// ucl_parser_add_string at ucl_parser.c:3169:6 in ucl.h
// ucl_parser_get_comments at ucl_util.c:3915:1 in ucl.h
// ucl_parser_chunk_peek at ucl_parser.c:3201:15 in ucl.h
// ucl_parser_add_chunk_full at ucl_parser.c:2974:6 in ucl.h
// ucl_parser_get_error at ucl_util.c:665:1 in ucl.h
// ucl_parser_get_error at ucl_util.c:665:1 in ucl.h
// ucl_parser_insert_chunk at ucl_parser.c:3120:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdbool.h>

static struct ucl_parser *initialize_parser() {
    struct ucl_parser *parser = ucl_parser_new(UCL_PARSER_NO_FILEVARS);
    return parser;
}

static void cleanup_parser(struct ucl_parser *parser) {
    if (parser) {
        ucl_parser_free(parser);
    }
}

int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size) {
    struct ucl_parser *parser = initialize_parser();
    if (parser == NULL) {
        return 0;
    }

    // Ensure the data is zero-terminated to prevent overflow in ucl_parser_add_string
    char *null_terminated_data = (char *)malloc(Size + 1);
    if (null_terminated_data == NULL) {
        cleanup_parser(parser);
        return 0;
    }
    memcpy(null_terminated_data, Data, Size);
    null_terminated_data[Size] = '\0';

    // Fuzz ucl_parser_add_string
    ucl_parser_add_string(parser, null_terminated_data, Size);

    // Fuzz ucl_parser_get_comments
    const ucl_object_t *comments = ucl_parser_get_comments(parser);
    if (comments) {
        // Do something with comments if needed
    }

    // Fuzz ucl_parser_chunk_peek
    unsigned char peek_char = ucl_parser_chunk_peek(parser);

    // Fuzz ucl_parser_add_chunk_full
    ucl_parser_add_chunk_full(parser, (unsigned char *)null_terminated_data, Size, 0, UCL_DUPLICATE_APPEND, UCL_PARSE_AUTO);

    // Fuzz ucl_parser_get_error
    const char *error = ucl_parser_get_error(parser);
    if (error) {
        // Do something with error if needed
    }

    // Attempt to insert a chunk only if parser is in a valid state
    if (ucl_parser_get_error(parser) == NULL) {
        ucl_parser_insert_chunk(parser, (unsigned char *)null_terminated_data, Size);
    }

    free(null_terminated_data);
    cleanup_parser(parser);
    return 0;
}