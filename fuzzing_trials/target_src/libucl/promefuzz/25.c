// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_frombool at ucl_util.c:3118:1 in ucl.h
// ucl_object_todouble at ucl_util.c:3446:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_frombool at ucl_util.c:3118:1 in ucl.h
// ucl_object_frombool at ucl_util.c:3118:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Ensure there's at least 1 byte to read

    // Create a boolean UCL object
    bool bool_value = Data[0] % 2;
    ucl_object_t *bool_obj = ucl_object_frombool(bool_value);
    if (!bool_obj) return 0;

    // Convert the boolean UCL object to a double
    double double_value = ucl_object_todouble(bool_obj);

    // Unreference the boolean UCL object
    ucl_object_unref(bool_obj);

    // Create a new UCL object to use as a top-level object
    ucl_object_t *top_obj = ucl_object_frombool(false); // Just to have a valid object
    if (!top_obj) return 0;

    // Create another UCL object to insert
    ucl_object_t *insert_obj = ucl_object_frombool(true);
    if (!insert_obj) {
        ucl_object_unref(top_obj);
        return 0;
    }

    // Use a key from the input data
    const char *key = (const char *)Data;
    size_t keylen = Size;

    // Insert the object with the key into the top-level object
    bool result = ucl_object_insert_key(top_obj, insert_obj, key, keylen, true);

    // Cleanup
    ucl_object_unref(top_obj); // This will also unref insert_obj if insertion was successful

    return 0;
}