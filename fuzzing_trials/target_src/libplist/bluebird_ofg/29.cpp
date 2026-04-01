#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "plist/plist.h"

extern "C" int plist_bool_val_is_true(plist_t node);

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
    // Initialize a plist node
    plist_t node = plist_new_bool(false);

    // If size is greater than 0, use the first byte to set the boolean value
    if (size > 0) {
        bool value = (data[0] % 2 == 0);  // Use the first byte to determine true or false
        plist_set_bool_val(node, value);
    }

    // Call the function-under-test
    int result = plist_bool_val_is_true(node);

    // Clean up
    plist_free(node);

    return 0;
}