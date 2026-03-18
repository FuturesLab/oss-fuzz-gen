// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_parser_new at ucl_parser.c:2804:1 in ucl.h
// ucl_parser_add_chunk at ucl_parser.c:3109:6 in ucl.h
// ucl_parser_chunk_skip at ucl_parser.c:3211:6 in ucl.h
// ucl_parser_add_string at ucl_parser.c:3169:6 in ucl.h
// ucl_parser_add_chunk_full at ucl_parser.c:2974:6 in ucl.h
// ucl_parser_add_chunk_priority at ucl_parser.c:3097:6 in ucl.h
// ucl_parser_get_object at ucl_util.c:590:1 in ucl.h
// ucl_parser_insert_chunk at ucl_parser.c:3120:6 in ucl.h
// ucl_parser_free at ucl_util.c:599:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ucl.h>

static void write_to_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file != NULL) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_45(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    struct ucl_parser *parser = ucl_parser_new(UCL_PARSER_DEFAULT);
    if (parser == NULL) return 0;

    // Fuzz ucl_parser_add_chunk
    ucl_parser_add_chunk(parser, Data, Size);

    // Fuzz ucl_parser_chunk_skip
    ucl_parser_chunk_skip(parser);

    // Fuzz ucl_parser_add_string
    ucl_parser_add_string(parser, (const char *)Data, Size);

    // Fuzz ucl_parser_add_chunk_full
    ucl_parser_add_chunk_full(parser, Data, Size, 0xF, UCL_DUPLICATE_APPEND, UCL_PARSE_UCL);

    // Fuzz ucl_parser_add_chunk_priority
    ucl_parser_add_chunk_priority(parser, Data, Size, 0xF);

    // Attempt to insert chunk only if parser has a top object and it is an array
    ucl_object_t *top_obj = ucl_parser_get_object(parser);
    if (top_obj != NULL && top_obj->type == UCL_ARRAY) {
        ucl_parser_insert_chunk(parser, Data, Size);
    }

    // Write data to dummy file if needed by other parts of the library
    write_to_dummy_file(Data, Size);

    ucl_parser_free(parser);

    return 0;
}