#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Allocate memory for ucl_object_t
    ucl_object_t *ucl_obj = (ucl_object_t *)malloc(sizeof(ucl_object_t));
    if (ucl_obj == NULL) {
        return 0;
    }

    // Initialize ucl_object_t with some data
    memset(ucl_obj, 0, sizeof(ucl_object_t));
    ucl_obj->type = UCL_STRING;
    ucl_obj->value.sv = (char *)data;
    ucl_obj->len = size;

    // Prepare a pointer for the result string
    const char *result_str = NULL;

    // Call the function-under-test
    bool success = ucl_object_tostring_safe(ucl_obj, &result_str);

    // Free allocated memory
    free(ucl_obj);

    return 0;
}