#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_65(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for creating meaningful inputs
    if (size < 2) {
        return 0;
    }

    // Allocate and initialize ucl_object_t objects
    ucl_object_t *obj1 = ucl_object_new();
    ucl_object_t *obj2 = ucl_object_new();

    // Create a string for the comment, ensuring null-termination
    size_t comment_size = size - 1;
    char *comment = (char *)malloc(comment_size + 1);
    if (comment == NULL) {
        ucl_object_unref(obj1);
        ucl_object_unref(obj2);
        return 0;
    }
    memcpy(comment, data, comment_size);
    comment[comment_size] = '\0';

    // Call the function under test
    ucl_comments_add(obj1, obj2, comment);

    // Clean up
    ucl_object_unref(obj1);
    ucl_object_unref(obj2);
    free(comment);

    return 0;
}