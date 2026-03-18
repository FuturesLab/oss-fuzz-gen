// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_iterate_new at ucl_util.c:2794:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_iterate_safe at ucl_util.c:2839:1 in ucl.h
// ucl_object_iterate_reset at ucl_util.c:2819:1 in ucl.h
// ucl_object_iterate_with_error at ucl_util.c:2717:1 in ucl.h
// ucl_object_iterate_free at ucl_util.c:2903:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_fromstring_common at ucl_util.c:2225:1 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>

static ucl_object_t* create_dummy_ucl_object(const uint8_t *Data, size_t Size) {
    ucl_object_t *obj = ucl_object_fromstring_common((const char *)Data, Size, 0);
    return obj;
}

int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    ucl_object_t *obj = create_dummy_ucl_object(Data, Size);
    if (!obj) return 0;

    ucl_object_iter_t iter = ucl_object_iterate_new(obj);
    if (!iter) {
        ucl_object_unref(obj);
        return 0;
    }

    const ucl_object_t *next_obj;
    bool expand_values = true;
    while ((next_obj = ucl_object_iterate_safe(iter, expand_values)) != NULL) {
        // Process next_obj if necessary
    }

    // Reset the iterator
    iter = ucl_object_iterate_reset(iter, obj);

    // Iterate with error handling
    int error = 0;
    ucl_object_iter_t iter_with_error = NULL;
    while ((next_obj = ucl_object_iterate_with_error(obj, &iter_with_error, expand_values, &error)) != NULL) {
        if (error) {
            // Handle error
            break;
        }
    }

    // Free the iterator
    ucl_object_iterate_free(iter);

    // Clean up
    ucl_object_unref(obj);

    return 0;
}