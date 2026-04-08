#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *tree = NULL;
    LY_ERR err;
    int fd;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";

    // Create a temporary file
    fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Reset the file offset to the beginning
    lseek(fd, 0, SEEK_SET);

    // Initialize the context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    lyd_parse_data_fd(ctx, fd, LYD_JSON, 0, LYD_VALIDATE_PRESENT, &tree);

    // Cleanup

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function lyd_free_all with lyd_free_tree

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from lyd_parse_data_fd to lyd_eval_xpath2

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from lyd_parse_data_fd to lyd_validate_op
    LY_ERR ret_lyd_unlink_tree_ebkav = lyd_unlink_tree(tree);
    lyd_free_all(tree);

    LY_ERR ret_lyd_validate_op_xviva = lyd_validate_op(tree, tree, 0, &tree);

    // End mutation: Producer.APPEND_MUTATOR

    ly_bool ret_ly_ctx_is_printed_qyqig = ly_ctx_is_printed(NULL);

    LY_ERR ret_lyd_eval_xpath2_xcyfe = lyd_eval_xpath2(tree, (const char *)"w", NULL, &ret_ly_ctx_is_printed_qyqig);

    // End mutation: Producer.APPEND_MUTATOR

    lyd_free_tree(tree);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    ly_ctx_destroy(ctx);
    close(fd);
    unlink(tmpl);

    return 0;
}