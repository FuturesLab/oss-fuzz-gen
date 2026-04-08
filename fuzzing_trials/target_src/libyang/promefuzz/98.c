// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// lyd_new_term at tree_data_new.c:742:1 in tree_data.h
// lyd_parse_value_fragment at tree_data.c:252:1 in parser_data.h
// lyd_new_path2 at tree_data_new.c:1787:1 in tree_data.h
// lyd_new_attr2 at tree_data_new.c:987:1 in tree_data.h
// lyd_new_list2 at tree_data_new.c:581:1 in tree_data.h
// lyd_new_attr at tree_data_new.c:937:1 in tree_data.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "parser_data.h"
#include "tree_data.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_98(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare inputs for lyd_new_term
    struct lyd_node *parent = NULL;
    const struct lys_module *module = NULL;
    char *name = strndup((const char *)Data, Size);
    char *value = strndup((const char *)Data, Size);
    uint32_t options = 0;
    struct lyd_node *node = NULL;

    // Fuzz lyd_new_term
    lyd_new_term(parent, module, name, value, options, &node);

    // Prepare inputs for lyd_parse_value_fragment
    struct ly_ctx *ctx = NULL;
    char *path = strndup((const char *)Data, Size);
    struct ly_in *in = NULL;
    LYD_FORMAT format = LYD_JSON;
    uint32_t new_val_options = 0;
    uint32_t parse_options = 0;
    uint32_t validate_options = 0;
    struct lyd_node *tree = NULL;

    // Write to dummy file
    write_dummy_file(Data, Size);

    // Fuzz lyd_parse_value_fragment
    lyd_parse_value_fragment(ctx, path, in, format, new_val_options, parse_options, validate_options, &tree);

    // Prepare inputs for lyd_new_path2
    void *value_path = NULL;
    uint64_t value_size_bits = 0;
    uint32_t any_hints = 0;
    struct lyd_node *new_parent = NULL;
    struct lyd_node *new_node = NULL;

    // Fuzz lyd_new_path2
    lyd_new_path2(parent, ctx, path, value_path, value_size_bits, any_hints, options, &new_parent, &new_node);

    // Prepare inputs for lyd_new_attr2
    const char *module_ns = NULL;
    char *attr_name = strndup((const char *)Data, Size);
    char *attr_value = strndup((const char *)Data, Size);
    struct lyd_attr *attr = NULL;

    // Fuzz lyd_new_attr2
    lyd_new_attr2(parent, module_ns, attr_name, attr_value, &attr);

    // Prepare inputs for lyd_new_list2
    const char *keys = NULL;

    // Fuzz lyd_new_list2
    lyd_new_list2(parent, module, name, keys, options, &node);

    // Prepare inputs for lyd_new_attr
    const char *module_name = NULL;

    // Fuzz lyd_new_attr
    lyd_new_attr(parent, module_name, attr_name, attr_value, &attr);

    // Cleanup
    free(name);
    free(value);
    free(path);
    free(attr_name);
    free(attr_value);

    return 0;
}