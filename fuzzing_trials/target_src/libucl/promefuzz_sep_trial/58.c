// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_parser_new at ucl_parser.c:2804:1 in ucl.h
// ucl_parser_free at ucl_util.c:599:6 in ucl.h
// ucl_parser_set_default_priority at ucl_parser.c:2840:6 in ucl.h
// ucl_parser_set_filevars at ucl_util.c:1977:6 in ucl.h
// ucl_parser_add_string_priority at ucl_parser.c:3154:6 in ucl.h
// ucl_parser_add_file_full at ucl_util.c:2012:6 in ucl.h
// ucl_parser_add_file_priority at ucl_util.c:2043:6 in ucl.h
// ucl_parser_add_chunk_full at ucl_parser.c:2974:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

static struct ucl_parser *initialize_parser() {
    return ucl_parser_new(0);
}

static void cleanup_parser(struct ucl_parser *parser) {
    if (parser) {
        ucl_parser_free(parser);
    }
}

int LLVMFuzzerTestOneInput_58(const uint8_t *Data, size_t Size) {
    struct ucl_parser *parser = initialize_parser();
    if (!parser) {
        return 0;
    }

    // Test ucl_parser_set_default_priority
    if (Size > 0) {
        unsigned priority = Data[0] % 17; // Priority range 0-16
        ucl_parser_set_default_priority(parser, priority);
    }

    // Test ucl_parser_set_filevars
    const char *filename = "./dummy_file";
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd != -1) {
        write(fd, Data, Size);
        close(fd);
    }
    ucl_parser_set_filevars(parser, filename, true);

    // Test ucl_parser_add_string_priority
    if (Size > 2) {
        unsigned priority = Data[1] % 17;
        ucl_parser_add_string_priority(parser, (const char *)Data, Size, priority);
    }

    // Test ucl_parser_add_file_full
    if (Size > 5) {
        unsigned priority = Data[2] % 17;
        enum ucl_duplicate_strategy strat = Data[3] % 4;
        enum ucl_parse_type parse_type = Data[4] % 4;
        ucl_parser_add_file_full(parser, filename, priority, strat, parse_type);
    }

    // Test ucl_parser_add_file_priority
    if (Size > 3) {
        unsigned priority = Data[3] % 17;
        ucl_parser_add_file_priority(parser, filename, priority);
    }

    // Test ucl_parser_add_chunk_full
    if (Size > 6) {
        unsigned priority = Data[4] % 17;
        enum ucl_duplicate_strategy strat = Data[5] % 4;
        enum ucl_parse_type parse_type = Data[6] % 4;
        ucl_parser_add_chunk_full(parser, Data, Size, priority, strat, parse_type);
    }

    cleanup_parser(parser);
    return 0;
}