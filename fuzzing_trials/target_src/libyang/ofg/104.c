#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_104(const uint8_t *data, size_t size) {
    struct lyxp_var *vars = NULL;
    char *name = NULL;
    char *value = NULL;
    LY_ERR err;

    // Ensure that size is large enough to split into two strings
    if (size < 2) {
        return 0;
    }

    // Allocate memory for name and value, splitting the input data
    size_t name_len = size / 2;
    size_t value_len = size - name_len;

    name = (char *)malloc(name_len + 1);
    value = (char *)malloc(value_len + 1);

    if (!name || !value) {
        free(name);
        free(value);
        return 0;
    }

    // Copy data into name and value, ensuring null-termination
    memcpy(name, data, name_len);
    name[name_len] = '\0';

    memcpy(value, data + name_len, value_len);
    value[value_len] = '\0';

    // Call the function-under-test
    err = lyxp_vars_set(&vars, name, value);

    // Free allocated memory
    free(name);
    free(value);

    // Clean up vars if it was set
    if (vars) {
        lyxp_vars_free(vars);
    }

    return 0;
}