// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_parser_new at ucl_parser.c:2804:1 in ucl.h
// ucl_parser_register_variable at ucl_parser.c:2913:6 in ucl.h
// ucl_parser_free at ucl_util.c:599:6 in ucl.h
// ucl_parser_set_filevars at ucl_util.c:1977:6 in ucl.h
// ucl_parser_free at ucl_util.c:599:6 in ucl.h
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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

static int write_dummy_file(const uint8_t *Data, size_t Size) {
    int fd = open("./dummy_file", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        return -1;
    }
    if (write(fd, Data, Size) != (ssize_t)Size) {
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    const char *var_name = "test_var";
    const char *var_value = "test_value";
    ucl_parser_register_variable(parser, var_name, var_value);

    if (write_dummy_file(Data, Size) != 0) {
        ucl_parser_free(parser);
        return 0;
    }

    bool set_filevars_result = ucl_parser_set_filevars(parser, "./dummy_file", false);
    if (!set_filevars_result) {
        ucl_parser_free(parser);
        return 0;
    }

    unsigned priority = Data[0] & 0xF; // Use only the 4 least significant bits
    enum ucl_duplicate_strategy strat = UCL_DUPLICATE_APPEND;
    enum ucl_parse_type parse_type = UCL_PARSE_UCL; // Changed from AUTO to UCL

    bool add_chunk_result = ucl_parser_add_chunk_full(parser, Data, Size, priority, strat, parse_type);

    // Clean up
    ucl_parser_free(parser);

    return 0;
}