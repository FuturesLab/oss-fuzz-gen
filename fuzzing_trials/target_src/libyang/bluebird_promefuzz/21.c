#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libyang/src/tree_data.h"

static char *create_null_terminated_string(const uint8_t *Data, size_t Size) {
    char *str = (char *)malloc(Size + 1);
    if (!str) {
        return NULL;
    }
    memcpy(str, Data, Size);
    str[Size] = '\0';
    return str;
}

int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
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