#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "/src/libyang/src/context.h"
#include "/src/libyang/src/parser_schema.h"
#include "/src/libyang/src/in.h"

static struct ly_ctx *create_context() {
    struct ly_ctx *ctx = NULL;
    if (ly_ctx_new(NULL, 0, &ctx) != LY_SUCCESS) {
        return NULL;
    
    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ly_ctx_new to ly_ctx_set_options
    uint32_t ret_ly_ctx_get_options_fitve = ly_ctx_get_options(ctx);
    if (ret_ly_ctx_get_options_fitve < 0){
    	return 0;
    }

    LY_ERR ret_ly_ctx_set_options_lnqzx = ly_ctx_set_options(ctx, ret_ly_ctx_get_options_fitve);

    // End mutation: Producer.APPEND_MUTATOR

}
    return ctx;
}

static void cleanup_context(struct ly_ctx *ctx) {
    if (ctx) {

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function ly_ctx_destroy with ly_ctx_free_parsed

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function ly_ctx_free_parsed with ly_ctx_destroy
        ly_ctx_destroy(ctx);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        // End mutation: Producer.REPLACE_FUNC_MUTATOR


    }
}

static void fuzz_ly_ctx_get_module_ns(const struct ly_ctx *ctx, const char *ns, const char *revision) {

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function ly_ctx_get_module_ns with ly_ctx_get_module

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function ly_ctx_get_module with ly_ctx_get_module_ns

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function ly_ctx_get_module_ns with ly_ctx_get_module
    struct lys_module *module = ly_ctx_get_module(ctx, ns, revision);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // No specific cleanup required for ly_ctx_get_module_ns result

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ly_ctx_get_module to lyd_validate_module
    struct lyd_node *mxsdesmp;
    memset(&mxsdesmp, 0, sizeof(mxsdesmp));

    LY_ERR ret_lyd_validate_module_pqsak = lyd_validate_module(&mxsdesmp, module, 1, NULL);

    // End mutation: Producer.APPEND_MUTATOR

}

static void fuzz_lys_parse(struct ly_ctx *ctx, const char *data, LYS_INFORMAT format) {
    struct ly_in *in = NULL;
    if (ly_in_new_memory(data, &in) != LY_SUCCESS) {
        return;
    }
    struct lys_module *module = NULL;
    if (lys_parse(ctx, in, format, NULL, &module) != LY_SUCCESS) {
        // Handle error
    }
    ly_in_free(in, 0);
}

static void fuzz_lys_parse_fd(struct ly_ctx *ctx, int fd, LYS_INFORMAT format) {
    struct lys_module *module = NULL;
    if (lys_parse_fd(ctx, fd, format, &module) != LY_SUCCESS) {
        // Handle error
    }
    // No specific cleanup required for lys_parse_fd result
}

