// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// lyd_new_term at tree_data_new.c:742:1 in tree_data.h
// lyd_new_opaq at tree_data_new.c:878:1 in tree_data.h
// lyd_new_list at tree_data_new.c:528:1 in tree_data.h
// lyd_new_any at tree_data_new.c:749:1 in tree_data.h
// lyd_new_inner at tree_data_new.c:446:1 in tree_data.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "tree_data.h"

static char *create_null_terminated_string(const uint8_t *Data, size_t Size) {
    char *str = (char *)malloc(Size + 1);
    if (!str) {
        return NULL;
    }
    memcpy(str, Data, Size);
    str[Size] = '\0';
    return str;
}

int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    struct lyd_node *parent = NULL;
    struct lys_module *module = NULL;
    struct lyd_node *node = NULL;
    const char *name = "test-name";

    char *value = create_null_terminated_string(Data, Size);
    if (!value) {
        return 0;
    }

    // Test lyd_new_term
    lyd_new_term(parent, module, name, value, 0, &node);

    // Test lyd_new_opaq
    lyd_new_opaq(parent, NULL, name, value, NULL, "test-module", &node);

    // Test lyd_new_list
    lyd_new_list(parent, module, name, 0, &node);

    // Test lyd_new_any
    lyd_new_any(parent, module, name, NULL, value, 0, 0, &node);

    // Test lyd_new_inner
    lyd_new_inner(parent, module, name, 0, &node);

    // Cleanup
    free(value);

    return 0;
}