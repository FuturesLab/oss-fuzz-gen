// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_new_full at ucl_util.c:2992:1 in ucl.h
// ucl_object_new_full at ucl_util.c:2992:1 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_lookup_len at ucl_util.c:2656:1 in ucl.h
// ucl_object_pop_key at ucl_util.c:2528:1 in ucl.h
// ucl_object_new_full at ucl_util.c:2992:1 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_pop_key at ucl_util.c:2528:1 in ucl.h
// ucl_object_lookup_len at ucl_util.c:2656:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "ucl.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize a UCL object
    ucl_object_t *root = ucl_object_new_full(UCL_OBJECT, 0);

    // Use the data to create a key
    const char *key1 = "key1";
    const char *key2 = "key2";
    const char *key3 = "key3";
    size_t keylen1 = strlen(key1);
    size_t keylen2 = strlen(key2);
    size_t keylen3 = strlen(key3);

    // Create a new UCL object to insert
    ucl_object_t *new_obj = ucl_object_new_full(UCL_STRING, 0);
    new_obj->value.sv = (const char *)Data;
    new_obj->len = Size;

    // Insert the new object with a key
    ucl_object_insert_key(root, new_obj, key1, keylen1, true);

    // Lookup the object by key
    const ucl_object_t *looked_up = ucl_object_lookup_len(root, key1, keylen1);

    // Pop a key from the object
    ucl_object_t *popped_obj1 = ucl_object_pop_key(root, key1);

    // Insert another object
    ucl_object_t *another_obj = ucl_object_new_full(UCL_STRING, 0);
    another_obj->value.sv = "static_data";
    another_obj->len = strlen("static_data");
    ucl_object_insert_key(root, another_obj, key2, keylen2, true);

    // Pop another key
    ucl_object_t *popped_obj2 = ucl_object_pop_key(root, key2);

    // Lookup again
    looked_up = ucl_object_lookup_len(root, key3, keylen3);

    // Clean up
    if (popped_obj1) {
        ucl_object_unref(popped_obj1);
    }
    if (popped_obj2) {
        ucl_object_unref(popped_obj2);
    }
    ucl_object_unref(root);

    return 0;
}