// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_parser_new at ucl_parser.c:2804:1 in ucl.h
// ucl_parser_get_comments at ucl_util.c:3915:1 in ucl.h
// ucl_parser_get_object at ucl_util.c:590:1 in ucl.h
// ucl_parser_free at ucl_util.c:599:6 in ucl.h
// ucl_object_emit_file_funcs at ucl_emitter_utils.c:401:1 in ucl.h
// ucl_object_emit_fd_funcs at ucl_emitter_utils.c:420:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_parser_free at ucl_util.c:599:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <ucl.h>

#define DUMMY_FILE_PATH "./dummy_file"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen(DUMMY_FILE_PATH, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    struct ucl_parser *parser = ucl_parser_new(0);
    if (!parser) {
        return 0;
    }

    write_dummy_file(Data, Size);

    // Step 1: Call ucl_parser_get_comments
    const ucl_object_t *comments = ucl_parser_get_comments(parser);

    // Step 2: Call ucl_parser_get_object
    ucl_object_t *top_object = ucl_parser_get_object(parser);
    if (!top_object) {
        ucl_parser_free(parser);
        return 0;
    }

    // Step 3: Call ucl_object_emit_file_funcs
    FILE *fp = fopen(DUMMY_FILE_PATH, "wb");
    if (fp) {
        struct ucl_emitter_functions *file_funcs = ucl_object_emit_file_funcs(fp);
        if (file_funcs) {
            file_funcs->ucl_emitter_free_func(file_funcs->ud);
            free(file_funcs);
        }
        fclose(fp);
    }

    // Step 4: Call ucl_object_emit_fd_funcs
    int fd = open(DUMMY_FILE_PATH, O_WRONLY);
    if (fd != -1) {
        struct ucl_emitter_functions *fd_funcs = ucl_object_emit_fd_funcs(fd);
        if (fd_funcs) {
            fd_funcs->ucl_emitter_free_func(fd_funcs->ud);
            free(fd_funcs);
        }
        close(fd);
    }

    // Cleanup
    ucl_object_unref(top_object);
    ucl_parser_free(parser);

    return 0;
}