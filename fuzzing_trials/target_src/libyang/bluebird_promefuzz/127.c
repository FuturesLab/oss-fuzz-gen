#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "/src/libyang/src/parser_data.h"
#include "/src/libyang/src/tree_data.h"
#include "/src/libyang/src/tree_schema.h"
#include "/src/libyang/src/in.h"

static void fuzz_lyd_parse_data_fd(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *tree = NULL;
    int fd;
    char *filename = "./dummy_file";

    // Create a dummy file with fuzz data
    fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        return;
    }
    if (write(fd, Data, Size) != Size) {
        close(fd);
        return;
    }
    lseek(fd, 0, SEEK_SET);

    // Fuzzing the function
    lyd_parse_data_fd(ctx, fd, LYD_XML, 0, 0, &tree);

    // Cleanup
    lyd_free_all(tree);
    close(fd);
    unlink(filename);
}

static void fuzz_lyd_parse_data(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *tree = NULL;
    struct ly_in *input = NULL;

    // Create input handler
    ly_in_new_memory((const char *)Data, &input);

    // Fuzzing the function
    lyd_parse_data(ctx, NULL, input, LYD_XML, 0, 0, &tree);

    // Cleanup
    lyd_free_all(tree);
    ly_in_free(input, 0);
}

static void fuzz_lyd_parse_op(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *tree = NULL, *op = NULL;
    struct ly_in *input = NULL;

    // Create input handler
    ly_in_new_memory((const char *)Data, &input);

    // Fuzzing the function
    lyd_parse_op(ctx, NULL, input, LYD_XML, LYD_TYPE_RPC_NETCONF, 0, &tree, &op);

    // Cleanup
    lyd_free_all(tree);
    ly_in_free(input, 0);
}

static void fuzz_lyd_validate_ext(const uint8_t *Data, size_t Size) {
    struct lyd_node *ext_tree = NULL;
    const struct lysc_ext_instance *ext = NULL; // Updated to use a pointer
    struct lyd_node *diff = NULL;

    // Fuzzing the function
    lyd_validate_ext(&ext_tree, ext, 0, &diff);

    // Cleanup
    lyd_free_all(ext_tree);
    lyd_free_all(diff);
}

static void fuzz_lyd_parse_data_mem(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *tree = NULL;

    // Ensure null-terminated input
    char *data = (char *)malloc(Size + 1);
    if (!data) {
        return;
    }
    memcpy(data, Data, Size);
    data[Size] = '\0';

    // Fuzzing the function
    lyd_parse_data_mem(ctx, data, LYD_XML, 0, 0, &tree);

    // Cleanup
    lyd_free_all(tree);
    free(data);
}

static void fuzz_lyd_new_implicit_all(const uint8_t *Data, size_t Size) {
    struct lyd_node *tree = NULL;
    struct ly_ctx *ctx = NULL;
    struct lyd_node *diff = NULL;

    // Fuzzing the function
    lyd_new_implicit_all(&tree, ctx, 0, &diff);

    // Cleanup
    lyd_free_all(tree);
    lyd_free_all(diff);
}

int LLVMFuzzerTestOneInput_127(const uint8_t *Data, size_t Size) {
    fuzz_lyd_parse_data_fd(Data, Size);
    fuzz_lyd_parse_data(Data, Size);
    fuzz_lyd_parse_op(Data, Size);
    fuzz_lyd_validate_ext(Data, Size);
    fuzz_lyd_parse_data_mem(Data, Size);
    fuzz_lyd_new_implicit_all(Data, Size);

    return 0;
}