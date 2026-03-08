// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_parser_new at ucl_parser.c:2804:1 in ucl.h
// ucl_parser_free at ucl_util.c:599:6 in ucl.h
// ucl_parser_add_chunk at ucl_parser.c:3109:6 in ucl.h
// ucl_parser_add_chunk_priority at ucl_parser.c:3097:6 in ucl.h
// ucl_parser_add_string at ucl_parser.c:3169:6 in ucl.h
// ucl_parser_add_chunk_full at ucl_parser.c:2974:6 in ucl.h
// ucl_parser_add_fd at ucl_util.c:2115:6 in ucl.h
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

// Forward declaration of the ucl_object_t structure
typedef struct ucl_object_s ucl_object_t;

static struct ucl_parser* initialize_parser() {
    return ucl_parser_new(0);
}

static void cleanup_parser(struct ucl_parser* parser) {
    if (parser) {
        ucl_parser_free(parser);
    }
}

int LLVMFuzzerTestOneInput_70(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    struct ucl_parser* parser = initialize_parser();
    if (!parser) {
        return 0;
    }

    // Fuzz ucl_parser_add_chunk
    ucl_parser_add_chunk(parser, Data, Size);

    // Fuzz ucl_parser_add_chunk_priority with varied priority
    unsigned priority = Data[0] & 0x0F; // Use only the lower 4 bits
    ucl_parser_add_chunk_priority(parser, Data, Size, priority);

    // Fuzz ucl_parser_add_string
    char *string_data = (char *)malloc(Size + 1);
    if (string_data) {
        memcpy(string_data, Data, Size);
        string_data[Size] = '\0'; // Null-terminate
        ucl_parser_add_string(parser, string_data, Size);
        free(string_data);
    }

    // Fuzz ucl_parser_add_chunk_full with varied parameters
    enum ucl_duplicate_strategy strat = UCL_DUPLICATE_APPEND;
    enum ucl_parse_type parse_type = UCL_PARSE_UCL;
    ucl_parser_add_chunk_full(parser, Data, Size, priority, strat, parse_type);

    // Fuzz ucl_parser_add_fd
    int fd = open("./dummy_file", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd != -1) {
        write(fd, Data, Size);
        lseek(fd, 0, SEEK_SET);
        ucl_parser_add_fd(parser, fd);
        close(fd);
    }

    cleanup_parser(parser);
    return 0;
}