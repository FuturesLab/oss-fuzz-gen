#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Ensure the input data is null-terminated
    char *input_data = (char *)malloc(size + 1);
    if (input_data == NULL) {
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0';

    ucl_type_t type;
    bool result = ucl_object_string_to_type(input_data, &type);

    // Clean up
    free(input_data);

    return 0;
}