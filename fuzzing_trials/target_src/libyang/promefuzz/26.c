// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// ly_ctx_new at context.c:278:1 in context.h
// ly_ctx_destroy at context.c:1503:1 in context.h
// lys_parse_mem at tree_schema.c:2872:1 in parser_schema.h
// lys_parse at tree_schema.c:2823:1 in parser_schema.h
// ly_ctx_is_printed at context.c:1493:1 in context.h
// lys_parse_fd at tree_schema.c:2888:1 in parser_schema.h
// ly_ctx_get_module_latest at context.c:972:1 in context.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "context.h"
#include "parser_schema.h"
#include "in.h" // Include the header for ly_in functions

static struct ly_ctx *initialize_context() {
    struct ly_ctx *ctx = NULL;
    if (ly_ctx_new(NULL, 0, &ctx) != LY_SUCCESS) {
        return NULL;
    }
    return ctx;
}

static void cleanup_context(struct ly_ctx *ctx) {
    if (ctx) {
        ly_ctx_destroy(ctx);
    }
}

int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    struct ly_ctx *ctx = initialize_context();
    if (!ctx) {
        return 0;
    }

    // Ensure the data is null-terminated for string operations
    char *schema_data = (char *)malloc(Size + 1);
    if (!schema_data) {
        cleanup_context(ctx);
        return 0;
    }
    memcpy(schema_data, Data, Size);
    schema_data[Size] = '\0';

    // Fuzz lys_parse_mem
    LYS_INFORMAT format = LYS_IN_YANG; // Assuming YANG format for fuzzing
    struct lys_module *module = NULL;
    lys_parse_mem(ctx, schema_data, format, &module);

    // Fuzz lys_parse
    struct ly_in *input = NULL;
    ly_in_new_memory(schema_data, &input);
    lys_parse(ctx, input, format, NULL, &module);
    ly_in_free(input, 0);

    // Fuzz ly_ctx_is_printed
    ly_ctx_is_printed(ctx);

    // Fuzz lys_parse_fd
    int fd = open("./dummy_file", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd != -1) {
        write(fd, Data, Size);
        lseek(fd, 0, SEEK_SET);
        lys_parse_fd(ctx, fd, format, &module);
        close(fd);
    }

    // Fuzz ly_ctx_get_module_latest
    const char *module_name = "test_module"; // Example module name
    ly_ctx_get_module_latest(ctx, module_name);

    free(schema_data);
    cleanup_context(ctx);
    return 0;
}