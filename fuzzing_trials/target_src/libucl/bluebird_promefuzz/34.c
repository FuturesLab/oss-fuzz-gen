#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include "ucl.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file != NULL) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size) {
    // Step 1: Prepare the environment
    ucl_object_t *comments = NULL;
    ucl_object_t *srch = NULL;
    ucl_object_t *new_object = NULL;
    ucl_object_t *from_string = NULL;
    ucl_object_t *result = NULL;

    // Step 2: Initialize objects
    if (Size > 0) {
        comments = ucl_object_typed_new(UCL_OBJECT);
        srch = ucl_object_typed_new(UCL_OBJECT);

        // Use the data as keys for the objects
        comments->key = (const char *)Data;
        comments->keylen = Size;
        
        srch->key = (const char *)Data;
        srch->keylen = Size;
    }

    // Step 3: Invoke the target functions
    const ucl_object_t *found_comment = ucl_comments_find(comments, srch);
    found_comment = ucl_comments_find(comments, srch);

    if (Size > 0) {
        new_object = ucl_object_typed_new((ucl_type_t)(Data[0] % (UCL_NULL + 1)));
        if (new_object != NULL) {
            // Ensure the string is null-terminated before passing it to ucl_object_fromstring
            char *null_terminated_string = (char *)malloc(Size + 1);
            if (null_terminated_string != NULL) {
                memcpy(null_terminated_string, Data, Size);
                null_terminated_string[Size] = '\0';
                from_string = ucl_object_fromstring(null_terminated_string);
                free(null_terminated_string);

                if (from_string != NULL) {
                    result = ucl_elt_append(NULL, from_string);
                    // Avoid double free by setting from_string to NULL after appending
                    from_string = NULL;
                }
            }
        }
    }

    // Step 4: Cleanup
    if (comments) ucl_object_unref(comments);
    if (srch) ucl_object_unref(srch);
    if (new_object) ucl_object_unref(new_object);
    if (result) ucl_object_unref(result);

    return 0;
}