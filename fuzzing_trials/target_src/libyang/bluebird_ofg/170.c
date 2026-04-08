#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_170(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from lyd_free_all to lyd_new_any
    LY_ERR ret_lyd_unlink_tree_qxvcm = lyd_unlink_tree(tree);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from lyd_unlink_tree to lyd_dup_single
    struct lyd_node* ret_lyd_first_sibling_mvvil = lyd_first_sibling(tree);
    if (ret_lyd_first_sibling_mvvil == NULL){
    	return 0;
    }
    uint32_t ret_ly_ctx_internal_modules_count_sfxqd = ly_ctx_internal_modules_count(ctx);
    if (ret_ly_ctx_internal_modules_count_sfxqd < 0){
    	return 0;
    }
    lyd_free_siblings(tree);

    LY_ERR ret_lyd_dup_single_uyrri = lyd_dup_single(tree, ret_lyd_first_sibling_mvvil, ret_ly_ctx_internal_modules_count_sfxqd, &tree);

    // End mutation: Producer.APPEND_MUTATOR

    LY_ERR ret_lyd_unlink_tree_iejhw = lyd_unlink_tree(tree);
    uint32_t ret_ly_ctx_get_options_xcpmg = ly_ctx_get_options(NULL);
    if (ret_ly_ctx_get_options_xcpmg < 0){
    	return 0;
    }
    const char gwvoogdo[1024] = "dlzcw";
    const char hzdypxsj[1024] = "nlunj";

    LY_ERR ret_lyd_new_any_yuvaw = lyd_new_any(tree, NULL, gwvoogdo, tree, hzdypxsj, ret_ly_ctx_get_options_xcpmg, 0, &tree);

    // End mutation: Producer.APPEND_MUTATOR

    ly_ctx_destroy(ctx);
    close(fd);
    unlink(tmpl);

    return 0;
}