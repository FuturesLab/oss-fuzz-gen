#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_130(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lys_module *module = NULL;
    LY_ERR err;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd;
    FILE *file;

    // Initialize the context

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of ly_ctx_new
    err = ly_ctx_new(NULL, 1, &ctx);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Create a temporary file to write the fuzz data
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from lys_parse_path to ly_ctx_get_submodule2_latest

    const struct lysp_submodule* ret_ly_ctx_get_submodule2_latest_smmkj = ly_ctx_get_submodule2_latest(module, (const char *)data);
    if (ret_ly_ctx_get_submodule2_latest_smmkj == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function ly_ctx_destroy with ly_ctx_free_parsed
    ly_ctx_free_parsed(ctx);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    unlink(tmpl);

    return 0;
}