#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "/src/libyang/src/context.h"

static struct ly_ctx* create_context() {
    struct ly_ctx *ctx = NULL;
    ly_ctx_new(NULL, 0, &ctx);
    return ctx;
}

static void destroy_context(struct ly_ctx *ctx) {
    ly_ctx_destroy(ctx);
}

static char* copy_input_to_string(const uint8_t *Data, size_t Size) {
    char *str = (char *)malloc(Size + 1);
    if (str) {
        memcpy(str, Data, Size);
        str[Size] = '\0';
    }
    return str;
}

int LLVMFuzzerTestOneInput_126(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    struct ly_ctx *ctx = create_context();
    if (!ctx) {
        return 0;
    }

    char *input_str = copy_input_to_string(Data, Size);
    if (!input_str) {
        destroy_context(ctx);
        return 0;
    }

    // Fuzz ly_ctx_get_module_latest_ns
    struct lys_module *module = ly_ctx_get_module_latest_ns(ctx, input_str);
    if (module) {
        // Use module if needed
    }

    // Fuzz ly_ctx_get_submodule
    const struct lysp_submodule *submodule = ly_ctx_get_submodule(ctx, input_str, NULL);
    if (submodule) {
        // Use submodule if needed
    }

    // Fuzz ly_ctx_get_submodule2
    const struct lysp_submodule *submodule2 = ly_ctx_get_submodule2(module, input_str, NULL);
    if (submodule2) {
        // Use submodule2 if needed
    }

    // Fuzz ly_ctx_get_submodule2_latest
    const struct lysp_submodule *submodule2_latest = ly_ctx_get_submodule2_latest(module, input_str);
    if (submodule2_latest) {
        // Use submodule2_latest if needed
    }

    // Fuzz ly_ctx_get_submodule_latest
    const struct lysp_submodule *submodule_latest = ly_ctx_get_submodule_latest(ctx, input_str);
    if (submodule_latest) {
        // Use submodule_latest if needed
    }

    // Fuzz ly_ctx_get_module_latest
    struct lys_module *module_latest = ly_ctx_get_module_latest(ctx, input_str);
    if (module_latest) {
        // Use module_latest if needed
    }

    free(input_str);
    destroy_context(ctx);
    return 0;
}