// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_parser_new at ucl_parser.c:2804:1 in ucl.h
// ucl_parser_free at ucl_util.c:599:6 in ucl.h
// ucl_parser_add_fd_full at ucl_util.c:2066:6 in ucl.h
// ucl_parser_add_fd_priority at ucl_util.c:2104:6 in ucl.h
// ucl_parser_add_string_priority at ucl_parser.c:3154:6 in ucl.h
// ucl_parser_add_string_priority at ucl_parser.c:3154:6 in ucl.h
// ucl_parser_add_file_full at ucl_util.c:2012:6 in ucl.h
// ucl_parser_add_file_priority at ucl_util.c:2043:6 in ucl.h
// ucl_parser_set_default_priority at ucl_parser.c:2840:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void fuzz_ucl_parser_add_fd_full(struct ucl_parser *parser, const uint8_t *Data, size_t Size) {
    int fd = open("./dummy_file", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        return;
    }
    write(fd, Data, Size);
    lseek(fd, 0, SEEK_SET);
    
    unsigned priority = Data[0] & 0x0F; // Use only 4 least significant bits
    enum ucl_duplicate_strategy strat = UCL_DUPLICATE_APPEND;
    enum ucl_parse_type parse_type = UCL_PARSE_UCL;
    
    ucl_parser_add_fd_full(parser, fd, priority, strat, parse_type);
    close(fd);
}

static void fuzz_ucl_parser_add_fd_priority(struct ucl_parser *parser, const uint8_t *Data, size_t Size) {
    int fd = open("./dummy_file", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        return;
    }
    write(fd, Data, Size);
    lseek(fd, 0, SEEK_SET);
    
    unsigned priority = Data[0] & 0x0F; // Use only 4 least significant bits
    
    ucl_parser_add_fd_priority(parser, fd, priority);
    close(fd);
}

static void fuzz_ucl_parser_add_string_priority(struct ucl_parser *parser, const uint8_t *Data, size_t Size) {
    if (Size > 0) {
        unsigned priority = Data[0] & 0x0F; // Use only 4 least significant bits
        size_t len = Size - 1; // Ensure we do not read beyond buffer
        if (Data[Size - 1] != '\0') {
            // Ensure null termination
            char *null_terminated_data = (char *)malloc(Size + 1);
            if (null_terminated_data == NULL) {
                return;
            }
            memcpy(null_terminated_data, Data, Size);
            null_terminated_data[Size] = '\0';
            ucl_parser_add_string_priority(parser, null_terminated_data, len, priority);
            free(null_terminated_data);
        } else {
            ucl_parser_add_string_priority(parser, (const char *)Data, len, priority);
        }
    }
}

static void fuzz_ucl_parser_add_file_full(struct ucl_parser *parser, const uint8_t *Data, size_t Size) {
    int fd = open("./dummy_file", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        return;
    }
    write(fd, Data, Size);
    close(fd);
    
    unsigned priority = Data[0] & 0x0F; // Use only 4 least significant bits
    enum ucl_duplicate_strategy strat = UCL_DUPLICATE_APPEND;
    enum ucl_parse_type parse_type = UCL_PARSE_UCL;
    
    ucl_parser_add_file_full(parser, "./dummy_file", priority, strat, parse_type);
}

static void fuzz_ucl_parser_add_file_priority(struct ucl_parser *parser, const uint8_t *Data, size_t Size) {
    int fd = open("./dummy_file", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        return;
    }
    write(fd, Data, Size);
    close(fd);
    
    unsigned priority = Data[0] & 0x0F; // Use only 4 least significant bits
    
    ucl_parser_add_file_priority(parser, "./dummy_file", priority);
}

static void fuzz_ucl_parser_set_default_priority(struct ucl_parser *parser, const uint8_t *Data, size_t Size) {
    if (Size > 0) {
        unsigned priority = Data[0] % 17; // Priority range is 0 to 16
        ucl_parser_set_default_priority(parser, priority);
    }
}

int LLVMFuzzerTestOneInput_54(const uint8_t *Data, size_t Size) {
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }
    
    fuzz_ucl_parser_add_fd_full(parser, Data, Size);
    fuzz_ucl_parser_add_fd_priority(parser, Data, Size);
    fuzz_ucl_parser_add_string_priority(parser, Data, Size);
    fuzz_ucl_parser_add_file_full(parser, Data, Size);
    fuzz_ucl_parser_add_file_priority(parser, Data, Size);
    fuzz_ucl_parser_set_default_priority(parser, Data, Size);
    
    ucl_parser_free(parser);
    return 0;
}