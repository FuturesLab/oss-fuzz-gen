#include "ucl.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    // Initialize a ucl_object_t object
    ucl_object_t *obj = ucl_object_fromstring((const char *)data);

    // Ensure the object is not NULL
    if (obj == NULL) {
        return 0;
    }

    // Initialize a pointer for the output string
    const char *output_str = NULL;

    // Call the function under test
    bool result = ucl_object_tostring_safe(obj, &output_str);

    // Free the ucl_object_t object
    ucl_object_unref(obj);

    // Return 0 to indicate successful execution
    return 0;
}