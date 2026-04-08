#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_114(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lys_module *module = NULL;
    LY_ERR err;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd;
    FILE *file;

    // Initialize the context

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of ly_ctx_new

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of ly_ctx_new
    err = ly_ctx_new(NULL, 0, &ctx);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Create a temporary file to write the fuzz data

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ly_ctx_new to ly_ctx_unset_options
    int ret_ly_ctx_compiled_size_zngie = ly_ctx_compiled_size(ctx);
    if (ret_ly_ctx_compiled_size_zngie < 0){
    	return 0;
    }


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function ly_ctx_unset_options with ly_ctx_set_options
    LY_ERR ret_ly_ctx_unset_options_yzhey = ly_ctx_set_options(ctx, (uint32_t)ret_ly_ctx_compiled_size_zngie);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // End mutation: Producer.APPEND_MUTATOR

    fd = mkstemp(tmpl);
    if (fd == -1) {
        fprintf(stderr, "Failed to create temporary file\n");
        ly_ctx_destroy(ctx);
        
        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ly_ctx_destroy to lys_parse_fd
        uint32_t ret_ly_ctx_internal_modules_count_uzwfe = ly_ctx_internal_modules_count(ctx);
        if (ret_ly_ctx_internal_modules_count_uzwfe < 0){
        	return 0;
        }

        LY_ERR ret_lys_parse_fd_dafzg = lys_parse_fd(ctx, (int )ret_ly_ctx_internal_modules_count_uzwfe, 0, NULL);

        // End mutation: Producer.APPEND_MUTATOR

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