// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_parser_new at ucl_parser.c:2804:1 in ucl.h
// ucl_parser_add_string at ucl_parser.c:3169:6 in ucl.h
// ucl_parser_insert_chunk at ucl_parser.c:3120:6 in ucl.h
// ucl_parser_add_chunk_full at ucl_parser.c:2974:6 in ucl.h
// ucl_parser_chunk_peek at ucl_parser.c:3201:15 in ucl.h
// ucl_parser_get_comments at ucl_util.c:3915:1 in ucl.h
// ucl_parser_free at ucl_util.c:599:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void write_to_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_56(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Initialize a new parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (!parser) return 0;

    // Fuzz ucl_parser_add_string
    if (ucl_parser_add_string(parser, (const char *)Data, Size)) {
        // Only proceed if the string was successfully added
        // Fuzz ucl_parser_insert_chunk
        ucl_parser_insert_chunk(parser, Data, Size);

        // Fuzz ucl_parser_add_chunk_full
        ucl_parser_add_chunk_full(parser, Data, Size, 0, UCL_DUPLICATE_APPEND, UCL_PARSE_UCL);

        // Fuzz ucl_parser_chunk_peek
        unsigned char peeked_char = ucl_parser_chunk_peek(parser);

        // Fuzz ucl_parser_get_comments
        const ucl_object_t *comments = ucl_parser_get_comments(parser);
    }

    // Cleanup
    ucl_parser_free(parser);

    // Write data to a dummy file and test file-based parsing if needed
    write_to_dummy_file(Data, Size);

    return 0;
}