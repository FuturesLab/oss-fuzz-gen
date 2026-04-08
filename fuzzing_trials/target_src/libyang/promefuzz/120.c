// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// ly_ctx_new_ylpath at context.c:449:1 in context.h
// lyd_diff_siblings at diff.c:1435:1 in tree_data.h
// lyd_new_list2 at tree_data_new.c:581:1 in tree_data.h
// ly_ctx_set_ext_data_clb at context.c:837:1 in context.h
// lyd_free_attr_siblings at tree_data_free.c:139:1 in tree_data.h
// ly_ctx_get_change_count at context.c:755:1 in context.h
// lyd_free_tree at tree_data_free.c:265:1 in tree_data.h
// ly_ctx_destroy at context.c:1503:1 in context.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "context.h"
#include "tree_data.h"

static LY_ERR dummy_ext_data_clb(const struct lysc_ext_instance *ext, const struct lyd_node *parent, void *user_data, void **tree, unsigned char *ext_data) {
    (void)ext;
    (void)parent;
    (void)user_data;
    (void)tree;
    (void)ext_data;
    return LY_SUCCESS;
}

int LLVMFuzzerTestOneInput_120(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    struct ly_ctx *ctx = NULL;
    struct lyd_node *first = NULL, *second = NULL, *diff = NULL;
    struct lys_module *module = NULL;
    LY_ERR err;
    uint16_t options = 0;
    uint32_t new_list_options = 0;
    struct lyd_node *new_list_node = NULL;
    const char *dummy_search_dir = NULL;
    const char *dummy_file_path = "./dummy_file";
    LYD_FORMAT dummy_format = 0;
    FILE *file = fopen(dummy_file_path, "wb");
    if (!file) {
        return 0;
    }
    fwrite(Data, Size, 1, file);
    fclose(file);

    // ly_ctx_new_ylpath
    err = ly_ctx_new_ylpath(dummy_search_dir, dummy_file_path, dummy_format, 0, &ctx);
    if (err != LY_SUCCESS) {
        goto cleanup;
    }

    // lyd_diff_siblings
    err = lyd_diff_siblings(first, second, options, &diff);
    if (err != LY_SUCCESS) {
        goto cleanup;
    }

    // lyd_new_list2
    err = lyd_new_list2(first, module, "list-name", "[key='value']", new_list_options, &new_list_node);
    if (err != LY_SUCCESS) {
        goto cleanup;
    }

    // ly_ctx_set_ext_data_clb
    ly_ctx_set_ext_data_clb(ctx, dummy_ext_data_clb, NULL);

    // lyd_free_attr_siblings
    struct lyd_attr *attr = NULL;
    lyd_free_attr_siblings(ctx, attr);

    // ly_ctx_get_change_count
    uint16_t change_count = ly_ctx_get_change_count(ctx);

cleanup:
    if (diff) {
        lyd_free_tree(diff);
    }
    if (ctx) {
        ly_ctx_destroy(ctx);
    }
    remove(dummy_file_path);
    return 0;
}