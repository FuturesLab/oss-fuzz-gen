#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_112(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lys_module *module = NULL;
    LY_ERR err;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd;
    FILE *file;

    // Create a new context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Create a temporary file
    fd = mkstemp(tmpl);
    if (fd == -1) {
        fprintf(stderr, "Failed to create temporary file\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Write fuzz data to the temporary file
    file = fdopen(fd, "wb");
    if (file == NULL) {
        fprintf(stderr, "Failed to open temporary file\n");
        close(fd);
        ly_ctx_destroy(ctx);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Call the function-under-test
    lys_parse_path(ctx, tmpl, LYS_IN_YANG, &module);

    // Clean up
    ly_ctx_destroy(ctx);
    unlink(tmpl);

    return 0;
}