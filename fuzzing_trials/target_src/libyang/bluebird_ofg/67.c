#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_67(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from lyd_parse_data_fd to ly_ctx_new_printed
    struct ly_ctx *dovqqdmz;
    memset(&dovqqdmz, 0, sizeof(dovqqdmz));

    LY_ERR ret_ly_ctx_new_printed_daluf = ly_ctx_new_printed((const void *)tree, &dovqqdmz);

    // End mutation: Producer.APPEND_MUTATOR

    lyd_free_all(tree);

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function ly_ctx_destroy with ly_ctx_free_parsed

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from lyd_free_all to lyd_new_attr2
    const char ehorvglk[1024] = "jvqpa";

    LY_ERR ret_lyd_new_attr2_pexee = lyd_new_attr2(tree, ehorvglk, (const char *)data, (const char *)"r", NULL);

    // End mutation: Producer.APPEND_MUTATOR

    ly_ctx_free_parsed(ctx);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    close(fd);
    unlink(tmpl);

    return 0;
}