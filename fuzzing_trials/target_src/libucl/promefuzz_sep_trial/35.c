// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_array_index_of at ucl_util.c:3355:1 in ucl.h
// ucl_object_copy at ucl_util.c:3692:1 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_array_prepend at ucl_util.c:3163:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static void write_to_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Ensure the input data is null-terminated
    char *null_terminated_data = (char *)malloc(Size + 1);
    if (!null_terminated_data) return 0;

    memcpy(null_terminated_data, Data, Size);
    null_terminated_data[Size] = '\0';

    // Prepare environment
    ucl_object_t *array = ucl_object_fromstring("[]");
    ucl_object_t *element = ucl_object_fromstring(null_terminated_data);
    ucl_object_t *copy = NULL;

    if (array && element) {
        // Invoke ucl_array_index_of
        unsigned int index = ucl_array_index_of(array, element);

        // Invoke ucl_object_copy
        copy = ucl_object_copy(element);

        // Invoke ucl_object_fromstring
        ucl_object_t *new_element = ucl_object_fromstring(null_terminated_data);

        // Invoke ucl_array_prepend
        if (new_element) {
            bool result = ucl_array_prepend(array, new_element);
            if (!result) {
                ucl_object_unref(new_element);
            }
        }
    }

    // Cleanup
    free(null_terminated_data);
    if (element) {
        ucl_object_unref(element);
    }
    if (copy) {
        ucl_object_unref(copy);
    }
    if (array) {
        ucl_object_unref(array);
    }

    return 0;
}