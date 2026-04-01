// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_parser_new at ucl_parser.c:2804:1 in ucl.h
// ucl_parser_set_filevars at ucl_util.c:1977:6 in ucl.h
// ucl_parser_get_error_code at ucl_util.c:678:5 in ucl.h
// ucl_parser_get_default_priority at ucl_parser.c:2851:5 in ucl.h
// ucl_parser_add_chunk_full at ucl_parser.c:2974:6 in ucl.h
// ucl_parser_add_fd at ucl_util.c:2115:6 in ucl.h
// ucl_parser_free at ucl_util.c:599:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

static void write_to_dummy_file(const uint8_t *Data, size_t Size) {
    int fd = open("./dummy_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd >= 0) {
        write(fd, Data, Size);
        close(fd);
    }
}

int LLVMFuzzerTestOneInput_93(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Prepare filename
    char *filename = NULL;
    if (Size > 1) {
        filename = (char *)malloc(Size);
        if (filename) {
            memcpy(filename, Data, Size - 1);
            filename[Size - 1] = '\0';
        }
    }

    // Set file variables in parser
    bool need_expand = Data[0] % 2 == 0; // Arbitrary choice for need_expand
    ucl_parser_set_filevars(parser, filename, need_expand);

    // Get error code
    int error_code = ucl_parser_get_error_code(parser);

    // Get default priority
    int default_priority = ucl_parser_get_default_priority(parser);

    // Add chunk full
    if (Size > 0) { // Ensure there's data to add
        unsigned priority = Data[0] & 0xF; // Use 4 least significant bits
        enum ucl_duplicate_strategy strat = UCL_DUPLICATE_APPEND;
        enum ucl_parse_type parse_type = UCL_PARSE_AUTO;

        ucl_parser_add_chunk_full(parser, Data, Size, priority, strat, parse_type);
    }

    // Write to a dummy file and add via file descriptor
    write_to_dummy_file(Data, Size);
    int fd = open("./dummy_file", O_RDONLY);
    if (fd >= 0) {
        ucl_parser_add_fd(parser, fd);
        close(fd);
    }

    // Cleanup
    ucl_parser_free(parser);
    free(filename);

    return 0;
}