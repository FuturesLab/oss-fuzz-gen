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

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of ly_ctx_new
    if (ly_ctx_new(NULL, 0, &ctx) != LY_SUCCESS) {
    // End mutation: Producer.REPLACE_ARG_MUTATOR


        return NULL;
    
    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ly_ctx_new to ly_ctx_get_module_iter
    uint32_t ret_ly_ctx_get_modules_hash_gcqpk = ly_ctx_get_modules_hash(ctx);
    if (ret_ly_ctx_get_modules_hash_gcqpk < 0){
    	return 0;
    }

    struct lys_module* ret_ly_ctx_get_module_iter_auinm = ly_ctx_get_module_iter(ctx, &ret_ly_ctx_get_modules_hash_gcqpk);
    if (ret_ly_ctx_get_module_iter_auinm == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

}
    return ctx;
}

static void cleanup_context(struct ly_ctx *ctx) {
    if (ctx) {
        ly_ctx_destroy(ctx);
    }
}

static void fuzz_ly_ctx_get_module_ns(const struct ly_ctx *ctx, const char *ns, const char *revision) {

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function ly_ctx_get_module_ns with ly_ctx_get_module

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of ly_ctx_get_module

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function ly_ctx_get_module with ly_ctx_get_module_ns
    struct lys_module *module = ly_ctx_get_module_ns(ctx, ns, (const char *)"w");
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // No specific cleanup required for ly_ctx_get_module_ns result
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

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of lys_parse_fd
    if (lys_parse_fd(ctx, -1, format, &module) != LY_SUCCESS) {
    // End mutation: Producer.REPLACE_ARG_MUTATOR


        // Handle error
    
    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from lys_parse_fd to ly_ctx_new_ylpath
    ly_pattern_free((void *)module);

    LY_ERR ret_ly_ctx_new_ylpath_ufnia = ly_ctx_new_ylpath(module, (const char *)"w", 0, 1, &ctx);

    // End mutation: Producer.APPEND_MUTATOR

}
    // No specific cleanup required for lys_parse_fd result
}

static void fuzz_lys_parse_mem(struct ly_ctx *ctx, const char *data, LYS_INFORMAT format) {
    struct lys_module *module = NULL;
    if (lys_parse_mem(ctx, data, format, &module) != LY_SUCCESS) {
        // Handle error
    
    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from lys_parse_mem to ly_ctx_get_yanglib_data
    struct lyd_node *rcnhhcbs;
    memset(&rcnhhcbs, 0, sizeof(rcnhhcbs));
    const char mmwxvpac[1024] = "ergqk";

    LY_ERR ret_ly_ctx_get_yanglib_data_txktw = ly_ctx_get_yanglib_data(ctx, &rcnhhcbs, mmwxvpac);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ly_ctx_get_yanglib_data to lyd_eval_xpath
    ly_pattern_free((void *)module);
    ly_bool ret_lyd_is_default_khscu = lyd_is_default(rcnhhcbs);


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of lyd_eval_xpath

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from lyd_is_default to lyd_eval_xpath

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function lyd_unlink_siblings with lyd_unlink_tree
    LY_ERR ret_lyd_unlink_siblings_adlvq = lyd_unlink_tree(rcnhhcbs);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    const char qmlllofc[1024] = "pvsme";

    LY_ERR ret_lyd_eval_xpath_rzcon = lyd_eval_xpath(rcnhhcbs, qmlllofc, &ret_lyd_is_default_khscu);

    // End mutation: Producer.APPEND_MUTATOR

    LY_ERR ret_lyd_eval_xpath_ioxuz = lyd_eval_xpath(rcnhhcbs, (const char *)data, &ret_lyd_is_default_khscu);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // End mutation: Producer.APPEND_MUTATOR

}
    // No specific cleanup required for lys_parse_mem result
}

static void fuzz_lys_parse_path(struct ly_ctx *ctx, const char *path, LYS_INFORMAT format) {
    struct lys_module *module = NULL;
    if (lys_parse_path(ctx, path, format, &module) != LY_SUCCESS) {
        // Handle error
    
    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from lys_parse_path to lyd_validate_module
    struct lyd_node *wizpysus;
    memset(&wizpysus, 0, sizeof(wizpysus));

    LY_ERR ret_lyd_validate_module_wcujm = lyd_validate_module(&wizpysus, module, 1, NULL);

    // End mutation: Producer.APPEND_MUTATOR

}
    // No specific cleanup required for lys_parse_path result
}

static void fuzz_ly_ctx_get_module_latest(const struct ly_ctx *ctx, const char *name) {
    struct lys_module *module = ly_ctx_get_module_latest(ctx, name);
    // No specific cleanup required for ly_ctx_get_module_latest result
}

int LLVMFuzzerTestOneInput_206(const uint8_t *Data, size_t Size) {
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