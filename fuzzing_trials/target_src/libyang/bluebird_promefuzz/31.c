#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libyang/src/context.h"

static struct ly_ctx *initialize_context() {
    struct ly_ctx *ctx = NULL;
    if (ly_ctx_new(NULL, 0, &ctx) != LY_SUCCESS) {
        return NULL;
    }
    return ctx;
}

static void cleanup_context(struct ly_ctx *ctx) {
    if (ctx) {
        ly_ctx_destroy(ctx);
    }
}

int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    struct ly_ctx *ctx = initialize_context();
    if (!ctx) {
        return 0;
    }

    char *input_str = (char *)malloc(Size + 1);
    if (!input_str) {
        cleanup_context(ctx);
        return 0;
    }
    memcpy(input_str, Data, Size);
    input_str[Size] = '\0';

    // Fuzz ly_ctx_get_module_latest_ns
    struct lys_module *module_latest_ns = ly_ctx_get_module_latest_ns(ctx, input_str);
    if (module_latest_ns) {
        // Do something with module_latest_ns if needed
    }

    // Fuzz ly_ctx_get_submodule_latest
    const struct lysp_submodule *submodule_latest = ly_ctx_get_submodule_latest(ctx, input_str);
    if (submodule_latest) {
        // Do something with submodule_latest if needed
    }

    // Fuzz ly_ctx_get_submodule2_latest
    if (module_latest_ns) {
        const struct lysp_submodule *submodule2_latest = ly_ctx_get_submodule2_latest(module_latest_ns, input_str);
        if (submodule2_latest) {
            // Do something with submodule2_latest if needed
        }
    }

    // Fuzz ly_ctx_get_submodule
    const struct lysp_submodule *submodule = ly_ctx_get_submodule(ctx, input_str, NULL);
    if (submodule) {
        // Do something with submodule if needed
    }

    // Fuzz ly_ctx_get_module_latest
    struct lys_module *module_latest = ly_ctx_get_module_latest(ctx, input_str);
    if (module_latest) {
        // Do something with module_latest if needed
    }

    // Fuzz ly_ctx_get_submodule2
    if (module_latest) {
        const struct lysp_submodule *submodule2 = ly_ctx_get_submodule2(module_latest, input_str, NULL);
        if (submodule2) {
            // Do something with submodule2 if needed
        }
    }

    free(input_str);
    cleanup_context(ctx);
    return 0;
}