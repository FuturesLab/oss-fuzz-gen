// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_parser_new at ucl_parser.c:2804:1 in ucl.h
// ucl_parser_register_variable at ucl_parser.c:2913:6 in ucl.h
// ucl_parser_set_filevars at ucl_util.c:1977:6 in ucl.h
// ucl_parser_add_chunk_full at ucl_parser.c:2974:6 in ucl.h
// ucl_parser_free at ucl_util.c:599:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    int fd = open("./dummy_file", O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd != -1) {
        write(fd, Data, Size);
        close(fd);
    }
}

int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Step 1: Initialize a parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Step 2: Register a variable
    const char *var_name = "test_var";
    const char *var_value = "test_value";
    ucl_parser_register_variable(parser, var_name, var_value);

    // Step 3: Set file variables
    write_dummy_file(Data, Size);
    ucl_parser_set_filevars(parser, "./dummy_file", false);

    // Step 4: Add a chunk
    unsigned priority = Data[0] & 0x0F; // Use the first byte for priority
    enum ucl_duplicate_strategy strategy = UCL_DUPLICATE_APPEND;
    enum ucl_parse_type parse_type = UCL_PARSE_AUTO;
    ucl_parser_add_chunk_full(parser, Data, Size, priority, strategy, parse_type);

    // Cleanup
    ucl_parser_free(parser);

    return 0;
}