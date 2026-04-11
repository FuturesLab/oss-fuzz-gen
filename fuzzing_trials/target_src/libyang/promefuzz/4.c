// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// lyd_find_xpath3 at tree_data.c:3440:1 in tree_data.h
// lyd_trim_xpath at tree_data.c:3581:1 in tree_data.h
// lyd_find_xpath at tree_data.c:3424:1 in tree_data.h
// lyd_eval_xpath2 at tree_data.c:3457:1 in tree_data.h
// lyd_find_xpath2 at tree_data.c:3432:1 in tree_data.h
// lyd_eval_xpath4 at tree_data.c:3470:1 in tree_data.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <tree_data.h>
#include <set.h> // Include the header for ly_set_free

static void fuzz_lyd_trim_xpath(const uint8_t *Data, size_t Size) {
    struct lyd_node *tree = NULL;
    char *xpath = strndup((const char *)Data, Size);
    if (!xpath) {
        return;
    }
    struct lyxp_var *vars = NULL;

    lyd_trim_xpath(&tree, xpath, vars);

    free(xpath);
}

static void fuzz_lyd_find_xpath(const uint8_t *Data, size_t Size) {
    struct lyd_node *ctx_node = NULL;
    char *xpath = strndup((const char *)Data, Size);
    if (!xpath) {
        return;
    }
    struct ly_set *set = NULL;

    lyd_find_xpath(ctx_node, xpath, &set);

    if (set) {
        ly_set_free(set, NULL);
    }
    free(xpath);
}

static void fuzz_lyd_eval_xpath2(const uint8_t *Data, size_t Size) {
    struct lyd_node *ctx_node = NULL;
    char *xpath = strndup((const char *)Data, Size);
    if (!xpath) {
        return;
    }
    struct lyxp_var *vars = NULL;
    ly_bool result;

    lyd_eval_xpath2(ctx_node, xpath, vars, &result);

    free(xpath);
}

static void fuzz_lyd_find_xpath2(const uint8_t *Data, size_t Size) {
    struct lyd_node *ctx_node = NULL;
    char *xpath = strndup((const char *)Data, Size);
    if (!xpath) {
        return;
    }
    struct lyxp_var *vars = NULL;
    struct ly_set *set = NULL;

    lyd_find_xpath2(ctx_node, xpath, vars, &set);

    if (set) {
        ly_set_free(set, NULL);
    }
    free(xpath);
}

static void fuzz_lyd_eval_xpath4(const uint8_t *Data, size_t Size) {
    struct lyd_node *ctx_node = NULL;
    struct lyd_node *tree = NULL;
    struct lys_module *cur_mod = NULL;
    char *xpath = strndup((const char *)Data, Size);
    if (!xpath) {
        return;
    }
    LY_VALUE_FORMAT format = 0;
    void *prefix_data = NULL;
    struct lyxp_var *vars = NULL;
    LY_XPATH_TYPE ret_type;
    struct ly_set *node_set = NULL;
    char *string = NULL;
    long double number;
    ly_bool boolean;

    lyd_eval_xpath4(ctx_node, tree, cur_mod, xpath, format, prefix_data, vars, &ret_type, &node_set, &string, &number, &boolean);

    if (node_set) {
        ly_set_free(node_set, NULL);
    }
    free(string);
    free(xpath);
}

static void fuzz_lyd_find_xpath3(const uint8_t *Data, size_t Size) {
    struct lyd_node *ctx_node = NULL;
    struct lyd_node *tree = NULL;
    char *xpath = strndup((const char *)Data, Size);
    if (!xpath) {
        return;
    }
    LY_VALUE_FORMAT format = 0;
    void *prefix_data = NULL;
    struct lyxp_var *vars = NULL;
    struct ly_set *set = NULL;

    lyd_find_xpath3(ctx_node, tree, xpath, format, prefix_data, vars, &set);

    if (set) {
        ly_set_free(set, NULL);
    }
    free(xpath);
}

int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    fuzz_lyd_trim_xpath(Data, Size);
    fuzz_lyd_find_xpath(Data, Size);
    fuzz_lyd_eval_xpath2(Data, Size);
    fuzz_lyd_find_xpath2(Data, Size);
    fuzz_lyd_eval_xpath4(Data, Size);
    fuzz_lyd_find_xpath3(Data, Size);
    return 0;
}