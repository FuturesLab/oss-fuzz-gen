// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_parser_new at ucl_parser.c:2804:1 in ucl.h
// ucl_parser_free at ucl_util.c:599:6 in ucl.h
// ucl_parser_set_default_priority at ucl_parser.c:2840:6 in ucl.h
// ucl_parser_set_filevars at ucl_util.c:1977:6 in ucl.h
// ucl_parser_add_fd_full at ucl_util.c:2066:6 in ucl.h
// ucl_parser_add_fd_priority at ucl_util.c:2104:6 in ucl.h
// ucl_parser_add_fd at ucl_util.c:2115:6 in ucl.h
// ucl_parser_chunk_skip at ucl_parser.c:3211:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

static struct ucl_parser *init_parser() {
    struct ucl_parser *parser = ucl_parser_new(0);
    return parser;
}

static void cleanup_parser(struct ucl_parser *parser) {
    if (parser) {
        ucl_parser_free(parser);
    }
}

int LLVMFuzzerTestOneInput_84(const uint8_t *Data, size_t Size) {
    struct ucl_parser *parser = init_parser();
    if (!parser) {
        return 0;
    }

    // Fuzz ucl_parser_set_default_priority
    if (Size > 0) {
        unsigned prio = Data[0] % 17; // priority between 0 and 16
        ucl_parser_set_default_priority(parser, prio);
    }

    // Prepare a null-terminated string for filename
    char *filename = NULL;
    if (Size > 1) {
        size_t filename_len = Size - 1;
        filename = (char *)malloc(filename_len + 1);
        if (filename) {
            memcpy(filename, Data + 1, filename_len);
            filename[filename_len] = '\0';
        }
    }

    // Fuzz ucl_parser_set_filevars
    if (filename) {
        bool need_expand = Data[Size - 1] % 2;
        ucl_parser_set_filevars(parser, filename, need_expand);
        free(filename);
    }

    // Prepare a dummy file for file descriptor related functions
    int fd = open("./dummy_file", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd != -1) {
        // Fuzz ucl_parser_add_fd_full
        if (Size > 4) {
            unsigned priority = Data[1] % 17;
            enum ucl_duplicate_strategy strat = Data[2] % 4;
            enum ucl_parse_type parse_type = Data[3] % 4;
            ucl_parser_add_fd_full(parser, fd, priority, strat, parse_type);
        }

        // Fuzz ucl_parser_add_fd_priority
        if (Size > 2) {
            unsigned priority = Data[2] % 17;
            ucl_parser_add_fd_priority(parser, fd, priority);
        }

        // Fuzz ucl_parser_add_fd
        ucl_parser_add_fd(parser, fd);

        close(fd);
    }

    // Fuzz ucl_parser_chunk_skip
    ucl_parser_chunk_skip(parser);

    cleanup_parser(parser);
    return 0;
}