static void fuzz_lys_parse_mem(struct ly_ctx *ctx, const char *data, LYS_INFORMAT format) {
    struct lys_module *module = NULL;

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of lys_parse_mem

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of lys_parse_mem

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of lys_parse_mem
    if (lys_parse_mem(ctx, (const char *)data, format, &module) != LY_SUCCESS) {
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR


        // Handle error
    
    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from lys_parse_mem to ly_ctx_get_yanglib_data
    struct lyd_node *rcnhhcbs;
    memset(&rcnhhcbs, 0, sizeof(rcnhhcbs));
    const char mmwxvpac[1024] = "ergqk";


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of ly_ctx_get_yanglib_data

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of ly_ctx_get_yanglib_data

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of ly_ctx_get_yanglib_data
    const char egoekytg[1024] = "oylnu";
    LY_ERR ret_ly_ctx_get_yanglib_data_txktw = ly_ctx_get_yanglib_data(ctx, &rcnhhcbs, egoekytg);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ly_ctx_get_yanglib_data to lyd_eval_xpath
    ly_bool ret_ly_ctx_is_printed_sujfb = ly_ctx_is_printed(NULL);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ly_ctx_is_printed to lyd_eval_xpath2
    const char xuyqvtym[1024] = "wzlqy";


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ly_ctx_is_printed to lyd_eval_xpath


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ly_ctx_is_printed to lyd_eval_xpath2

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function lyd_unlink_tree with lyd_unlink_siblings
    LY_ERR ret_lyd_unlink_tree_nixwp = lyd_unlink_siblings(rcnhhcbs);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    LY_ERR ret_lyd_eval_xpath2_jocgz = lyd_eval_xpath2(rcnhhcbs, (const char *)"w", NULL, &ret_ly_ctx_is_printed_sujfb);

    // End mutation: Producer.APPEND_MUTATOR

    LY_ERR ret_lyd_eval_xpath_sqceh = lyd_eval_xpath(rcnhhcbs, (const char *)data, &ret_ly_ctx_is_printed_sujfb);

    // End mutation: Producer.APPEND_MUTATOR

    LY_ERR ret_lyd_eval_xpath2_xzxvz = lyd_eval_xpath2(rcnhhcbs, xuyqvtym, NULL, &ret_ly_ctx_is_printed_sujfb);

    // End mutation: Producer.APPEND_MUTATOR

    LY_ERR ret_lyd_eval_xpath_xlhwf = lyd_eval_xpath(rcnhhcbs, (const char *)"r", &ret_ly_ctx_is_printed_sujfb);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from lyd_eval_xpath to lyd_diff_apply_module

    LY_ERR ret_lyd_diff_apply_module_epnon = lyd_diff_apply_module(NULL, NULL, module, NULL, (void *)&ret_ly_ctx_is_printed_sujfb);

    // End mutation: Producer.APPEND_MUTATOR

}
    // No specific cleanup required for lys_parse_mem result
}

static void fuzz_lys_parse_path(struct ly_ctx *ctx, const char *path, LYS_INFORMAT format) {
    struct lys_module *module = NULL;

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of lys_parse_path

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of lys_parse_path
    if (lys_parse_path(ctx, NULL, format, &module) != LY_SUCCESS) {
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR


        // Handle error
    }
    // No specific cleanup required for lys_parse_path result
}

static void fuzz_ly_ctx_get_module_latest(const struct ly_ctx *ctx, const char *name) {

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function ly_ctx_get_module_latest with ly_ctx_get_module_latest_ns
    struct lys_module *module = ly_ctx_get_module_latest_ns(ctx, name);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // No specific cleanup required for ly_ctx_get_module_latest result
}

int LLVMFuzzerTestOneInput_415(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    struct ly_ctx *ctx = create_context();
    if (!ctx) {
        return 0;
    }

    char *dummy_data = (char *)malloc(Size + 1);
    if (!dummy_data) {
        cleanup_context(ctx);
        return 0;
    }
    memcpy(dummy_data, Data, Size);
    dummy_data[Size] = '\0';

    char *dummy_ns = "urn:example:namespace";
    char *dummy_revision = "2023-10-10";
    char *dummy_path = "./dummy_file";

    // Fuzz ly_ctx_get_module_ns
    fuzz_ly_ctx_get_module_ns(ctx, dummy_ns, dummy_revision);

    // Fuzz lys_parse
    fuzz_lys_parse(ctx, dummy_data, LYS_IN_YANG);

    // Create a dummy file for lys_parse_fd
    int fd = open(dummy_path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd != -1) {
        write(fd, dummy_data, Size);
        lseek(fd, 0, SEEK_SET);
        fuzz_lys_parse_fd(ctx, fd, LYS_IN_YANG);
        close(fd);
    }

    // Fuzz lys_parse_mem
    fuzz_lys_parse_mem(ctx, dummy_data, LYS_IN_YANG);

    // Fuzz lys_parse_path
    FILE *file = fopen(dummy_path, "w");
    if (file) {
        fwrite(dummy_data, 1, Size, file);
        fclose(file);
        fuzz_lys_parse_path(ctx, dummy_path, LYS_IN_YANG);
    }

    // Fuzz ly_ctx_get_module_latest
    fuzz_ly_ctx_get_module_latest(ctx, "example-module");

    free(dummy_data);
    cleanup_context(ctx);
    return 0;
}