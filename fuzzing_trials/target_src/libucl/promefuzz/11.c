// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_new_full at ucl_util.c:2992:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_lookup_len at ucl_util.c:2656:1 in ucl.h
// ucl_object_pop_key at ucl_util.c:2528:1 in ucl.h
// ucl_object_pop_key at ucl_util.c:2528:1 in ucl.h
// ucl_object_lookup_len at ucl_util.c:2656:1 in ucl.h
// ucl_object_new_full at ucl_util.c:2992:1 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Write the fuzzing data to a dummy file
    write_dummy_file(Data, Size);

    // Create a new UCL object
    ucl_object_t *root = ucl_object_new_full(UCL_OBJECT, 0);
    if (!root) {
        return 0;
    }

    // Use part of the data as a key, ensure null-termination
    char *key = (char *)malloc(Size + 1);
    if (!key) {
        ucl_object_unref(root);
        return 0;
    }
    memcpy(key, Data, Size);
    key[Size] = '\0'; // Null-terminate the key

    size_t keylen = Size; // Use the full size for the key length

    // Call ucl_object_lookup_len
    const ucl_object_t *lookup_result = ucl_object_lookup_len(root, key, keylen);

    // Call ucl_object_pop_key twice
    ucl_object_t *pop_result1 = ucl_object_pop_key(root, key);
    ucl_object_t *pop_result2 = ucl_object_pop_key(root, key);

    // Call ucl_object_lookup_len again
    lookup_result = ucl_object_lookup_len(root, key, keylen);

    // Create another UCL object to insert
    ucl_object_t *new_object = ucl_object_new_full(UCL_STRING, 0);
    if (new_object) {
        new_object->value.sv = "test_value";  // Assign a test value
    }

    // Call ucl_object_insert_key
    bool insert_result = ucl_object_insert_key(root, new_object, key, keylen, true);

    // Clean up
    if (pop_result1) {
        ucl_object_unref(pop_result1);
    }
    if (pop_result2) {
        ucl_object_unref(pop_result2);
    }
    ucl_object_unref(root);
    free(key);

    return 0;
}