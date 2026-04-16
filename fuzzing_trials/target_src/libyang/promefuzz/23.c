// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// ly_ctx_new at context.c:278:1 in context.h
// ly_ctx_destroy at context.c:1503:1 in context.h
// lyd_first_sibling at tree_data_common.c:771:1 in tree_data.h
// lyd_path at tree_data.c:2974:1 in tree_data.h
// lyd_free_tree at tree_data_free.c:265:1 in tree_data.h
// ly_ctx_destroy at context.c:1503:1 in context.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "libyang.h"
#include "parser_data.h"
#include "tree_data.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(LYD_FORMAT) + 2 * sizeof(uint32_t)) {
        return 0;
    }

    struct ly_ctx *ctx = NULL;
    if (ly_ctx_new(NULL, 0, &ctx) != LY_SUCCESS) {
        return 0;
    }

    write_dummy_file(Data, Size);

    int fd = open("./dummy_file", O_RDONLY);
    if (fd == -1) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    LYD_FORMAT format = *(LYD_FORMAT *)Data;
    uint32_t parse_options = *(uint32_t *)(Data + sizeof(LYD_FORMAT));
    uint32_t validate_options = *(uint32_t *)(Data + sizeof(LYD_FORMAT) + sizeof(uint32_t));

    struct lyd_node *tree = NULL;
    LY_ERR err = lyd_parse_data_fd(ctx, fd, format, parse_options, validate_options, &tree);
    if (err == LY_SUCCESS && tree) {
        struct lyd_node *sibling = lyd_first_sibling(tree);
        if (sibling) {
            char *path = lyd_path(sibling, 0, NULL, 0);
            if (path) {
                free(path);
            }
            lyd_free_tree(sibling);
        }
    }

    close(fd);
    ly_ctx_destroy(ctx);
    return 0;
}