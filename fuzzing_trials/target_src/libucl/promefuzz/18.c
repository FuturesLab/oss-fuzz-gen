// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_array_merge at ucl_util.c:3193:6 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_delete_key at ucl_util.c:2503:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
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
#include <string.h>

static void write_to_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file != NULL) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Prepare strings from the input data
    char *str1 = strndup((const char *)Data, Size);
    char *str2 = strndup((const char *)(Data + Size / 2), Size - Size / 2);

    // Create UCL objects from strings
    ucl_object_t *obj1 = ucl_object_fromstring(str1);
    ucl_object_t *obj2 = ucl_object_fromstring(str2);

    // Ensure objects are arrays for merging
    ucl_object_t *array1 = ucl_object_fromstring("[]");
    ucl_object_t *array2 = ucl_object_fromstring("[]");

    // Attempt to merge arrays
    if (array1 && array2) {
        ucl_array_merge(array1, array2, true);
    }

    // Insert key-value pairs into an object
    ucl_object_t *obj3 = ucl_object_fromstring("{}");
    if (obj3 && obj1 && obj2) {
        ucl_object_insert_key(obj3, obj1, "key1", 0, true);
        ucl_object_insert_key(obj3, obj2, "key2", 0, true);
    }

    // Delete a key from the object
    if (obj3) {
        ucl_object_delete_key(obj3, "key1");
    }

    // Free allocated resources
    if (array1) {
        ucl_object_unref(array1);
    }
    if (array2) {
        ucl_object_unref(array2);
    }
    if (obj3) {
        ucl_object_unref(obj3);
    }
    if (str1) {
        free(str1);
    }
    if (str2) {
        free(str2);
    }

    return 0;
}