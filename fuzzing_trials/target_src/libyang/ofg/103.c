#include <stdlib.h>
#include <string.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_103(const uint8_t *data, size_t size) {
    struct lyxp_var *vars = NULL;
    const char *var_name = "example_var";
    const char *var_value = "example_value";

    // Ensure data is not empty and has enough space for variable name and value
    if (size < strlen(var_name) + strlen(var_value) + 2) {
        return 0;
    }

    // Use data to create a string for the variable name and value
    char *name_data = (char *)malloc(size + 1);
    if (!name_data) {
        return 0;
    }
    memcpy(name_data, data, size);
    name_data[size] = '\0';

    // Call the function-under-test
    LY_ERR err = lyxp_vars_set(&vars, var_name, var_value);

    // Free allocated memory
    free(name_data);

    // Clean up vars if necessary
    if (vars) {
        lyxp_vars_free(vars);
    }

    return 0;
}