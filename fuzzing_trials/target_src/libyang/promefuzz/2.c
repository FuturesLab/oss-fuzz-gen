// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// ly_ctx_new at context.c:278:1 in context.h
// lyd_parse_data_fd at tree_data.c:224:1 in parser_data.h
// lyd_dup_siblings_to_ctx at tree_data.c:2547:1 in tree_data.h
// lyd_path at tree_data.c:2974:1 in tree_data.h
// lyd_find_sibling_first at tree_data.c:3182:1 in tree_data.h
// lyd_first_sibling at tree_data_common.c:771:1 in tree_data.h
// lyd_free_tree at tree_data_free.c:265:1 in tree_data.h
// lyd_free_tree at tree_data_free.c:265:1 in tree_data.h
// ly_ctx_destroy at context.c:1503:1 in context.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "parser_data.h"
#include "tree_data.h"
#include "libyang.h" // Include the correct header for context functions

static int write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        return -1;
    }
    size_t written = fwrite(Data, 1, Size, file);
    fclose(file);
    return (written == Size) ? 0 : -1;
}

int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    struct ly_ctx *ctx = NULL;
    struct lyd_node *tree = NULL;
    struct lyd_node *dup = NULL;
    struct lyd_node *match = NULL;
    char *path = NULL;
    int fd = -1;

    // Initialize context
    if (ly_ctx_new(NULL, 0, &ctx) != LY_SUCCESS) {
        goto cleanup;
    }

    // Write data to dummy file
    if (write_dummy_file(Data, Size) != 0) {
        goto cleanup;
    }

    // Open dummy file
    fd = open("./dummy_file", O_RDONLY);
    if (fd == -1) {
        goto cleanup;
    }

    // Fuzzing lyd_parse_data_fd
    lyd_parse_data_fd(ctx, fd, (LYD_FORMAT)(Data[0] % 3), 0, 0, &tree);

    // Fuzzing lyd_dup_siblings_to_ctx
    if (tree) {
        lyd_dup_siblings_to_ctx(tree, ctx, NULL, 0, &dup);
    }

    // Fuzzing lyd_path
    if (tree) {
        path = lyd_path(tree, (LYD_PATH_TYPE)(Data[0] % 2), NULL, 0);
        free(path);
    }

    // Fuzzing lyd_find_sibling_first
    if (tree) {
        lyd_find_sibling_first(tree, tree, &match);
    }

    // Fuzzing lyd_first_sibling
    if (tree) {
        struct lyd_node *first_sibling = lyd_first_sibling(tree);
        (void)first_sibling; // Suppress unused variable warning
    }

cleanup:
    if (fd != -1) {
        close(fd);
    }
    lyd_free_tree(tree);
    lyd_free_tree(dup);
    ly_ctx_destroy(ctx);
    return 0;
}