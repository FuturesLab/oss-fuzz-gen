#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lys_module *module = NULL;
    LY_ERR err;
    int fd;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";

    // Create a temporary file and write the fuzz data to it
    fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Reset file offset to the beginning
    lseek(fd, 0, SEEK_SET);

    // Initialize the context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    lys_parse_fd(ctx, fd, LYS_IN_YANG, &module);

    // Cleanup
    ly_ctx_destroy(ctx);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ly_ctx_destroy to ly_ctx_new
    uint32_t ret_lyd_list_pos_dznye = lyd_list_pos(NULL);
    if (ret_lyd_list_pos_dznye < 0){
    	return 0;
    }

    LY_ERR ret_ly_ctx_new_tchcc = ly_ctx_new((const char *)"r", ret_lyd_list_pos_dznye, &ctx);

    // End mutation: Producer.APPEND_MUTATOR

    close(fd);
    unlink(tmpl);

    return 0;
}