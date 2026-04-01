// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_parser_set_filevars at ucl_util.c:1977:6 in ucl.h
// ucl_parser_set_filevars at ucl_util.c:1977:6 in ucl.h
// ucl_parser_add_string_priority at ucl_parser.c:3154:6 in ucl.h
// ucl_parser_add_fd at ucl_util.c:2115:6 in ucl.h
// ucl_parser_add_file_full at ucl_util.c:2012:6 in ucl.h
// ucl_parser_add_file_priority at ucl_util.c:2043:6 in ucl.h
// ucl_parser_set_default_priority at ucl_parser.c:2840:6 in ucl.h
// ucl_parser_new at ucl_parser.c:2804:1 in ucl.h
// ucl_parser_free at ucl_util.c:599:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

static void fuzz_ucl_parser_set_filevars(struct ucl_parser *parser, const uint8_t *Data, size_t Size) {
    if (Size > 0) {
        // Use part of the data as a filename
        char *filename = strndup((const char *)Data, Size);
        bool need_expand = Data[0] % 2; // Randomize need_expand
        ucl_parser_set_filevars(parser, filename, need_expand);
        free(filename);
    } else {
        ucl_parser_set_filevars(parser, NULL, false);
    }
}

static void fuzz_ucl_parser_add_string_priority(struct ucl_parser *parser, const uint8_t *Data, size_t Size) {
    unsigned priority = Data[0] % 16; // Priority is limited to 4 bits
    // Ensure the data is null-terminated
    char *data_copy = (char *)malloc(Size + 1);
    if (data_copy != NULL) {
        memcpy(data_copy, Data, Size);
        data_copy[Size] = '\0';
        ucl_parser_add_string_priority(parser, data_copy, Size, priority);
        free(data_copy);
    }
}

static void fuzz_ucl_parser_add_fd(struct ucl_parser *parser, const uint8_t *Data, size_t Size) {
    int fd = open("./dummy_file", O_RDWR | O_CREAT, 0666);
    if (fd != -1) {
        write(fd, Data, Size);
        lseek(fd, 0, SEEK_SET); // Reset file descriptor position
        ucl_parser_add_fd(parser, fd);
        close(fd);
    }
}

static void fuzz_ucl_parser_add_file_full(struct ucl_parser *parser, const uint8_t *Data, size_t Size) {
    if (Size > 2) { // Ensure we have enough bytes for indices
        char *filename = strndup((const char *)Data, Size);
        unsigned priority = Data[0] % 16;
        enum ucl_duplicate_strategy strat = Data[1] % 4;
        enum ucl_parse_type parse_type = Data[2] % 4;
        ucl_parser_add_file_full(parser, filename, priority, strat, parse_type);
        free(filename);
    }
}

static void fuzz_ucl_parser_add_file_priority(struct ucl_parser *parser, const uint8_t *Data, size_t Size) {
    if (Size > 0) {
        char *filename = strndup((const char *)Data, Size);
        unsigned priority = Data[0] % 16;
        ucl_parser_add_file_priority(parser, filename, priority);
        free(filename);
    }
}

static void fuzz_ucl_parser_set_default_priority(struct ucl_parser *parser, const uint8_t *Data, size_t Size) {
    if (Size > 0) {
        unsigned prio = Data[0] % 17; // Priority range is 0 to 16
        ucl_parser_set_default_priority(parser, prio);
    }
}

int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size) {
    struct ucl_parser *parser = ucl_parser_new(0);

    if (parser != NULL) {
        fuzz_ucl_parser_set_filevars(parser, Data, Size);
        fuzz_ucl_parser_add_string_priority(parser, Data, Size);
        fuzz_ucl_parser_add_fd(parser, Data, Size);
        fuzz_ucl_parser_add_file_full(parser, Data, Size);
        fuzz_ucl_parser_add_file_priority(parser, Data, Size);
        fuzz_ucl_parser_set_default_priority(parser, Data, Size);

        ucl_parser_free(parser);
    }

    return 0;
}