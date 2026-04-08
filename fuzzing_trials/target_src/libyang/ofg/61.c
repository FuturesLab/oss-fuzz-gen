#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
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
    lyd_free_all(tree);
    ly_ctx_destroy(ctx);
    close(fd);
    unlink(tmpl);

    return 0;
}