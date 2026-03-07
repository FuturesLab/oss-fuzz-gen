// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_new at ucl_util.c:2980:1 in ucl.h
// ucl_object_new at ucl_util.c:2980:1 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_new at ucl_util.c:2980:1 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_new_userdata at ucl_util.c:3045:1 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_fromlstring at ucl_util.c:3084:1 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_lookup_any at ucl_util.c:2683:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static void dummy_dtor(void *ptr) {
    // Dummy destructor
}

static int dummy_emitter(const ucl_object_t *obj, const char *key, size_t keylen, void *ud) {
    // Dummy emitter
    return 0;
}

int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare the data for the first ucl_object_insert_key
    ucl_object_t *top = ucl_object_new();
    ucl_object_t *elt1 = ucl_object_new();
    const char *key1 = "key1";
    size_t keylen1 = strlen(key1);

    // First insertion
    ucl_object_insert_key(top, elt1, key1, keylen1, true);

    // Prepare the data for the second ucl_object_insert_key
    ucl_object_t *elt2 = ucl_object_new();
    const char *key2 = "key2";
    size_t keylen2 = strlen(key2);

    // Second insertion
    ucl_object_insert_key(top, elt2, key2, keylen2, true);

    // Create user data object
    ucl_object_t *userdata_obj = ucl_object_new_userdata(dummy_dtor, dummy_emitter, NULL);
    const char *key3 = "userdata";
    size_t keylen3 = strlen(key3);

    // Third insertion
    ucl_object_insert_key(top, userdata_obj, key3, keylen3, true);

    // Create a UCL object from a string
    if (Size > 1) {
        const char *str = (const char *)Data;
        size_t len = Size - 1;
        ucl_object_t *str_obj = ucl_object_fromlstring(str, len);

        const char *key4 = "string";
        size_t keylen4 = strlen(key4);

        // Fourth insertion
        ucl_object_insert_key(top, str_obj, key4, keylen4, true);
    }

    // Look up an object with a key
    const char *lookup_key = "key1";
    ucl_object_lookup_any(top, lookup_key, "key2", "userdata", "string", NULL);

    // Cleanup
    ucl_object_unref(top);

    return 0;
}